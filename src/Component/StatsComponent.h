#pragma once
#ifndef StatsComponent_h
#define StatsComponent_h

#include <algorithm>
#include "../Settings.h"

class StatsComponent
{
public:
    StatsComponent(int _level, int _experience, int _experienceToNextLevel,int _strength, int _dexterity, int _intelligence,
                   int _vitality, int _agility, int _statsUsed, int _statsAvailable);
    ~StatsComponent();
    void Update();
    void ApplyDamage(int _damage);

    int Level = 0;
    int Experience = 0;
    int ExperienceToNextLevel = 0;

    int Health = 0;
    int MaxHealth = 0;
    int Mana = 0;
    int MaxMana = 0;
    int Damage = 0;
    int Defense = 0;
    int AttackSpeed = 0;

    int Strength = 0;
    int Dexterity = 0;
    int Intelligence = 0;
    int Vitality = 0;
    int Agility = 0;

    int StatsUsed = 0;
    int StatsAvailable = 0;

    int Power = 0;
};

#endif // StatsComponent_h
