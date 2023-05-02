#include "Map.h"
#include "MapManager.h"
Map::Map(int _id, std::string maptex, std::string overlay)
: id(_id), width(0), height(0), sizeX(0), sizeY(0), targetX(0), targetY(0), position(), mTexture(NULL), mTexture_Overlay(NULL)
{
    std::vector<std::vector<Tile>> mapBase = MapManager::mapBase[id];
    mTexture = TextureManager::GetTexture(maptex);
    mTexture_Overlay = TextureManager::GetTexture(overlay);
    SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);
    srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    position.x = 0.0f;
    position.y = 0.0f;
    if(mapBase.empty()){
        std::cerr << "Mapbase is empty! Please check Map Manager!" << std::endl;
        return;
    }
    sizeX = mapBase[0].size();
    sizeY = mapBase.size();

    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0 ; x < sizeX; x++)
        {
            if(mapBase[y][x].isWall)
                AddWall(mapBase[y][x].position.x * GAME_PIXELS * GAME_SCALE, mapBase[y][x].position.y * GAME_PIXELS * GAME_SCALE);
        }
    }
}

Map::~Map() {}

void Map::Refresh()
{
    /*
    walls.erase(std::remove_if(walls.begin(), walls.end(),
        [](auto& theWall){return !theWall->isActive();}), walls.end());


    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](auto& theMonster){return !theMonster->isActive();}), monsters.end());

    npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
        [](auto& theNPC) {return !theNPC->isActive();}), npcs.end());

    */
    events.erase(std::remove_if(events.begin(), events.end(),
        [](auto& theEvent){return !theEvent->isActive();}), events.end());

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](auto& theProjectile){return !theProjectile->isActive();}), projectiles.end());

}

void Map::Update()
{

    Refresh();
    // Saved the last position after taking the next move
    Vector2D playerPos = Game::gPlayer->getTransformComponent()->position;

    destRect.x = position.x - Game::gCamera.x;
    destRect.y = position.y - Game::gCamera.y;

    Game::gPlayer->Update();

    for(auto& w : walls)
    {
        w->Update();
    }

    for(auto& m : monsters)
    {
        m->Update();
    }

    for(auto& n : npcs)
    {
        n->Update();
    }

    for(auto& e : events)
    {
        e->Update();
    }

    for(auto& p : projectiles)
    {
        p->Update();
    }

    // Collision check
    for(auto& wall : walls)
    {
        if(Collision::AABB(*Game::gPlayer->getColliderComponent(), *wall->getColliderComponent()))
        {
            Game::gPlayer->getTransformComponent()->position = playerPos;
        }
    }

    // Collide with NPC
    for(auto& npc : npcs)
    {
        // Check Collision
        if(Collision::AABB(*Game::gPlayer->getColliderComponent(), *npc->getColliderComponent()))
        {
            Game::gPlayer->getTransformComponent()->position = playerPos;
        }
        // Interact with NPC
        Vector2D npcPos = npc->getTransformComponent()->position;
        Vector2D currentplayerPos = Game::gPlayer->getTransformComponent()->position;
        float distance = sqrt((npcPos.x - currentplayerPos.x)*(npcPos.x - currentplayerPos.x) + (npcPos.y - currentplayerPos.y)*(npcPos.y - currentplayerPos.y));

        float exitDistance = 1.0f;
        if((Game::event.type == SDL_KEYDOWN) && (distance <= GAME_PIXELS + exitDistance))
        {

            switch(Game::event.key.keysym.sym )
            {
                case SDLK_LCTRL:
                    npc->PlayDialogue();
                    break;
            }
        }

        if((distance > GAME_PIXELS + 1) && (npc->isInteract))
        {
            npc->HideDialogue();
            Game::gShop->hideWindow();
        }

    }

    // Apply damage from projectile
    for(auto& prjtile : projectiles)
    {
        if(prjtile->isUsed()) continue;
        for(auto& mon : monsters)
        {
            if(prjtile->getTag() == "Monster") continue;
            if(Collision::AABB(*prjtile->getColliderComponent(), *mon->getColliderComponent()))
            {
                mon->ApplyDamage(prjtile->getDamage());
                prjtile->Used();
            }
        }

        if(prjtile->getTag() == "Player") continue;
        if(Collision::AABB(*prjtile->getColliderComponent(), *Game::gPlayer->getColliderComponent()))
        {
            Game::gPlayer->mStats->ApplyDamage(prjtile->getDamage());
            prjtile->Used();
        }
    }



    // Interact with event
    for(auto& eventa : events)
    {
        if(Collision::AABB(*Game::gPlayer->getColliderComponent(), *eventa->getColliderComponent()))
        {
            eventa->Perform();
            break;
        }
    }
}

void Map::RenderBottomLayer()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
    for(auto& e : events)
    {
        e->Render();
    }
}

void Map::RenderUpperLayer()
{
    for(auto& m : monsters)
    {
        m->Render();
    }

    for(auto& n : npcs)
    {
        n->Render();
    }

    for(auto& p : projectiles)
    {
        p->Render();
    }
    TextureManager::Draw(mTexture_Overlay, srcRect, destRect);
    Game::gPlayer->getNameComponent()->Render();
}
void Map::AddWall(float x, float y)
{
    walls.emplace_back(std::make_shared<Wall>(x,y));
}

void Map::AddMonster(float x, float y, int monster_id, std::vector<std::vector<Tile>> mapBase)
{
    MonsterType monster = MonsterDB::monsterDatabase[monster_id];
    if(!monster.monsterSprite.empty())
    {
        monsters.emplace_back(std::make_shared<Monster>(monster.monster_id, x, y, monster.width, monster.height, GAME_SCALE, monster.monsterName
                                          , monster.monsterSprite, monster.damage, monster.health, monster.attackSpeed,
                                          monster.attackRange, monster.stopChaseRange, monster.chaseSpeed, monster.roamSpeed,mapBase,
                                          monster.exp_reward, monster.gold_reward, monster.item_reward_id, monster.item_drop_percent,
                                          monster.equipment_reward_id, monster.equipment_drop_percent, monster.freeze));
    }
    else
    {
        std::cerr << "Can not find monster id " << monster_id << "! Please check Monster Database!";
    }
}

void Map::AddEvent(float x, float y, std::string spriteName, std::function<void()> func)
{
    events.emplace_back(std::make_shared<Event>(x,y,spriteName,func));
}

void Map::AddNPC(float x, float y, const char* filepath, std::string name)
{
    npcs.emplace_back(std::make_shared<NPC>(x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE, filepath, name));
}

void Map::AddProjectile(float x, float y, int frames, std::string skillSprite, float _damage)
{
    projectiles.emplace_back(std::make_shared<Projectile>(x, y, frames, 100, "Player", skillSprite, _damage));
}

int Map::getWidth()
{
    return width;
}
int Map::getHeight()
{
    return height;
}
int Map::getSizeX()
{
    return sizeX;
}
int Map::getSizeY()
{
    return sizeY;
}
void Map::ClearMap()
{
    walls.clear();
    monsters.clear();
    events.clear();
    npcs.clear();
    projectiles.clear();
    Game::gPlayer->getKeyboardController()->unsetTarget();
    mTexture = NULL;
}
