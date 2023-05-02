#include "SkillDB.h"

std::map<int , SkillType> SkillDB::skillDatabase;

void SkillDB::LoadSkillDatabase()
{
    skillDatabase[1] = SkillType(
        "Basic Attack",
        "Icon-Basick Attack",
        "Skill-Basic Attack",
        5,
        0,
        0,
        2000,
        46,
        1,
        1
    );
}
