#pragma once
#ifndef ShopDB_h
#define ShopDB_h

#include <string>
#include <vector>
#include <map>

struct ShopType
{
    std::string shop_title;
    std::vector<int> itemList;
    std::vector<int> equipmentList;
    ShopType() {}
    ShopType(std::string _shop_title): shop_title(_shop_title) {}
    void AddItemID(int item_id)
    {
        itemList.push_back(item_id);
    }

    void AddEquipmentID(int equipment_id)
    {
        equipmentList.push_back(equipment_id);
    }

};

class ShopDB
{
public:
    static void LoadShopDatabase();
    static std::map<int, ShopType> shopDatabase;
};

#endif // ShopDB_h
