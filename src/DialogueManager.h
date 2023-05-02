#pragma once
#ifndef DialogueManager_h
#define DialogueManager_h

#include <map>
#include <string>
#include <vector>
#include <functional>

#include "Game.h"
#include "Actor.h"
#include "Dialogue.h"
#include "Inventory.h"
#include "Shop.h"
#include "Database/QuestDB.h"

struct DialogueType;
class DialogueManager
{
public:
    static void Play(std::string dialogueName);
    static void LoadDialogue();
    static std::map<std::string, DialogueType> dialogueList;
};

#endif // DialogueManager_h
