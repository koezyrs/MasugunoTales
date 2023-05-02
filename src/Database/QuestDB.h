#pragma once
#ifndef QuestDB_h
#define QuestDB_h

#include <map>
#include "../Game.h"
#include "../Actor.h"
#include "../Quest.h"
#include "../Inventory.h"
#include "../QuestLog.h"

class QuestDB
{
public:
    static void LoadQuestDatabase();
    static std::map<int, Quest> questDatabase;
};

#endif // QuestDB_h
