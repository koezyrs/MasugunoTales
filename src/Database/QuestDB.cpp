#include "QuestDB.h"

std::map<int, Quest> QuestDB::questDatabase;

void QuestDB::LoadQuestDatabase()
{
    questDatabase[9] = Quest(
        // Requirements
        9,                                  // Quest id (Must match database)
        "Collect 12 goblin tear!",    // Quest name
        "Collect 12 goblin tear in the west forest! ", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        20,                                  // Item id
        12,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        300,                                 // Exp
        30,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        22,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[8] = Quest(
        // Requirements
        8,                                  // Quest id (Must match database)
        "Find a mystery man in the forest!",    // Quest name
        "A mysterious journeyman has been spotted in the forest to the east. We're not sure what he's doing there, but we need you to find him and report back.", // Desc
        4,                                  // Var id
        1,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        300,                                 // Exp
        30,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[7] = Quest(
        // Requirements
        7,                                  // Quest id (Must match database)
        "Get 10 wolf fangs.",    // Quest name
        "Adventurer needs to 10 wolf fangs.", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        19,                                  // Item id
        10,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        1500,                                 // Exp
        70,                                  // Gold
        14,                                  // Reward item id
        1,                                  // Reward item amount
        16,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[6] = Quest(
        // Requirements
        6,                                  // Quest id (Must match database)
        "Get to Lv 7.",    // Quest name
        "Adventurer needs to get to Lv 10", // Desc
        3,                                  // Var id
        1,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        1000,                                 // Exp
        50,                                  // Gold
        5,                                  // Reward item id
        10,                                  // Reward item amount
        13,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[5] = Quest(
        // Requirements
        5,                                  // Quest id (Must match database)
        "Defeat 10 green slime",    // Quest name
        "Go to the east of the town, you will see some green slime!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        2,                                  // Enemy id
        10,                                  // Enemy amount
        // Reward
        150,                                 // Exp
        35,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        9,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[4] = Quest(
        // Requirements
        4,                                  // Quest id (Must match database)
        "Meet every one in the town!",    // Quest name
        "Go out and talk to everyone you see!", // Desc
        2,                                  // Var id
        1,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        50,                                 // Exp
        30,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        1,                                  // Reward equip id
        1,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[3] = Quest(
        // Requirements
        3,                                  // Quest id (Must match database)
        "Buy a small HP potion!",    // Quest name
        "Small HP Potion can be bought from Ryn's store!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        1,                                  // Item id
        1,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        10,                                 // Exp
        10,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[2] = Quest(
        // Requirements
        2,                                  // Quest id (Must match database)
        "Collect 5 blue slime phlegms!",    // Quest name
        "Slime phlegms can be collected through defeating the blue slime in the north of the town!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        2,                                  // Item id
        5,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        0,                                  // Enemy id
        0,                                  // Enemy amount
        // Reward
        50,                                 // Exp
        10,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );
    questDatabase[1] = Quest(
        // Requirements
        1,                                  // Quest id (Must match database)
        "Train with the dummies",           // Quest name
        "The dummies can be find at the gate of town! Defeat 10 of those!", // Desc
        0,                                  // Var id
        0,                                  // Var amount
        0,                                  // Item id
        0,                                  // Item amount
        0,                                  // Equip id
        0,                                  // Equip amount
        3,                                  // Enemy id
        10,                                  // Enemy amount
        // Reward
        30,                                 // Exp
        10,                                  // Gold
        0,                                  // Reward item id
        0,                                  // Reward item amount
        0,                                  // Reward equip id
        0,                                  // Reward equip amount
        false                               // Repeat
    );

}
