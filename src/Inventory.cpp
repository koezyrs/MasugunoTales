#include "Inventory.h"

struct InventorySlot
{
    InventorySlot() {}
    void init(int _x, int _y)
    {
        stackLabel = new Label(GAME_FONT, " ", 10, _x + 26, _y + 24, White, 20, false, []{});
        srcRect = {0,0,32,32};
        destRect = {_x, _y,32,32};
        lastClick = 0;
        lastUpdateStack = 0;
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
                if(SDL_GetTicks64() - 250 <= lastClick)     // Double Click
                {
                    if(!(Game::gShop->isHide()) && (Game::gShop->isBuyOrSell()))
                    {
                        item->currentStack = item->currentStack - 1;
                        Game::gInventory->AddGold(item->sellPrice);
                    }else
                    {
                        std::cout << "You have use the " << item->itemName << "!" << std::endl;
                        item->Perform();
                        item->currentStack = item->currentStack - 1;
                    }
                }
                lastClick = SDL_GetTicks64();
            }


            if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFull == true && equipment != NULL)
            {
                if(SDL_GetTicks64() - 250 <= lastClick)     // Double Click
                {
                    if(!(Game::gShop->isHide()) && (Game::gShop->isBuyOrSell()))
                    {
                        equipment->destroy();
                        Game::gInventory->AddGold(equipment->sellPrice);
                        Reset();
                    }else
                    {
                        if(AddEquipmentToCharacterInformation(equipment->equipment_id))
                        {
                            std::cerr << "You have equip the " << equipment->equipmentName << "!" << std::endl;
                            equipment->destroy();
                            Reset();
                        }
                    }
                }
                lastClick = SDL_GetTicks64();
            }

        }

        if(item != NULL)
        {
            if(item->currentStack <= 0)
            {
                item->destroy();
                Reset();

            }else
            {
                if(lastUpdateStack != item->currentStack)
                {
                    std::string tmp = std::to_string(item->currentStack);
                    SDL_Color White = {255, 255, 255};
                    lastUpdateStack = item->currentStack;
                    stackLabel->Reset();
                    stackLabel = new Label(GAME_FONT, tmp.c_str(), 10, destRect.x + 26, destRect.y + 24,  White, 20, false, []{});
                }
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
        lastUpdateStack = 0;
        stackLabel->Reset();
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

    bool AddEquipmentToCharacterInformation(int equipment_id)
    {
        EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
        if(equipTemp.equipmentName.empty())
        {
            std::cerr << "Can not find equipment id: " << equipment_id << std::endl;
            return false;
        }

        if(Game::gCharacterInformation->AddEquipment(equipment_id))
        {
            Game::gPlayer->mStats->Strength += equipTemp.Strength;
            Game::gPlayer->mStats->Dexterity += equipTemp.Dexterity;
            Game::gPlayer->mStats->Intelligence += equipTemp.Intelligence;
            Game::gPlayer->mStats->Vitality += equipTemp.Vitality;
            Game::gPlayer->mStats->Agility += equipTemp.Agility;
            return true;
        }
        return false;
    }

    SDL_Color White = {255,255,255};
    bool isFull = false;
    Item* item = NULL;
    Equipment* equipment = NULL;
    Label* stackLabel;
    int lastUpdateStack;
    SDL_Rect srcRect, destRect;
    Uint64 lastClick;
    SDL_Texture* descriptionBox = TextureManager::GetTexture("DescriptionBox");
    Label* descriptionName;
    Label* descriptionContent;
    Label* descriptionSellGold;
};

Inventory::Inventory(int _x, int _y, int _width, int _height)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height), gold(0)
{
    InventoryBox = TextureManager::GetTexture("Inventory");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 181, _y + 3, 13, 13, [this]{Window::hideWindow(); });
    inventoryTitle = new Label(GAME_FONT, "Inventory", 10, _x + 5, _y + 5, White, 250);
    goldLabel = new Label(GAME_FONT, " ", 10, _x + 30, _y + 296, White, 250);
    invSlot = new InventorySlot[MAX_INVENTORY_SLOTS];
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};

    int slot = 0;
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            invSlot[slot].init(position.x + 7 + j*38, position.y + 25 + i*39);
            slot++;
        }
    }

}

void Inventory::Update()
{
    if(isHide()) return;
    itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
                [](Item* theItem){return !theItem->isActive();}), itemList.end());

    equipmentList.erase(std::remove_if(equipmentList.begin(), equipmentList.end(),
                [](Equipment* theEquipment){return !theEquipment->isActive();}), equipmentList.end());

    closeButton->handleEvent(&Game::event);

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        invSlot[i].handleEvent(&Game::event);
    }

    std::string newGold = std::to_string(gold);
    if(goldStr != newGold)
    {
        goldStr = newGold;
        goldLabel->Reset();
        goldLabel = new Label(GAME_FONT, goldStr.c_str(), 10, position.x + 30, position.y + 296, White, 250);
    }

}

void Inventory::Render()
{
    if(isHide()) return;

    TextureManager::Draw(InventoryBox, srcRect, destRect);
    inventoryTitle->Render();
    goldLabel->Render();
    closeButton->Render();

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull)
        {
            if(invSlot[i].item != NULL) TextureManager::Draw(invSlot[i].item->getItemSprite(), invSlot[i].srcRect, invSlot[i].destRect);
            if(invSlot[i].equipment != NULL) TextureManager::Draw(invSlot[i].equipment->getEquipmentSprite(), invSlot[i].srcRect, invSlot[i].destRect);
            if(invSlot[i].stackLabel != NULL) invSlot[i].stackLabel->Render();
        }
    }

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull)
        {
            invSlot[i].RenderDescription();
        }
    }

}

bool Inventory::AddItem(int item_id)
{
    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return false;
    }
    for(auto& theItem : itemList)
    {
        if(theItem->itemName == itemTemp.itemName && theItem->currentStack < theItem->maxStack)
        {
            theItem->currentStack = theItem->currentStack + 1;
            return true;
        }
    }

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull == false)
        {
            itemList.emplace_back(new Item(itemTemp.item_id, itemTemp.spriteName,itemTemp.maxStack,itemTemp.itemTag, itemTemp.itemName, itemTemp.itemDescription, itemTemp.buyPrice, itemTemp.sellPrice, itemTemp.ItemFunc));
            invSlot[i].AddItemToSlot(itemList.back());
            std::cout << "Added " << itemTemp.itemName << " to the Inventory!" << std::endl;
            return true;
        }
    }
    std::cout << "Inventory full!" << std::endl;
    return false;
}

bool Inventory::AddEquipment(int equipment_id)
{
    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(invSlot[i].isFull == false)
        {
            equipmentList.emplace_back(new Equipment(equipTemp.equipment_id, equipTemp.spriteName, equipTemp.equipmentTag, equipTemp.equipmentName, equipTemp.equipmentDescription,
                                                     equipTemp.Strength, equipTemp.Dexterity, equipTemp.Intelligence,
                                                     equipTemp.Vitality, equipTemp.Agility, equipTemp.buyPrice, equipTemp.sellPrice));
            invSlot[i].AddEquipmentToSlot(equipmentList.back());
            std::cout << "Added " << equipTemp.equipmentName << " to the Inventory!" << std::endl;
            return true;
            break;
        }
    }

    std::cout << "Inventory full!" << std::endl;
    return false;
}

Inventory::~Inventory()
{
    delete closeButton;
    delete inventoryTitle;
    delete[] invSlot;
    delete goldLabel;

    InventoryBox = NULL;
}

bool Inventory::FindItem(int item_id, int item_amount)
{
    int amount = 0;
    bool success = false;

    if(ItemDB::itemDatabase.count(item_id) <= 0)
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return false;
    }

    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(amount >= item_amount) {success = true; break;}
        if(!invSlot[i].isFull) continue;
        if(invSlot[i].item == NULL) continue;
        if(invSlot[i].item->item_id == item_id) amount = amount + invSlot[i].item->currentStack;
    }

    return success;
}

bool Inventory::FindEquip(int equip_id, int equip_amount)
{
    int amount = 0;
    bool success = false;

    if(EquipmentDB::equipmentDatabase.count(equip_id) <= 0) return false;
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(amount >= equip_amount) {success = true; break;}
        if(!invSlot[i].isFull) continue;
        if(invSlot[i].equipment == NULL) continue;
        if(invSlot[i].equipment->equipment_id == equip_id) amount = amount + 1;
    }
    return success;
}

bool Inventory::RemoveItem(int item_id, int item_amount)
{
    bool success = false;
    int amount = 0;
    if(ItemDB::itemDatabase.count(item_id) <= 0) return false;

    if(FindItem(item_id, item_amount))
    {
        for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
        {
            if(amount >= item_amount) {success = true; break;}
            if(!invSlot[i].isFull) continue;
            if(invSlot[i].item == NULL) continue;
            if(invSlot[i].item->item_id == item_id)
            {
                if(amount + invSlot[i].item->currentStack > item_amount)
                {
                    invSlot[i].item->currentStack = invSlot[i].item->currentStack - (item_amount - amount);
                    amount = item_amount;
                    success = true;
                    break;
                }else
                {
                    amount = amount + invSlot[i].item->currentStack;
                    invSlot[i].item->currentStack = 0;
                }
            }
        }
    }
    return success;
}

bool Inventory::RemoveEquipment(int equip_id, int equip_amount)
{
    int amount = 0;
    bool success = false;

    if(EquipmentDB::equipmentDatabase.count(equip_id) <= 0) return false;
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if(amount >= equip_amount) {success = true; break;}
        if(!invSlot[i].isFull) continue;
        if(invSlot[i].equipment == NULL) continue;
        if(invSlot[i].equipment->equipment_id == equip_id)
        {
            invSlot[i].equipment->destroy();
            amount = amount + 1;
            invSlot[i].Reset();
        }
    }
    return success;
}

void Inventory::AddEquipmentToSlot(int slot_id, int equipment_id)
{
    EquipmentType equipTemp = EquipmentDB::equipmentDatabase[equipment_id];
    if(equipTemp.equipmentName.empty())
    {
        std::cerr << "Not found equip id: " << equipment_id << std::endl;
        return;
    }
    equipmentList.emplace_back(new Equipment(equipTemp.equipment_id, equipTemp.spriteName, equipTemp.equipmentTag, equipTemp.equipmentName, equipTemp.equipmentDescription,
                                            equipTemp.Strength, equipTemp.Dexterity, equipTemp.Intelligence,
                                            equipTemp.Vitality, equipTemp.Agility, equipTemp.buyPrice, equipTemp.sellPrice));
    invSlot[slot_id].AddEquipmentToSlot(equipmentList.back());
    std::cout << "Added " << equipTemp.equipmentName << " to the Inventory!" << std::endl;
}

void Inventory::AddItemToSlot(int slot_id, int item_id, int item_amount)
{
    ItemType itemTemp = ItemDB::itemDatabase[item_id];
    if(itemTemp.itemName.empty())
    {
        std::cerr << "Not found item id: " << item_id << std::endl;
        return;
    }

    itemList.emplace_back(new Item(itemTemp.item_id, itemTemp.spriteName,itemTemp.maxStack,itemTemp.itemTag,itemTemp.itemName, itemTemp.itemDescription, itemTemp.buyPrice, itemTemp.sellPrice, itemTemp.ItemFunc));
    itemList.back()->currentStack = itemList.back()->currentStack + item_amount - 1;
    invSlot[slot_id].AddItemToSlot(itemList.back());
    std::cout << "Added " << itemTemp.itemName << " to the Inventory!" << std::endl;
}

void Inventory::FindItemAtSlot(int slot_id, int* item_id, int* item_amount)
{
    if(!invSlot[slot_id].item)
    {
        *item_id = 0;
        *item_amount = 0;
    }else
    {
        *item_id = invSlot[slot_id].item->item_id;
        *item_amount = invSlot[slot_id].item->currentStack;
    }
}
void Inventory::FindEquipmentAtSlot(int slot_id, int* equipment_id)
{
    if(!invSlot[slot_id].equipment)
    {
        *equipment_id = 0;
    }else
    {
        *equipment_id = invSlot[slot_id].equipment->equipment_id;
    }
}

void Inventory::AddGold(int gold)
{
    this->gold += gold;
}

int Inventory::GetGold()
{
    return gold;
}
