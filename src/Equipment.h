#pragma once
#ifndef Equipment_h
#define Equipment_h

#include <SDL.h>
#include <string>
#include <functional>

#include "TextureManager.h"
#include "Settings.h"

class Equipment
{
public:
    Equipment(int equipment_id, std::string spriteName, EQUIPMENT_TAG _equipmentTag, std::string _equipmentName, std::string _description,
                     int _strength, int _dexterity, int _intelligence, int _vitality, int _agility, int _buyPrice, int _sellPrice);
    ~Equipment();
    SDL_Texture* getEquipmentSprite();
    bool isActive();
    void destroy();
    int equipment_id;
    EQUIPMENT_TAG equipmentTag;
    std::string equipmentName;
    std::string description;
    int Strength = 0;
    int Dexterity = 0;
    int Intelligence = 0;
    int Vitality = 0;
    int Agility = 0;
    int buyPrice, sellPrice;
private:
    bool active = true;
    SDL_Texture* equipmentSprite;
};

#endif // Equipment
