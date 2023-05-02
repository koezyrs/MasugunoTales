#include "EquipmentDB.h"

std::map<int, EquipmentType> EquipmentDB::equipmentDatabase;

void EquipmentDB::LoadEquipmentDatabase()
{
    equipmentDatabase[27] = EquipmentType(
        27,                      // id
        "Equip-RareShoes",  // Sprite Database
        SHOES,                 // Equipment Tag
        "Red's Shoes - Rare",      // Equipment Name
        "??? \nVitality: 7 \nAgility: 38",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        7,                      // Vit
        38,                      // Agi
        100,                     // Buy Price
        56                       // Sell Price
    );
    equipmentDatabase[26] = EquipmentType(
        26,                      // id
        "Equip-UncommonShoes",  // Sprite Database
        SHOES,                 // Equipment Tag
        "Kana's Shoes - Uncommon",      // Equipment Name
        "??? \nVitality: 5 \nAgility: 20",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        5,                      // Vit
        20,                      // Agi
        75,                     // Buy Price
        45                       // Sell Price
    );
    equipmentDatabase[25] = EquipmentType(
        25,                      // id
        "Equip-CommonShoes",  // Sprite Database
        SHOES,                 // Equipment Tag
        "Common Shoes - Common",      // Equipment Name
        "Just a common shoes. \nVitality: 3 \nAgility: 10",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        3,                      // Vit
        10,                      // Agi
        50,                     // Buy Price
        20                       // Sell Price
    );
    equipmentDatabase[24] = EquipmentType(
        24,                      // id
        "Equip-BeginnerShoes",  // Sprite Database
        SHOES,                 // Equipment Tag
        "Beginner Shoes - Beginner",      // Equipment Name
        "Shoes for beginner adventurers. \nVitality: 2 \nAgility: 5",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        2,                      // Vit
        5,                      // Agi
        35,                     // Buy Price
        15                       // Sell Price
    );
    equipmentDatabase[23] = EquipmentType(
        23,                      // id
        "Equip-UncommonGlove",  // Sprite Database
        GLOVE,                 // Equipment Tag
        "Hiro's Gloves - Uncommom",      // Equipment Name
        "This gloves were collected from a warrior named Hiro. \nAgility: 50",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        0,                      // Vit
        50,                      // Agi
        70,                     // Buy Price
        30                       // Sell Price
    );
    equipmentDatabase[22] = EquipmentType(
        22,                      // id
        "Equip-CommonGlove",  // Sprite Database
        GLOVE,                 // Equipment Tag
        "Fighter Gloves - Common",      // Equipment Name
        "Just a common gloves \nAgility: 20",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        0,                      // Vit
        20,                      // Agi
        50,                     // Buy Price
        15                       // Sell Price
    );
    equipmentDatabase[21] = EquipmentType(
        21,                      // id
        "Equip-BeginnerGloves",  // Sprite Database
        GLOVE,                 // Equipment Tag
        "Beginner Gloves - Beginner",      // Equipment Name
        "Just a beginner gloves \nAgility: 5",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        0,                      // Vit
        5,                      // Agi
        25,                     // Buy Price
        7                       // Sell Price
    );
    equipmentDatabase[20] = EquipmentType(
        20,                      // id
        "Equip-Rare2Armor",  // Sprite Database
        ARMOR,                 // Equipment Tag
        "Alaek's Armor - Rare",      // Equipment Name
        "??? \nDexterity: 7\nVitality: 0",
        0,                      // Strength
        7,                      // Dex
        0,                      // Int
        0,                      // Vit
        0,                      // Agi
        100,                     // Buy Price
        50                       // Sell Price
    );
    equipmentDatabase[19] = EquipmentType(
        19,                      // id
        "Equip-RareArmor",  // Sprite Database
        ARMOR,                 // Equipment Tag
        "Asahi's Armor - Rare",      // Equipment Name
        "I like this armor most xD - KoeZyrs! \nDexterity: 5\nVitality: 10",
        0,                      // Strength
        5,                      // Dex
        0,                      // Int
        10,                      // Vit
        0,                      // Agi
        96,                     // Buy Price
        45                       // Sell Price
    );
    equipmentDatabase[18] = EquipmentType(
        18,                      // id
        "Equip-UncommonArmor",  // Sprite Database
        ARMOR,                 // Equipment Tag
        "Great Armor - Uncommon",      // Equipment Name
        "A uncommon armor! \nDexterity: 3\nVitality: 5",
        0,                      // Strength
        3,                      // Dex
        0,                      // Int
        5,                      // Vit
        0,                      // Agi
        70,                     // Buy Price
        29                       // Sell Price
    );
    equipmentDatabase[17] = EquipmentType(
        17,                      // id
        "Equip-CommonArmor",  // Sprite Database
        ARMOR,                 // Equipment Tag
        "Cool Armor - Common",      // Equipment Name
        "Just a common armor! \nDexterity: 2\nVitality: 4",
        0,                      // Strength
        2,                      // Dex
        0,                      // Int
        4,                      // Vit
        0,                      // Agi
        50,                     // Buy Price
        10                       // Sell Price
    );
    equipmentDatabase[16] = EquipmentType(
        16,                      // id
        "Equip-BeginnerArmor",  // Sprite Database
        ARMOR,                 // Equipment Tag
        "BeginnerArmor - Beginner",      // Equipment Name
        "Just a beginner armor! \nDexterity: 1\nVitality: 2",
        0,                      // Strength
        1,                      // Dex
        0,                      // Int
        2,                      // Vit
        0,                      // Agi
        24,                     // Buy Price
        2                       // Sell Price
    );
    equipmentDatabase[15] = EquipmentType(
        15,                      // id
        "Equip-Rare2Helmet",  // Sprite Database
        HELMET,                 // Equipment Tag
        "Fiora's Helmet - Rare",      // Equipment Name
        "A unique helmet that bears the name of its legendary creator, Fiora the Master Smith. Its design is intricate and elegant, featuring delicate metalwork and ornate engravings that speak to its maker's unparalleled craftsmanship. \nVitality: 13",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        13,                      // Vit
        0,                      // Agi
        70,                     // Buy Price
        27                       // Sell Price
    );
    equipmentDatabase[14] = EquipmentType(
        14,                      // id
        "Equip-CommonHelmet",  // Sprite Database
        HELMET,                 // Equipment Tag
        "Normal Helmet - Common",      // Equipment Name
        "The Common Helmet is often used by soldiers and adventurers who need a reliable defense in combat, but do not have access to more specialized or powerful helmets. It can withstand most standard attacks and projectiles, and can even resist some weaker spells and enchantments. \nVitality: 6",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        6,                      // Vit
        0,                      // Agi
        40,                     // Buy Price
        10                      // Sell Price
    );
    equipmentDatabase[13] = EquipmentType(
        13,                      // id
        "Equip-BeginnerHelmet",  // Sprite Database
        HELMET,                 // Equipment Tag
        "Beginner Helmet - Beginner",      // Equipment Name
        "A basic helmet designed to provide basic protection to those starting out on their adventure. Its design is simple and practical, consisting of a metal shell that covers the top and sides of the head, with leather straps to hold it in place. \nVitality: 2",
        0,                      // Strength
        0,                      // Dex
        0,                      // Int
        2,                      // Vit
        0,                      // Agi
        20,                     // Buy Price
        5                       // Sell Price
    );
    equipmentDatabase[12] = EquipmentType(
        12,                      // id
        "Equip-UncommonShield",  // Sprite Database
        SHIELD,                 // Equipment Tag
        "Red Knight - Uncommon",      // Equipment Name
        "A shield that stands out from the rest with its unique design and special abilities. Its appearance may vary widely, from intricately engraved metal plates to exotic materials and rare gems. \nDexterity: 10",
        0,                      // Strength
        10,                      // Dex
        0,                      // Int
        0,                      // Vit
        0,                      // Agi
        65,                     // Buy Price
        20                       // Sell Price
    );
    equipmentDatabase[11] = EquipmentType(
        11,                      // id
        "Equip-Common2Shield",  // Sprite Database
        SHIELD,                 // Equipment Tag
        "Metal Shield - Common",      // Equipment Name
        "A superior shield that offers superior protection against both physical and magical attacks. Its design features heavy metal plating that can withstand even the strongest blows and spells. \nDexterity: 7",
        0,                      // Strength
        7,                      // Dex
        0,                      // Int
        0,                      // Vit
        0,                      // Agi
        35,                     // Buy Price
        10                       // Sell Price
    );
    equipmentDatabase[10] = EquipmentType(
        10,                      // id
        "Equip-CommonShield",  // Sprite Database
        SHIELD,                 // Equipment Tag
        "Wooden Shield - Common",      // Equipment Name
        "A reliable and widely-used shield that provides decent protection against physical and magical attacks. Its design varies depending on the region and culture, but it often features sturdy metal plating and a reinforced wooden core. \nDexterity: 6",
        0,                      // Strength
        6,                      // Dex
        0,                      // Int
        0,                      // Vit
        0,                      // Agi
        30,                     // Buy Price
        8                       // Sell Price
    );
    equipmentDatabase[9] = EquipmentType(
        9,                      // id
        "Equip-BeginnerShield",  // Sprite Database
        SHIELD,                 // Equipment Tag
        "Beginner Shield - Beginner",      // Equipment Name
        "A sturdy and reliable shield that offers basic protection to those starting out on their adventure. Its design is simple and straightforward, with a plain metal surface and a leather strap for easy carrying. \nDexterity: 4",
        0,                      // Strength
        4,                      // Dex
        0,                      // Int
        0,                      // Vit
        0,                      // Agi
        20,                     // Buy Price
        5                       // Sell Price
    );
    equipmentDatabase[8] = EquipmentType(
        8,                      // id
        "Equip-WaterStaff",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Water Staff - Rare",      // Equipment Name
        "A rare weapon that harnesses the fluid and ever-changing nature of water, the Water Staff is a weapon of great beauty and power. Its design features shimmering blue crystals that evoke the calming and refreshing nature of water, and its fluid movements mimic the ebb and flow of the tides. \nStrength: 8\nDexterity: 3\nIntelligence: 10\nVitality: 0\nAgility: 2",
        8,                      // Strength
        3,                      // Dex
        10,                      // Int
        0,                      // Vit
        2,                      // Agi
        100,                     // Buy Price
        50                       // Sell Price
    );
    equipmentDatabase[7] = EquipmentType(
        7,                      // id
        "Equip-WaterBlade",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Water Blade - Rare",      // Equipment Name
        "A weapon that harnesses the fluid and adaptable nature of water, the Water Blade is a versatile weapon that can change its form and strike with fluid precision. Its blade is as clear as crystal, reflecting the rippling light of the sun and the moon.  \nStrength: 8\nDexterity: 5\nIntelligence: 0\nVitality: 5\nAgility: 10",
        8,                      // Strength
        5,                      // Dex
        0,                      // Int
        5,                      // Vit
        20,                      // Agi
        100,                     // Buy Price
        50                       // Sell Price
    );
    equipmentDatabase[6] = EquipmentType(
        6,                      // id
        "Equip-FlameStaff",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Flame Staff - Rare",      // Equipment Name
        "A powerful magical weapon that harnesses the destructive power of fire, the Flame Staff is a force to be reckoned with in the hands of a skilled caster. Its intricate design and blazing red crystals speak to the raw power it possesses, and the flames that dance around the staff warn all who dare to face it. \nStrength: 8\nDexterity: 3\nIntelligence: 10\nVitality: 0\nAgility: 2",
        8,                      // Strength
        3,                      // Dex
        10,                      // Int
        0,                      // Vit
        2,                      // Agi
        100,                     // Buy Price
        50                       // Sell Price
    );
    equipmentDatabase[5] = EquipmentType(
        5,                      // id
        "Equip-FlameBlade",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Flame Blade - Rare",      // Equipment Name
        "A fiery weapon imbued with the power of flames, the Flame Blade is a formidable weapon that can turn the tide of battle. Its blade burns with intense heat, leaving a trail of fire in its wake, and can deal devastating damage to both flesh and armor. \nStrength: 8\nDexterity: 5\nIntelligence: 0\nVitality: 5\nAgility: 10",
        8,                      // Strength
        5,                      // Dex
        0,                      // Int
        5,                      // Vit
        20,                      // Agi
        100,                     // Buy Price
        50                       // Sell Price
    );
    equipmentDatabase[4] = EquipmentType(
        4,                      // id
        "Equip-LightSword",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Light Sword - Common",      // Equipment Name
        "A swift and graceful weapon that embodies the beauty and elegance of combat. With its lightweight and balanced design, the Light Sword allows for quick and precise strikes, making it ideal for those who value speed and agility in battle. \nStrength: 2\nDexterity: 2\nIntelligence: 0\nVitality: 1\nAgility: 10",
        2,                      // Strength
        2,                      // Dex
        0,                      // Int
        1,                      // Vit
        10,                      // Agi
        50,                     // Buy Price
        10                       // Sell Price
    );
    equipmentDatabase[3] = EquipmentType(
        3,                      // id
        "Equip-LongSword",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Long Sword - Common",      // Equipment Name
        "A powerful and versatile weapon, the Long Sword is the weapon of choice for many seasoned adventurers. \nStrength: 3\nDexterity: 1\nIntelligence: 0\nVitality: 3\nAgility: 5",
        3,                      // Strength
        1,                      // Dex
        0,                      // Int
        3,                      // Vit
        5,                      // Agi
        50,                     // Buy Price
        10                       // Sell Price
    );
    equipmentDatabase[2] = EquipmentType(
        2,                      // id
        "Equip-BeginnerStaff",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Beginner Staff - Beginner",      // Equipment Name
        "A reliable and lightweight weapon for novice adventurers, perfect for those starting out on their journey. \nStrength: 2\nDexterity: 0\nIntelligence: 5\nVitality: 2\nAgility: 15",
        2,                      // Strength
        0,                      // Dex
        5,                      // Int
        2,                      // Vit
        15,                      // Agi
        30,                      // Buy Price
        5                        // Sell Price
    );
    equipmentDatabase[1] = EquipmentType(
        1,                      // id
        "Equip-AssasinDagger",  // Sprite Database
        WEAPON,                 // Equipment Tag
        "Beginner Dagger - Beginner",      // Equipment Name
        "A nimble and versatile weapon for those who prefer speed and agility over brute force. \nStrength: 2\nDexterity: 0\nIntelligence: 0\nVitality: 2\nAgility: 20",
        2,                      // Strength
        0,                      // Dex
        0,                      // Int
        2,                      // Vit
        20,                      // Agi
        30,                      // Buy Price
        5                        // Sell Price
    );
}
