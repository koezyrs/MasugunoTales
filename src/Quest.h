#pragma once
#ifndef Quest_h
#define Quest_h

#include <string>

class Quest
{
public:
    Quest();
    Quest(int _id, std::string name, std::string desc, int variable_id, int variable_amount, int item_id, int item_amount,
          int equip_id, int equip_amount, int enemy_id, int enemy_amount, int reward_exp, int reward_gold,
          int reward_item_id, int reward_item_amount, int reward_equip_id, int reward_equip_amount, bool repeat);
    ~Quest();
    int id;
    std::string name;
    std::string desc;
    // Requirement for finishing the quest
    int variable_id;
    int variable_amount;
    int item_id;
    int item_amount;
    int equip_id;
    int equip_amount;
    int enemy_id;
    int enemy_amount;
    // Reward
    int reward_exp;
    int reward_gold;
    int reward_item_id;
    int reward_item_amount;
    int reward_equip_id;
    int reward_equip_amount;

    // Repeatable ?
    bool repeat;
};

#endif // Quest_h
