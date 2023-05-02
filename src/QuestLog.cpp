#include "QuestLog.h"
std::map<int,int> QuestLog::mVariable;
std::map<int,int> QuestLog::totalMonsterKilled;
std::map<int,bool> QuestLog::onGoingQuest;
std::map<int,bool> QuestLog::finishedQuest;

QuestLog::QuestLog()
{

}

QuestLog::~QuestLog()
{

}

bool QuestLog::giveQuest(int quest_id)
{

    if(QuestDB::questDatabase.count(quest_id) <= 0)
    {
        std::cerr << "Can not found quest id:" << quest_id << std::endl;
        return false;
    }

    Quest quest = QuestDB::questDatabase[quest_id];
    if((finishedQuest.count(quest_id) > 0) && !quest.repeat)
    {
        std::cerr << "Quest was completed! Can not take again!" << std::endl;
        return false;
    }
    if(onGoingQuest.count(quest_id) > 0)
    {
        std::cerr << "Quest has already being accepted!" << std::endl;
        return false;
    }

    onGoingQuest[quest_id] = true;
    if(totalMonsterKilled.count(quest.enemy_id) <= 0) totalMonsterKilled[quest.enemy_id] = 0;
    std::cerr << "Quest "<< quest.name << " was given!" << std::endl;
    return true;
}

void QuestLog::dropQuest(int quest_id)
{
    Quest quest = QuestDB::questDatabase[quest_id];
}

bool QuestLog::checkQuest(int quest_id)
{
    if(QuestDB::questDatabase.count(quest_id) <= 0)
    {
        std::cerr << "Can not found quest id:" << quest_id << std::endl;
        return false;
    }

    if(onGoingQuest.count(quest_id) <= 0)
    {
        std::cerr << "You haven't claim the quest yet!" << std::endl;
        return false;
    }

    bool success = true;
    Quest quest = QuestDB::questDatabase[quest_id];

    if((mVariable[quest.variable_id] < quest.variable_amount) && (quest.variable_id > 0))
    {
        std::cerr << "Doesn't match variable requirements!" << std::endl;
        success = false;
    }

    if(quest.item_id > 0)
    {
        bool tmp = success;
        success = Game::gInventory->FindItem(quest.item_id, quest.item_amount);
        if(!success && tmp) std::cerr << "Doesn't match item requirements!" << std::endl;
    }
    if(quest.equip_id > 0)
    {
        bool tmp = success;
        success = Game::gInventory->FindEquip(quest.equip_id, quest.equip_amount);
        if(!success && tmp) std::cerr << "Doesn't match equipment requirements!" << std::endl;
    }

    if((totalMonsterKilled[quest.enemy_id] < quest.enemy_amount) && (quest.enemy_id > 0))
    {
        success = false;
        std::cerr << "Doesn't match monster requirements!" << std::endl;
    }

    if(success)
    {
        Game::gPlayer->mStats->Experience += quest.reward_exp;
        Game::gInventory->AddGold(quest.reward_gold);
        for(int i = 1; i <= quest.reward_item_amount; i++) Game::gInventory->AddItem(quest.reward_item_id);
        for(int i = 1; i <= quest.reward_equip_amount; i++) Game::gInventory->AddEquipment(quest.reward_equip_id);
        Game::gInventory->RemoveItem(quest.item_id, quest.item_amount);
        Game::gInventory->RemoveEquipment(quest.equip_id, quest.equip_amount);
        totalMonsterKilled[quest.enemy_id] = 0;
        onGoingQuest[quest_id] = false;
        if(!quest.repeat) finishedQuest[quest_id] = true;
        std::cerr << "Finished quest and received reward!" << std::endl;
    }
    return success;
}

void QuestLog::GuildMasterGiveQuest()
{
    // Quest 9
    if(finishedQuest.count(9) > 0)
    {
        DialogueManager::Play("Guild Master#25");
        return;
    }

    if(onGoingQuest.count(9) > 0)
    {
        DialogueManager::Play("Guild Master#23");
        return;
    }

    // Quest 8
    if(finishedQuest.count(8) > 0)
    {
        DialogueManager::Play("Guild Master#23");
        return;
    }

    if(onGoingQuest.count(8) > 0)
    {
        if(mVariable[4] == 1) DialogueManager::Play("Guild Master#23");
        else DialogueManager::Play("Guild Master#24");
        return;
    }
    // Quest 7
    if(finishedQuest.count(7) > 0)
    {
        DialogueManager::Play("Guild Master#22"); // Give quest 8
        return;
    }

    if(onGoingQuest.count(7) > 0)
    {
        if(checkQuest(7)) DialogueManager::Play("Guild Master#22"); // Give quest 8
        else DialogueManager::Play("Guild Master#21");              // Not finish quest 7
        return;
    }
    // Quest 6
    if(finishedQuest.count(6) > 0)
    {
        DialogueManager::Play("Guild Master#20"); // Give quest 7
        return;
    }

    if(onGoingQuest.count(6) > 0)
    {
        if(Game::gPlayer->mStats->Level >= 7) mVariable[3] = 1;
        if(checkQuest(6)) DialogueManager::Play("Guild Master#20"); // Give quest 7
        else DialogueManager::Play("Guild Master#19");              // Not finish quest 6
        return;
    }
    // Quest 5
    if(finishedQuest.count(5) > 0)
    {
        DialogueManager::Play("Guild Master#18"); // Give quest 6
        return;
    }

    if(onGoingQuest.count(5) > 0)
    {
        if(Game::gPlayer->mStats->Level == 7) mVariable[3] = 1;
        if(checkQuest(5)) DialogueManager::Play("Guild Master#18"); // Give quest 6
        else DialogueManager::Play("Guild Master#17");              // Not finish quest 5
        return;
    }
    // Quest 4
    if(finishedQuest.count(4) > 0)
    {
        DialogueManager::Play("Guild Master#15"); // Give quest 5
        return;
    }

    if(onGoingQuest.count(4) > 0)
    {
        if(checkQuest(4)) DialogueManager::Play("Guild Master#15"); // Give quest 5
        else DialogueManager::Play("Guild Master#14");              // Not finish quest 4
        return;
    }
    // Quest 3
    if(finishedQuest.count(3) > 0)
    {
        DialogueManager::Play("Guild Master#11");
        return;
    }

    if(onGoingQuest.count(3) > 0)
    {
        if(checkQuest(3)) DialogueManager::Play("Guild Master#11");
        else DialogueManager::Play("Guild Master#10");
        return;
    }
    // Quest 2
    if(finishedQuest.count(2) > 0)
    {
        DialogueManager::Play("Guild Master#8");
        return;
    }

    if(onGoingQuest.count(2) > 0)
    {
        if(checkQuest(2)) DialogueManager::Play("Guild Master#8");
        else DialogueManager::Play("Guild Master#7");
        return;
    }

    // Quest 1
    if(finishedQuest.count(1) > 0)
    {
        DialogueManager::Play("Guild Master#5"); // Give Quest 2
        return;
    }

    if(onGoingQuest.count(1) > 0)
    {
        if(checkQuest(1)) DialogueManager::Play("Guild Master#5"); // Give Quest 2
        else DialogueManager::Play("Guild Master#4");
        return;
    }

    // Introduce
    DialogueManager::Play("Guild Master#1");

}
