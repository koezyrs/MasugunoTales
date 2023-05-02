#pragma once
#ifndef ItemDB_h
#define ItemDB_h

#include <functional>
#include "../Game.h"
#include "../Actor.h"
#include "../Inventory.h"

struct ItemType{
    int item_id;
    std::string spriteName;
    int maxStack;
    const char* itemTag;
    std::string itemName;
    std::string itemDescription;
    int buyPrice, sellPrice;
    std::function<void()> ItemFunc;
    ItemType() {}
    ItemType(int _item_id, std::string _spriteName, int _maxStack, const char* _itemTag, std::string _itemName, std::string _itemDescription,int _buyPrice, int _sellPrice, std::function<void()> func)
    : item_id(_item_id), spriteName(_spriteName), maxStack(_maxStack), itemTag(_itemTag), itemName(_itemName), itemDescription(_itemDescription),buyPrice(_buyPrice), sellPrice(_sellPrice),
    ItemFunc([this,func] {func();})
    {}
};

class ItemDB
{
public:
    static void LoadItemDatabase();
    static std::map<int, ItemType> itemDatabase;
};

#endif // ItemDB_h
