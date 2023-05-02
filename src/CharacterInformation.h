#pragma once
#ifndef CharacterInformation_h
#define CharacterInformation_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <algorithm>

#include "Game.h"
#include "Window.h"
#include "Actor.h"
#include "Button.h"
#include "Label.h"
#include "Equipment.h"
#include "Inventory.h"

#include "Settings.h"

struct EquipmentSlot;

class CharacterInformation : public Window
{
public:
    CharacterInformation(int _x, int _y, int _width, int _height);

    ~CharacterInformation();
    void Update() override;
    void Render() override;
    bool AddEquipment(int equipment_id);

    // For save data only
    void FindEquipmentAtSlot(int slot_id, int *equipment_id);
    // </>
private:
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* CharacterInformationBox;
    SDL_Rect srcRect, destRect;

    std::vector<Equipment*> equipmentList;

    EquipmentSlot* equipSlot;

    Label* characterInformationTitle;

    Label *name, *playerClass, *level, *damage, *defense, *health, *mana, *attackSpeed;

    Label *strength, *dexterity, *intelligence, *vitality, *agility;


    std::string LevelStr, DamageStr, DefenseStr, HPStr, MPStr, ASStr;
    std::string strengthStr, dexterityStr, intelligenceStr, vitalityStr, agilityStr;
    Button* closeButton;
    Button *addStrength, *addDexterity, *addIntelligence, *addVitality, *addAgility;

    //Power points + avalible points
    Label *powerPoint, *avaliblePoints;
    std::string PowerStr, AvalibleStr;
};

#endif // CharacterInformation_h

