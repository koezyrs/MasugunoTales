#pragma once
#ifndef Inventory_h
#define Inventory_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <algorithm>

#include "Game.h"
#include "Window.h"
#include "Button.h"
#include "Label.h"
#include "Item.h"
#include "Equipment.h"
#include "CharacterInformation.h"
#include "Shop.h"
#include "Database/ItemDB.h"
#include "Database/EquipmentDB.h"

#include "Settings.h"
#include "TextureManager.h"

struct InventorySlot;

class Inventory : public Window
{
public:
    Inventory(int _x, int _y, int _width, int _height);

    ~Inventory();
    void Update() override;
    void Render() override;

    bool AddItem(int item_id);
    bool AddEquipment(int equipment_id);
    bool FindItem(int item_id, int item_amount);
    bool FindEquip(int equip_id, int equip_amount);
    bool RemoveItem(int item_id, int item_amount);
    bool RemoveEquipment(int equip_id, int equip_amount);
    void AddGold(int gold);
    int GetGold();

    // Use for login only
    void AddEquipmentToSlot(int slot_id, int equipment_id);
    void AddItemToSlot(int slot_id, int item_id, int item_amount);
    // </>

    // Use for save data only
    void FindItemAtSlot(int slot_id, int* item_id, int* item_amount);
    void FindEquipmentAtSlot(int slot_id, int* equipment_id);
    // </>
private:
    SDL_Color White = {255,255,255};
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* InventoryBox;
    SDL_Rect srcRect, destRect;

    std::vector<Item*> itemList;
    std::vector<Equipment*> equipmentList;
    int gold;

    InventorySlot* invSlot;
    Label* inventoryTitle;
    Button* closeButton;

    Label* goldLabel;
    std::string goldStr;
};

#endif // Inventory_h

