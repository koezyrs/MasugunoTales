#pragma once
#ifndef Shop_h
#define Shop_h

#include "Game.h"
#include "Window.h"
#include "Button.h"
#include "Label.h"
#include "Item.h"
#include "Equipment.h"
#include "Dialogue.h"
#include "Inventory.h"
#include "HUD.h"
#include "Database/ItemDB.h"
#include "Database/EquipmentDB.h"
#include "Database/ShopDB.h"
#include "Settings.h"
#include "TextureManager.h"

struct ShopSlot;

class Shop : public Window
{
public:
    Shop(int _x, int _y, int _width, int _height, std::string shop_title);
    ~Shop();
    void Update() override;
    void Render() override;
    void Reset();
    bool OpenShop(int shop_id);
    bool AddItem(int item_id);
    bool AddEquipment(int equipment_id);
    void SetItemTarget(Item* item);
    void SetEquipmentTarget(Equipment* equip);
    void SetNameAndPriceLabel(std::string _name, int _price);
    bool isBuyOrSell();
private:
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* ShopBox;
    SDL_Rect srcRect, destRect;
    std::vector<Item*> itemList;
    std::vector<Equipment*> equipmentList;
    ShopSlot* shopSlot;
    Label* shopTitle;
    Button* closeButton;

    Label* goldLabel;
    std::string goldStr;

    // Target
    Item* pickedItem;
    Equipment* pickedEquip;
    SDL_Rect srcPickedRect, destPickedRect;
    Label* pickedName;
    Label* pickedPrice;

    // Buy or Sell
    // Buy = 0, Sell = 1
    bool BuyOrSell = 0; // Default buy
    Button *acceptBtn, *buyingBtn, *sellBtn;

private:
    void Buy();
};

#endif // Shop_h
