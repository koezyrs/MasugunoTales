#include "Equipment.h"

Equipment::Equipment(int _equipment_id, std::string spriteName, EQUIPMENT_TAG _equipmentTag, std::string _equipmentName, std::string _description,
                     int _strength, int _dexterity, int _intelligence, int _vitality, int _agility, int _buyPrice, int _sellPrice)
: equipment_id(_equipment_id), equipmentTag(_equipmentTag), equipmentName(_equipmentName), description(_description),
Strength(_strength), Dexterity(_dexterity), Intelligence(_intelligence), Vitality(_vitality), Agility(_agility), buyPrice(_buyPrice), sellPrice(_sellPrice)
{
    equipmentSprite = TextureManager::GetTexture(spriteName);
}

Equipment::~Equipment()
{
    equipmentSprite = NULL;
}

SDL_Texture* Equipment::getEquipmentSprite()
{
    return equipmentSprite;
}
bool Equipment::isActive()
{
    return active;
}
void Equipment::destroy()
{
    active = false;
}
