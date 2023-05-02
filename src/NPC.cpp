#include "NPC.h"
NPC::NPC(float _x, float _y, int _width, int _height, int _scale, std::string spriteName, std::string name)
: position(_x,_y), npcName(name)
{
    mTransform = new TransformComponent(_x, _y, _width, _height, _scale);
    mSprite = new SpriteComponent(spriteName, mTransform, true);
    mCollider = new ColliderComponent(mTransform, "NPC");
    mName = new NameComponent(mTransform, name, GAME_FONT, 10, SDL_Color{255,255,255});
}

void NPC::Update()
{
    mTransform->position.x = position.x;
    mTransform->position.y = position.y;
    mTransform->Update();
    mCollider->Update();
    mSprite->Update();
    mName->Update();
}
void NPC::Render()
{
    mSprite->Render();
    mName->Render();
}

TransformComponent* NPC::getTransformComponent() {return mTransform;}
ColliderComponent* NPC::getColliderComponent() {return mCollider;}
SpriteComponent* NPC::getSpriteComponent() {return mSprite;}
NameComponent* NPC::getNameComponent() {return mName;}
bool NPC::isActive() {return active;}
void NPC::destroy() {active = false;}

NPC::~NPC()
{
    delete mTransform;
    delete mSprite;
    delete mCollider;
    delete mName;
}

void NPC::PlayDialogue()
{
    isInteract = true;
    Game::gShop->hideWindow();
    DialogueManager::Play(npcName);
}

void NPC::HideDialogue()
{
    isInteract = false;
    Game::gDialogue->hideWindow();
}
