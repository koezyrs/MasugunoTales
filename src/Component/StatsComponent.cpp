#include "StatsComponent.h"
#include "../MapManager.h"

StatsComponent::StatsComponent(int _level, int _experience, int _experienceToNextLevel,int _strength, int _dexterity, int _intelligence,
                   int _vitality, int _agility, int _statsUsed, int _statsAvailable)
: Level(_level), Experience(_experience), ExperienceToNextLevel(_experienceToNextLevel), Strength(_strength),
Dexterity(_dexterity), Intelligence(_intelligence), Vitality(_vitality), Agility(_agility), StatsUsed(_statsUsed), StatsAvailable(_statsAvailable)
{
    Damage = _strength*2;
    Defense = _dexterity*0.5;
    MaxMana = _intelligence*3;
    MaxHealth = _vitality*5;
    AttackSpeed = _agility;
    Mana = MaxMana;
    Health = MaxHealth;
    Power = Strength*3+Dexterity*3+Intelligence*2+Vitality*2+Agility*0.1;
}

StatsComponent::~StatsComponent() {}

void StatsComponent::Update()
{
    Damage = Strength*2;
    Defense = Dexterity*0.5;
    MaxMana = Intelligence*3;
    MaxHealth = Vitality*5;
    AttackSpeed = Agility;
    Power = Strength*3+Dexterity*3+Intelligence*2+Vitality*2+Agility*5;

    if(Health <= 0) Health = 0;
    if(Mana <= 0) Mana = 0;
    if(Health >= MaxHealth) Health = MaxHealth;
    if(Mana >= MaxMana) Mana = MaxMana;

    if(Level >= MAX_LEVEL)
    {
        Level = MAX_LEVEL;
        Experience = ExperienceToNextLevel;
    }else{
        if(Experience >= ExperienceToNextLevel)
        {
            Experience = Experience - ExperienceToNextLevel;
            Level = Level + 1;
            ExperienceToNextLevel = ExperienceToNextLevel + ExperienceToNextLevel*NEXT_LEVEL_EXP_RATE;
            int rewardStatsForLevelUp = 3;
            StatsAvailable += rewardStatsForLevelUp;
        }
    }

    if(Health <= 0)
    {
        MapManager::LoadMap(2);
        Game::gPlayer->setPosition(16 * 32, 15 * 32);
        Game::gInventory->AddGold(-Game::gInventory->GetGold()*0.3);
        Health = MaxHealth * 0.5;
    }
}

void StatsComponent::ApplyDamage(int _damage)
{
    float LO = 0.5f;
    float HI = 1.5f;
    float D = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    int healthLose = (_damage - Defense) * D;

    if(healthLose <= 0) return;
    if(Health - healthLose <= 0) Health = 0;
    else Health -= healthLose;
}
