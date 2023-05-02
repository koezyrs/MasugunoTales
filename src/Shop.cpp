#include "Shop.h"

struct ShopSlot
{
    ShopSlot() {}
    void init(int _x, int _y)
    {
        SDL_Color White = {255, 255, 255};
        srcRect = {0,0,32,32};
        destRect = {_x, _y,32,32};
        descriptionName = new Label(GAME_FONT, " ", 10, _x - 140 + 15, _y - 30 + 5, White, 132);
        descriptionContent = new Label(GAME_FONT, " ", 10, _x - 140 + 3, _y - 30 + 15, White, 132);
        descriptionSellGold = new Label(GAME_FONT, " ", 10, _x - 140 + 10, _y - 30 + 183, White, 132);
    }


    void handleEvent(SDL_Event* e)
    {
        if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            bool inside = false;
            // check if the mouse is in the button
            if((x < destRect.x) || (x > destRect.x + 32) || (y < destRect.y) || (y > destRect.y + 32)) inside = false;
            else inside = true;

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && item != NULL)
            {
                Game::gShop->SetItemTarget(item);
                Game::gShop->SetNameAndPriceLabel(item->itemName, item->buyPrice);
            }

            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {
                Game::gShop->SetEquipmentTarget(equipment);
                Game::gShop->SetNameAndPriceLabel(equipment->equipmentName, equipment->buyPrice);
            }

        }
    }

    void RenderDescription()
    {
        //Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            bool inside = false;
            // check if the mouse is in the button
            if((x < destRect.x) || (x > destRect.x + 32) || (y < destRect.y) || (y > destRect.y + 32)) inside = false;
            else inside = true;

            if(inside && isFull && (item || equipment))
            {
                SDL_Rect descriptSrc = {0,0,137,198}, descriptDest = {destRect.x - 140, destRect.y - 30, 137, 198};
                TextureManager::Draw(descriptionBox, descriptSrc, descriptDest);
                descriptionName->Render();
                descriptionContent->Render();
                descriptionSellGold->Render();
            }
    }

    void Reset()
    {
        item = NULL;
        equipment = NULL;
        descriptionName->Reset();
        descriptionContent->Reset();
        descriptionSellGold->Reset();
        isFull = false;
    }

    void AddItemToSlot(Item* _item)
    {
        Reset();
        item = _item;
        descriptionName = new Label(GAME_FONT, item->itemName.c_str(), 10, destRect.x - 140 + 15, destRect.y - 30 + 5, White, 132);
        descriptionContent = new Label(GAME_FONT, item->description.c_str(), 10, destRect.x - 140 + 3, destRect.y - 30 + 15, White, 132);
        std::string value = "Sell gold: " +  std::to_string(item->sellPrice);
        descriptionSellGold = new Label(GAME_FONT, value.c_str(), 10, destRect.x - 140 + 10, destRect.y - 30 + 183, White, 132);
        isFull = true;
    }

    void AddEquipmentToSlot(Equipment* _equipment)
    {
        Reset();
        equipment = _equipment;
        descriptionName = new Label(GAME_FONT, equipment->equipmentName.c_str(), 10, destRect.x - 140 + 15, destRect.y - 30 + 5, White, 132);
        descriptionContent = new Label(GAME_FONT, equipment->description.c_str(), 10, destRect.x - 140 + 3, destRect.y - 30 + 15, White, 132);
        std::string value = "Sell gold: " + std::to_string(equipment->sellPrice);
        descriptionSellGold = new Label(GAME_FONT, value.c_str(), 10, destRect.x - 140 + 10, destRect.y - 30 + 183, White, 132);
        isFull = true;
    }

    SDL_Color White = {255,255,255};
    bool isFull = false;
    Item* item = NULL;
    Equipment* equipment = NULL;
    SDL_Rect srcRect, destRect;
    SDL_Texture* descriptionBox = TextureManager::GetTexture("DescriptionBox");
    Label* descriptionName;
    Label* descriptionContent;
    Label* descriptionSellGold;
};

Shop::Shop(int _x, int _y, int _width, int _height, std::string shop_title)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height), pickedItem(NULL), pickedEquip(NULL)
{
    ShopBox = TextureManager::GetTexture("Shop");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 257, _y + 5, 13, 13, [this]{Window::hideWindow(); });
    shopTitle = new Label(GAME_FONT, shop_title.c_str(), 10, _x + 5, _y + 5, White, 250);
    goldLabel = new Label(GAME_FONT, " ", 10, _x + 35, _y + 270, White, 250);
    shopSlot = new ShopSlot[MAX_SHOP_SLOTS];
    pickedName = new Label(GAME_FONT, " ", 10, _x + 60, _y + 226, Black, 250);
    pickedPrice = new Label(GAME_FONT, " ", 10, _x + 60, _y + 244, Black, 250);
    acceptBtn = new Button("AcceptButtonOut", "AcceptButtonOver", _x + 201, _y + 229, 56, 21, [this]{Buy();});
    buyingBtn = new Button("BuyButtonOut", "BuyButtonOver", _x + 176, _y + 264, 49, 20, [this]{BuyOrSell = 0;});
    sellBtn = new Button("SellButtonOut", "SellButtonOver", _x + 225, _y + 264, 49, 20, [this]{BuyOrSell = 1;});
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};

    int slot = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            shopSlot[slot].init(position.x + 8 + j*38, position.y + 27 + i*38);
            slot++;
        }
    }

    srcPickedRect = {0,0,32,32};
    destPickedRect = {_x + 19, _y + 223, 32,32};
}

void Shop::Update()
{
    if(isHide()) return;
    itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
                [](Item* theItem){return !theItem->isActive();}), itemList.end());

    equipmentList.erase(std::remove_if(equipmentList.begin(), equipmentList.end(),
                [](Equipment* theEquipment){return !theEquipment->isActive();}), equipmentList.end());



    closeButton->handleEvent(&Game::event);
    buyingBtn->handleEvent(&Game::event);
    sellBtn->handleEvent(&Game::event);
    if(!BuyOrSell) acceptBtn->handleEvent(&Game::event);

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        shopSlot[i].handleEvent(&Game::event);
    }

    std::string newGold = std::to_string(Game::gInventory->GetGold());
    if(goldStr != newGold)
    {
        goldStr = newGold;
        goldLabel->Reset();
        goldLabel = new Label(GAME_FONT, goldStr.c_str(), 10, position.x + 35, position.y + 270, White, 250);
    }

}

void Shop::Render()
{
    if(isHide()) return;

    TextureManager::Draw(ShopBox, srcRect, destRect);
    shopTitle->Render();
    goldLabel->Render();
    closeButton->Render();

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull)
        {
            if(shopSlot[i].item != NULL) TextureManager::Draw(shopSlot[i].item->getItemSprite(), shopSlot[i].srcRect, shopSlot[i].destRect);
            if(shopSlot[i].equipment != NULL) TextureManager::Draw(shopSlot[i].equipment->getEquipmentSprite(), shopSlot[i].srcRect, shopSlot[i].destRect);
        }
    }

    if(pickedEquip)
    {
        TextureManager::Draw(pickedEquip->getEquipmentSprite(), srcPickedRect, destPickedRect);
    }
    else if(pickedItem)
    {
        TextureManager::Draw(pickedItem->getItemSprite(), srcPickedRect, destPickedRect);
    }
    pickedName->Render();
    pickedPrice->Render();
    buyingBtn->Render();
    sellBtn->Render();

    SDL_Rect optionSrc = {0,0,49,20};
    if(!BuyOrSell)
    {
        acceptBtn->Render();
        SDL_Rect optionDest = {static_cast<int>(position.x) + 176, static_cast<int>(position.y) + 264, 49, 20};
        TextureManager::Draw(TextureManager::GetTexture("BuyButtonOver"), optionSrc, optionDest);
    }else
    {
        SDL_Rect optionDest = {static_cast<int>(position.x) + 225, static_cast<int>(position.y) + 264, 49, 20};
        TextureManager::Draw(TextureManager::GetTexture("SellButtonOver"), optionSrc, optionDest);
    }

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull)
        {
            shopSlot[i].RenderDescription();
        }
    }
}

bool Shop::AddItem(int item_id)
{
    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return false;
    }

    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull == false)
        {
            itemList.emplace_back(new Item(itemTemp.item_id, itemTemp.spriteName,itemTemp.maxStack,itemTemp.itemTag,itemTemp.itemName, itemTemp.itemDescription, itemTemp.buyPrice, itemTemp.sellPrice ,itemTemp.ItemFunc));
            shopSlot[i].AddItemToSlot(itemList.back());
            return true;
        }
    }
    return false;
}

bool Shop::AddEquipment(int equipment_id)
{
    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        if(shopSlot[i].isFull == false)
        {
            equipmentList.emplace_back(new Equipment(equipTemp.equipment_id, equipTemp.spriteName, equipTemp.equipmentTag, equipTemp.equipmentName, equipTemp.equipmentDescription,
                                                     equipTemp.Strength, equipTemp.Dexterity, equipTemp.Intelligence,
                                                     equipTemp.Vitality, equipTemp.Agility, equipTemp.buyPrice, equipTemp.sellPrice));
            shopSlot[i].AddEquipmentToSlot(equipmentList.back());
            return true;
            break;
        }
    }
    return false;
}

void Shop::Reset()
{
    itemList.clear();
    equipmentList.clear();
    for(int i = 0; i < MAX_SHOP_SLOTS; i++)
    {
        shopSlot[i].Reset();
    }
    pickedName->Reset();
    pickedPrice->Reset();
    BuyOrSell = 0;
}

Shop::~Shop()
{
    delete closeButton;
    delete[] shopSlot;
    delete goldLabel;
    delete pickedName;
    delete pickedPrice;
    delete acceptBtn;
    delete buyingBtn;
    delete sellBtn;
    ShopBox = NULL;
}

bool Shop::OpenShop(int shop_id)
{
    if(ShopDB::shopDatabase.count(shop_id) <= 0)
    {
        std::cerr << "Not found shop id: " << shop_id << std::endl;
        return false;
    }
    Reset();
    pickedItem = NULL;
    pickedEquip = NULL;
    ShopType shopTemp = ShopDB::shopDatabase[shop_id];
    for(auto& i : shopTemp.itemList) AddItem(i);
    for(auto& e : shopTemp.equipmentList) AddEquipment(e);
    shopTitle->Reset();
    shopTitle = new Label(GAME_FONT, shopTemp.shop_title.c_str(), 10, position.x + 5, position.y + 5, White, 250);
    showWindow();
    Game::gDialogue->hideWindow();
    return true;
}

void Shop::SetItemTarget(Item* item)
{
    pickedEquip = NULL;
    pickedItem = item;
}

void Shop::SetEquipmentTarget(Equipment* equip)
{
    pickedItem = NULL;
    pickedEquip = equip;
}

void Shop::SetNameAndPriceLabel(std::string _name, int _price)
{
    pickedName->Reset();
    pickedPrice->Reset();
    std::string price = "Gold: " + std::to_string(_price);
    pickedName = new Label(GAME_FONT, _name.c_str(), 10, position.x + 60, position.y + 226, Black, 250);
    pickedPrice = new Label(GAME_FONT, price.c_str(), 10, position.x + 60, position.y + 244, Black, 250);
}

void Shop::Buy()
{
    int currentGold = Game::gInventory->GetGold();
    if(pickedEquip)
    {
        if(currentGold >= pickedEquip->buyPrice)
        {
            if(Game::gInventory->AddEquipment(pickedEquip->equipment_id))
            {
                Game::gInventory->AddGold(-pickedEquip->buyPrice);
            }else{
                Game::gHUD->setSystemMessage("Inventory is full!", 3000);
            }
        }
        else{
            Game::gHUD->setSystemMessage("You don't have enough currency to buy this equipment!", 3000);
        }
    }else if(pickedItem)
    {
        if(currentGold >= pickedItem->buyPrice)
        {
            if(Game::gInventory->AddItem(pickedItem->item_id))
            {
                Game::gInventory->AddGold(-pickedItem->buyPrice);
            }else{
                Game::gHUD->setSystemMessage("Inventory is full!", 3000);
            }
        }
        else{
            Game::gHUD->setSystemMessage("You don't have enough currency to buy this equipment!", 3000);
        }
    }
}

bool Shop::isBuyOrSell()
{
    return BuyOrSell;
}
