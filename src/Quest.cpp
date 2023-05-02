#include "Quest.h"
Quest::Quest() {}
Quest::Quest(int _id, std::string name, std::string desc, int variable_id, int variable_amount, int item_id, int item_amount,
            int equip_id, int equip_amount, int enemy_id, int enemy_amount, int reward_exp, int reward_gold,
            int reward_item_id, int reward_item_amount, int reward_equip_id, int reward_equip_amount, bool repeat)
{
    this->id = _id;
    this->name = name;
    this->desc = desc;
    this->variable_id = variable_id;
    this->variable_amount = variable_amount;
    this->item_id = item_id;
    this->item_amount = item_amount;
    this->equip_id = equip_id;
    this->equip_amount = equip_amount;
    this->enemy_id = enemy_id;
    this->enemy_amount = enemy_amount;
    this->reward_exp = reward_exp;
    this->reward_gold = reward_gold;
    this->reward_item_id = reward_item_id;
    this->reward_item_amount = reward_item_amount;
    this->reward_equip_id = reward_equip_id;
    this->reward_equip_amount = reward_equip_amount;
    this->repeat = repeat;
}

Quest::~Quest() {}
