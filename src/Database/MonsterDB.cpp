#include "MonsterDB.h"

std::map<int, MonsterType> MonsterDB::monsterDatabase;

//ID,   Width, Height ,Name, Sprite, Damage, Health, Attack Speed, Chase Speed, RoamSpeed, Attack Range, Stop Chase Range
// Exp , Gold, item_reward_id, item_drop_percent, equipment_reward_id, equipment_drop_percent;

void MonsterDB::LoadMonsterDatabase()
{
    monsterDatabase[3] = MonsterType(3, 32, 38, "Dummy", "Sprite-Dummy",
                                    0.0f, 15.0f, 10000.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                    0,0,0,0,0,0,true);
    monsterDatabase[1] = MonsterType(1, 32, 32, "Slime Lv.1", "Sprite-BlueSlime",
                                    10.0f, 30.0f, 3000.0f, 0.4f, 0.1f, 30.0f, 128.0f,
                                    15,5,2,0.65,0,0);
    monsterDatabase[2] = MonsterType(2, 32, 32, "Slime Lv.5", "Sprite-GreenSlime",
                                    17.0f, 100.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    25,10,0,0,0,0);
    monsterDatabase[4] = MonsterType(4, 32, 32, "Wolf Lv.9", "Sprite-Wolf",
                                    30.0f, 260.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    70,30,19,0.48,0,0);
    monsterDatabase[5] = MonsterType(5, 32, 32, "Goblin Lv.15", "Sprite-Goblin",
                                    55.0f, 300.0f, 1800.0f, 0.7f, 0.3f, 40.0f, 128.0f,
                                    300,50,20,0.4,0,0);
    monsterDatabase[6] = MonsterType(6, 32, 32, "Grasswyrm Lv.12", "Sprite-Grasswyrm",
                                    34.0f, 240.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    120,32,0,0,0,0);
    monsterDatabase[7] = MonsterType(7, 32, 32, "Carnivorous Petal Lv.10", "Sprite-CarnivorousPetal",
                                    31.0f, 245.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    100,30,0,0,0,0);
    monsterDatabase[8] = MonsterType(8, 32, 32, "Baconator Lv.20", "Sprite-Baconator",
                                    70.0f, 380.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    500,100,0,0,0,0);
    monsterDatabase[9] = MonsterType(9, 32, 32, "Bayou Behemoth.24", "Sprite-BayouBehemoth",
                                    88.0f, 420.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    1500,160,0,0,0,0);
    monsterDatabase[10] = MonsterType(10, 32, 32, "Minator Lv.25", "Sprite-Minator",
                                    91.0f, 480.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    1600,185,0,0,0,0);
    monsterDatabase[11] = MonsterType(11, 32, 32, "Nightwing Devastator Lv.27", "Sprite-NightwingDevastator",
                                    95.0f, 510.0f, 2000.0f, 0.4f, 0.2f, 40.0f, 128.0f,
                                    1800,230,0,0,0,0);
}
