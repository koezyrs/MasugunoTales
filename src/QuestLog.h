#pragma once
#ifndef QuestLog_h
#define QuestLog_h

#include <map>
#include "Window.h"

#include "Game.h"
#include "Actor.h"
#include "Inventory.h"
#include "DialogueManager.h"
#include "Database/QuestDB.h"

class QuestLog
{
public:
    QuestLog();
    ~QuestLog();
    static std::map<int,int> mVariable;
    static std::map<int,int> totalMonsterKilled;
    static std::map<int,bool> onGoingQuest;
    static std::map<int,bool> finishedQuest;

    static bool giveQuest(int quest_id);
    static void dropQuest(int quest_id);
    static bool checkQuest(int quest_id);

    static void GuildMasterGiveQuest();

};

#endif // QuestLog_h
