#include "ItemDB.h"

std::map<int, ItemType> ItemDB::itemDatabase;
void ItemDB::LoadItemDatabase()
{
    itemDatabase[20] = ItemType(
        20,                                          // id (Must match database)
        "Item-GoblinTear",                            // Item
        999,                                        // Max stack
        "Material",                                   // Tag
        "Goblin Tear - Material",                        // Name
        "Goblin tears are a rare and valuable substance that can be extracted from the eyes of goblins. The tears are often collected by adventurers or sold by those who have managed to obtain them. Goblin tears are a thick, viscous liquid that has a greenish tint to it. It is said to have healing properties and is often used as a potion ingredient by alchemists. .",
        999,
        20,
        []                                          // Use
        {
            Game::gInventory->AddItem(20);
        }
    );
    itemDatabase[19] = ItemType(
        19,                                          // id (Must match database)
        "Item-WolfFang",                            // Item
        999,                                        // Max stack
        "Material",                                   // Tag
        "Wolf Fang - Material",                        // Name
        "Sharp and deadly, these fangs are harvested from the jaws of ferocious wolves that roam the wilderness. They are prized for their razor-sharp edges and are often used by blacksmiths and crafters to make weapons and armor that can slice through even the toughest materials.",
        999,
        10,
        []                                          // Use
        {
            Game::gInventory->AddItem(19);
        }
    );
    itemDatabase[18] = ItemType(
        18,                                          // id (Must match database)
        "Item-TeleportWing",                            // Item
        999,                                        // Max stack
        "Gift",                                   // Tag
        "Teleport Wing - Common",                        // Name
        "A magical item imbued with the power to transport adventurers to distant lands and faraway realms. With a single wave of the Teleport Wing, the user is whisked away to their desired location, bypassing perilous obstacles and treacherous terrain.",
        50,
        20,
        []                                          // Use
        {
            Game::gInventory->AddItem(18);
        }
    );
    itemDatabase[17] = ItemType(
        17,                                          // id (Must match database)
        "Item-MysteryBox",                            // Item
        999,                                        // Max stack
        "Gift",                                   // Tag
        "Mystery Box - Common",                        // Name
        "Unlock the unknown and discover hidden treasures within. With its unpredictable contents, the Mystery Box promises excitement and the thrill of chance!",
        70,
        30,
        []                                          // Use
        {
            Game::gInventory->AddItem(17);
        }
    );
    itemDatabase[16] = ItemType(
        16,                                          // id (Must match database)
        "Item-GoldenKey",                            // Item
        999,                                        // Max stack
        "Key",                                   // Tag
        "Golden Key - Uncommon",                        // Name
        "A prestigious key crafted from pure gold. Unlock only the most valuable and elusive of cases and claim your place among the legends. Use to open golden cases!",
        20,
        8,
        []                                          // Use
        {
            Game::gInventory->AddItem(16);
        }
    );
    itemDatabase[15] = ItemType(
        15,                                          // id (Must match database)
        "Item-SilverKey",                            // Item
        999,                                        // Max stack
        "Key",                                   // Tag
        "Silver Key - Common",                        // Name
        "An elegant key made of gleaming silver. Unlock cases of equal or lesser value and discover untold riches. Use to open silver cases!",
        15,
        4,
        []                                          // Use
        {
            Game::gInventory->AddItem(15);
        }
    );
    itemDatabase[14] = ItemType(
        14,                                          // id (Must match database)
        "Item-BronzeKey",                            // Item
        999,                                        // Max stack
        "Key",                                   // Tag
        "Bronze Key - Common",                        // Name
        "A reliable tool for any adventurer seeking to unlock bronze cases, with intricate notches and sturdy construction. Use to open bronze cases!",
        10,
        2,
        []                                          // Use
        {
            Game::gInventory->AddItem(14);
        }
    );
    itemDatabase[13] = ItemType(
        13,                                          // id (Must match database)
        "Item-GoldenCase",                            // Item
        999,                                        // Max stack
        "Case",                                   // Tag
        "Golden Case - Uncommon",                        // Name
        "The golden gacha case(Prizes are reset every week) \nThis gacha case contains following items and equipments:\n * 50/85/140 gold\n * Big HP/MP/Synthetic Potion - Common x2\n * Standard Weapon/Gloves - Uncommon \n * Standard Necklace - Uncommon", // Description
        100,
        30,
        []                                          // Use
        {
            Game::gInventory->AddItem(13);
        }
    );
    itemDatabase[12] = ItemType(
        12,                                          // id (Must match database)
        "Item-SilverCase",                            // Item
        999,                                        // Max stack
        "Case",                                   // Tag
        "Silver Case - Common",                        // Name
        "The silver gacha case(Prizes are reset every week) \nThis gacha case contains following items and equipments:\n * 25/50/80 gold\n * Medium HP/MP/Synthetic Potion - Common x2\n * Beginner Weapon/Gloves - Common \n * Beginner Necklace - Common", // Description
        55,
        20,
        []                                          // Use
        {
            Game::gInventory->AddItem(12);
        }
    );
    itemDatabase[11] = ItemType(
        11,                                          // id (Must match database)
        "Item-BronzeCase",                            // Item
        999,                                        // Max stack
        "Case",                                   // Tag
        "Bronze Case - Common",                        // Name
        "The bronze gacha case(Prizes are reset every week) \nThis gacha case contains following items and equipments:\n * 15/25/50 gold\n * Small HP/MP/Synthetic Potion - Common x2\n * Beginner Helmet/Armo - Common \n * Beginner Ring/Cape - Common", // Description
        30,
        10,
        []                                          // Use
        {
            Game::gInventory->AddItem(11);
        }
    );

    itemDatabase[10] = ItemType(
        10,                                          // id (Must match database)
        "Item-BigSyntheticPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Big Synthetic Potion - Uncommon",                        // Name
        "A big synthetic potion that can heal you 50HP and restore 30MP per each!", // Description
        100,
        30,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 50;
            Game::gPlayer->mStats->Mana += 30;
        }
    );

    itemDatabase[9] = ItemType(
        9,                                          // id (Must match database)
        "Item-BigHPPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Big HP Potion - Uncommon",                        // Name
        "A big health potion that can heal you 50HP per each!", // Description
        50,
        15,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 50;
        }
    );
    itemDatabase[8] = ItemType(
        8,                                          // id (Must match database)
        "Item-BigMPPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Big MP Potion - Uncommon",                        // Name
        "A big mana potion that can heal you 30MP per each!", // Description
        50,
        15,
        []                                          // Use
        {
            Game::gPlayer->mStats->Mana += 30;
        }
    );
    itemDatabase[7] = ItemType(
        7,                                          // id (Must match database)
        "Item-MedSyntheticPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Medium Synthetic Potion - Common",                        // Name
        "A medium health potion that can heal you 20 HP and restore 10 MP per each!", // Description
        40,
        10,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 20;
            Game::gPlayer->mStats->Mana += 10;
        }
    );

    itemDatabase[6] = ItemType(
        6,                                          // id (Must match database)
        "Item-MedMPPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Medium MP Potion - Common",                        // Name
        "A medium mana potion that can heal you 10MP per each!", // Description
        20,
        5,
        []                                          // Use
        {
            Game::gPlayer->mStats->Mana += 10;
        }
    );
    itemDatabase[5] = ItemType(
        5,                                          // id (Must match database)
        "Item-MedHPPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Medium HP Potion - Common",                        // Name
        "A medium health potion that can heal you 20HP per each!", // Description
        20,
        5,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 20;
        }
    );

    itemDatabase[4] = ItemType(
        4,                                          // id (Must match database)
        "Item-SyntheticPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Small Synthetic Potion - Common",                       // Name
        "A synthetic potion that can restore 10 HP and 5 MP per each!", // Description
        20,
        4,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 10;
            Game::gPlayer->mStats->Mana += 5;
        }
    );

    itemDatabase[3] = ItemType(
        3,                                          // id (Must match database)
        "Item-MPPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Small MP Potion - Common",                       // Name
        "A small mana potion that can restore 5 MP per each!", // Description
        10,
        2,
        []                                          // Use
        {
            Game::gPlayer->mStats->Mana += 5;
        }
    );
    itemDatabase[2] = ItemType(
        2,                                          // id (Must match database)
        "Item-BlueSlimePhlegms",                    // Item
        999,                                        // Max stack
        "Quest Item",                               // Tag
        "Blue Phlegms - Common",                            // Name
        "Material Item \n A phlegm that drops when defeating a blue slime. \n (Use for quest and crafting)", // Description
        999,
        2,
        []                                          // Use
        {
            // Can not be comsume
            Game::gInventory->AddItem(2);
        }
    );
    itemDatabase[1] = ItemType(
        1,                                          // id (Must match database)
        "Item-HPPotion",                            // Item
        999,                                        // Max stack
        "Potion",                                   // Tag
        "Small HP Potion - Common",                        // Name
        "A small health potion that can heal you 10HP per each!", // Description
        10,
        2,
        []                                          // Use
        {
            Game::gPlayer->mStats->Health += 10;
        }
    );
}

