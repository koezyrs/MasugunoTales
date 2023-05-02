#include "KeyboardController.h"

#include "../Map.h"
#include "../Actor.h"
#include "../HUD.h"

KeyboardController::KeyboardController() {}
KeyboardController::KeyboardController(TransformComponent* trans, SpriteComponent* sprite, bool *movement)
: cooldownBasicAttack(0), state(NONE), movementAvailable(movement)
{
    mSprite = sprite;
    mTransform = trans;
    target = nullptr;
}

std::shared_ptr<Monster>const& KeyboardController::getTarget() const
{
    return target;
}

void KeyboardController::setTarget(std::shared_ptr<Monster>& _tar) {
    target = _tar;
}

void KeyboardController::unsetTarget() {
    if(target) target->unTargeted();
    target.reset();
}

void KeyboardController::setNearestTarget()
{
    int distanceToNearestTarget = 320; // Scan radious
    Vector2D playerPos = Game::gPlayer->getTransformComponent()->position;
    for(auto& monster : Game::currentMap->monsters)
    {
        Vector2D monsterPos = monster->getTransformComponent()->position;
        int distance = playerPos.DistanceTo(monsterPos);
        if(distance < distanceToNearestTarget)
        {
            distanceToNearestTarget = distance;
            if(target) target->unTargeted();
            target = monster;
            target->setTargeted();
        }
    }
    if(distanceToNearestTarget == 320)
    {
        if(target) target->unTargeted();
        target.reset();
    }
}

void KeyboardController::PerformSkill(int skill_id, Uint64 &_cooldown, bool is_collide_monster)
{
    if(!target) return;
    SkillType sk = SkillDB::skillDatabase[skill_id];
    if(sk.skillName.empty())
    {
        std::cerr << "No skill id as " << skill_id << "! Please check Skill Database" << std::endl;
        return;
    }

    float pAS = Game::gPlayer->mStats->AttackSpeed;
    if(SDL_GetTicks64() <= _cooldown - pAS * sk.percentAS)
    {
        std::string _message = "Wait " +  to_string((float)(_cooldown - pAS - SDL_GetTicks64())/1000) + "s for the next attack!";
        Game::gHUD->setSystemMessage(_message, 2000);
        return;
    }

    // Attack Monster
    bool success = false;
    SDL_Rect monsterRect = target->getColliderComponent()->mCollider;
    Vector2D monsterPos = Vector2D(monsterRect.x + Game::gCamera.x, monsterRect.y + Game::gCamera.y);
    Vector2D currentplayerPos = mTransform->position;
    float distance = sqrt((monsterPos.x - currentplayerPos.x)*(monsterPos.x - currentplayerPos.x) + (monsterPos.y - currentplayerPos.y)*(monsterPos.y - currentplayerPos.y));
    float skillRange = sk.skillRange;
    if( ((distance <= skillRange) || is_collide_monster) && (target->isTargeted()) )
    {
        float offsetX = 32;
        float offsetY = 32;
        target->setTrigger();
        int pDamage = Game::gPlayer->mStats->Damage;
        Game::currentMap->AddProjectile(monsterPos.x - offsetX, monsterPos.y - offsetY, sk.skillFrames, sk.skillSprite, sk.damage + pDamage * sk.percentDamage);
        success = true;
    }

    if(!success) return;
    _cooldown = SDL_GetTicks64() + sk.cooldown;
    Game::gHUD->setSystemMessage(" ", 0);
}

void KeyboardController::Update()
{
    if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
    {
        if(*movementAvailable)
        {

            switch(Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                mTransform->velocity.y -= mTransform->speed;
                break;
            case SDLK_DOWN:
                mTransform->velocity.y += mTransform->speed;
                break;
            case SDLK_LEFT:
                mTransform->velocity.x -= mTransform->speed;
                break;
            case SDLK_RIGHT:
                mTransform->velocity.x += mTransform->speed;
                break;
            default:
                break;
            }
        }
    }

    if(Game::event.type == SDL_KEYUP && Game::event.key.repeat == 0)
    {
        if(*movementAvailable)
        {
            switch(Game::event.key.keysym.sym)
            {
            case SDLK_UP:
                mTransform->velocity.y += mTransform->speed;
                break;
            case SDLK_DOWN:
                mTransform->velocity.y -= mTransform->speed;
                break;
            case SDLK_LEFT:
                mTransform->velocity.x += mTransform->speed;
                break;
            case SDLK_RIGHT:
                mTransform->velocity.x -= mTransform->speed;
                break;
            }
        }
    }

    if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
    {
        switch(Game::event.key.keysym.sym)
        {
        case SDLK_TAB:
            {
                setNearestTarget();
                break;
            }
        /*
        case SDLK_LCTRL:
            {
                PerformSkill(1, cooldownBasicAttack);
                break;
            }
        */
        }
    }

    // Collision check
    if(target)
    {
        if(Collision::AABB(*Game::gPlayer->getColliderComponent(), *target->getColliderComponent()))
        {
            if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
            {
                switch(Game::event.key.keysym.sym)
                {
                case SDLK_LCTRL:
                    {
                        PerformSkill(1, cooldownBasicAttack, true);
                        break;
                    }
                }
            }
        }else
        {
            if(Game::event.type == SDL_KEYDOWN && Game::event.key.repeat == 0)
            {
                switch(Game::event.key.keysym.sym)
                {
                case SDLK_LCTRL:
                    {
                        PerformSkill(1, cooldownBasicAttack, false);
                        break;
                    }
                }
            }
        }
    }




}
