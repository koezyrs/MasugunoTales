#pragma once
#ifndef MonsterDB_h
#define MonsterDB_h

#include <map>
#include <string>

struct MonsterType{
    int monster_id;
    int width, height;
    std::string monsterName;
    std::string monsterSprite;
    float damage, health, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;
    int exp_reward, gold_reward;
    int item_reward_id;
    float item_drop_percent;
    int equipment_reward_id;
    float equipment_drop_percent;
    bool freeze;
    MonsterType() {}
    MonsterType(int _monster_id, int _width, int _height, std::string _monsterName, std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                float _chaseSpeed, float _roamSpeed, float _attackRange, float _stopChaseRange, int _exp_reward, int _gold_reward,
                int _item_reward_id, float _item_drop_percent, int _equipment_reward_id, float _equipment_drop_percent, bool _freeze = false)
    : monster_id(_monster_id), width(_width), height(_height), monsterName(_monsterName), monsterSprite(_monsterSprite), damage(_damage), health(_health),
    attackSpeed(_attackSpeed), chaseSpeed(_chaseSpeed), roamSpeed(_roamSpeed), attackRange(_attackRange),
    stopChaseRange(_stopChaseRange), exp_reward(_exp_reward), gold_reward(_gold_reward), item_reward_id(_item_reward_id),
    item_drop_percent(_item_drop_percent), equipment_reward_id(_equipment_reward_id), equipment_drop_percent(_equipment_drop_percent), freeze(_freeze)
    {}
};

class MonsterDB
{
public:
    static void LoadMonsterDatabase();
    static std::map<int, MonsterType> monsterDatabase;
};

#endif // MonsterDB_h
