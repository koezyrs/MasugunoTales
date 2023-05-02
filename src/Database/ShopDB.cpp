#include "ShopDB.h"

std::map<int, ShopType> ShopDB::shopDatabase;

void ShopDB::LoadShopDatabase()
{
    // Shop 1
    shopDatabase[1] = ShopType("Ryn's Shop");
    shopDatabase[1].AddItemID(1);
    shopDatabase[1].AddItemID(3);
    shopDatabase[1].AddItemID(4);
    shopDatabase[1].AddItemID(5);
    shopDatabase[1].AddItemID(6);
    shopDatabase[1].AddItemID(7);
    shopDatabase[1].AddItemID(9);
    shopDatabase[1].AddItemID(8);
    shopDatabase[1].AddItemID(10);
    shopDatabase[1].AddItemID(11);
    shopDatabase[1].AddItemID(14);
    shopDatabase[1].AddItemID(12);
    shopDatabase[1].AddItemID(15);
    shopDatabase[1].AddItemID(13);
    shopDatabase[1].AddItemID(16);
    shopDatabase[1].AddItemID(17);
    shopDatabase[1].AddItemID(18);

    // Shop 2
    shopDatabase[2] = ShopType("Zeph's Shop");
    shopDatabase[2].AddEquipmentID(1);
    shopDatabase[2].AddEquipmentID(2);
    shopDatabase[2].AddEquipmentID(3);
    shopDatabase[2].AddEquipmentID(4);
    shopDatabase[2].AddEquipmentID(5);
    shopDatabase[2].AddEquipmentID(6);
    shopDatabase[2].AddEquipmentID(7);
    shopDatabase[2].AddEquipmentID(8);

    // Shop 3
    shopDatabase[3] = ShopType("Cephur's Shop");
    shopDatabase[3].AddEquipmentID(9);
    shopDatabase[3].AddEquipmentID(10);
    shopDatabase[3].AddEquipmentID(11);
    shopDatabase[3].AddEquipmentID(12);
    shopDatabase[3].AddEquipmentID(13);
    shopDatabase[3].AddEquipmentID(14);
    shopDatabase[3].AddEquipmentID(15);
    shopDatabase[3].AddEquipmentID(16);
    shopDatabase[3].AddEquipmentID(17);
    shopDatabase[3].AddEquipmentID(18);
    shopDatabase[3].AddEquipmentID(19);
    shopDatabase[3].AddEquipmentID(20);
    shopDatabase[3].AddEquipmentID(21);
    shopDatabase[3].AddEquipmentID(22);
    shopDatabase[3].AddEquipmentID(23);
    shopDatabase[3].AddEquipmentID(24);
    shopDatabase[3].AddEquipmentID(25);
    shopDatabase[3].AddEquipmentID(26);
    shopDatabase[3].AddEquipmentID(27);
}
