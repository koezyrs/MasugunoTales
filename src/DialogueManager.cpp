#include "DialogueManager.h"

struct DialogueType
{
    std::string TITLE;
    std::string CONTENT;
    const char* REPLY1;
    const char* REPLY2;
    const char* REPLY3;
    const char* REPLY4;
    std::function<void()> FUNC1;
    std::function<void()> FUNC2;
    std::function<void()> FUNC3;
    std::function<void()> FUNC4;
    std::string FACEPATH;

    DialogueType(std::string title = "", std::string content = "", const char* reply1 = NULL, const char* reply2 = NULL,
                 const char* reply3 = NULL, const char* reply4 = NULL,
                 std::function<void()> funct1 = []{}, std::function<void()> funct2 = []{},
                 std::function<void()> funct3 = []{}, std::function<void()> funct4 = []{}, std::string facePath = "")
    : TITLE(title), CONTENT(content), REPLY1(reply1), REPLY2(reply2), REPLY3(reply3), REPLY4(reply4),
        FUNC1([this, funct1] {funct1();}), FUNC2([this, funct2] {funct2();}), FUNC3([this, funct3] {funct3();}), FUNC4([this, funct4] {funct4();}) , FACEPATH(facePath)
    {}
};
std::map<std::string, DialogueType> DialogueManager::dialogueList;

void DialogueManager::Play(std::string dialogueName)
{
    if(DialogueManager::dialogueList[dialogueName].CONTENT.empty())
    {
        std::cout << "Unable to find " << dialogueName << " conversation!"  << std::endl;
        return;
    }
    DialogueType context = DialogueManager::dialogueList[dialogueName];
    Game::gDialogue->setFace(context.FACEPATH.c_str());
    Game::gDialogue->setTitleLabel(context.TITLE.c_str());
    Game::gDialogue->setContentLabel(context.CONTENT.c_str());
    Game::gDialogue->setOption1(context.REPLY1, context.FUNC1);
    Game::gDialogue->setOption2(context.REPLY2, context.FUNC2);
    Game::gDialogue->setOption3(context.REPLY3, context.FUNC3);
    Game::gDialogue->setOption4(context.REPLY4, context.FUNC4);
    Game::gDialogue->showWindow();
}

void DialogueManager::LoadDialogue()
{
    dialogueList["Guild Master#25"] = DialogueType("Conversation with Aurez",
                                             "Your performance has been impressive thus far. We have more difficult tasks for you to undertake. Your next quest will be provided soon.",
                                             "*Updating",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");

    dialogueList["???#10"] = DialogueType("Conversation with ???",
                                             "Of course, here you go. *Hands over a pouch of gold coins and give you a common glove.",
                                             "1. Alright, Thank you for the business. ",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#9"] = DialogueType("Conversation with ???",
                                             "Mysterious Man examines the goblin tears\nImpressive. These are of the highest quality. You have done well.",
                                             "1. Thank you. So, about the reward you promised?",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("???#10");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#8"] = DialogueType("Conversation with ???",
                                             "Excellent work. May I see them?",
                                             "1. Sure, here they are.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("???#9");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#7"] = DialogueType("Conversation with ???",
                                             "Ah, you have returned. Do you have the goblin tears that I requested?",
                                             "1. Yes, I was able to extract the substance from several goblins that I encountered.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("???#8");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#6"] = DialogueType("Conversation with ???",
                                             "You don't have 12 goblin tears. Try to get all of them..",
                                             "1. Alright",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#5"] = DialogueType("Conversation with ???",
                                             "Nothing to see here!",
                                             "*You go away",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#4"] = DialogueType("Conversation with ???",
                                             "Excellent. Please do not hesitate to bring them to me if you find any. I will reward you generously for your efforts.",
                                             "1. Alright, I will keep that in mind. Thank you for your time.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gQuestLog->mVariable[4] = 1;
                                                 Game::gQuestLog->checkQuest(8);
                                                 Game::gQuestLog->giveQuest(9);
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#3"] = DialogueType("Conversation with ???",
                                             "It is not actual tears that I seek, but rather a rare substance that can be extracted from their bodies. It is said to be difficult to obtain, but I am willing to pay handsomely for it. Bring back 12 goblin tear my friend!",
                                             "1. I see. Well, I will keep an eye out for any goblins that might have what you're looking for.",
                                             NULL,
                                             "2. Well, I'm not interested anymore...",
                                             NULL,
                                             []{
                                                 Play("???#4");
                                             },
                                             []{},
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#2"] = DialogueType("Conversation with ???",
                                             "They are said to have magical properties and can be used in certain rituals. I am willing to pay a handsome sum for any that you may come across in your travels.",
                                             "1. Hmm, I see. Well, I have fought goblins before, but I have never seen them cry.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("???#3");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["???#1"] = DialogueType("Conversation with ???",
                                             "Yes, I am. I am in search of a rare item known as goblin tears.",
                                             "1. Goblin tears? I've never heard of such a thing. What are they used for?",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("???#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["Lv. ???"] = DialogueType("You approach mysterious journeyman ",
                                             "You said: Excuse me, sir. Are you looking for something?",
                                             "*The mysterious man reply",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 if(Game::gQuestLog->onGoingQuest[8] == true)
                                                 {
                                                     Play("???#1");
                                                 }else if(Game::gQuestLog->onGoingQuest[9] == true)
                                                 {
                                                    if(Game::gQuestLog->checkQuest(9)) Play("???#7");
                                                    else Play("???#6");
                                                 }else
                                                 {
                                                    Play("???#5");
                                                 }


                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-MysteryMan");
    dialogueList["Guild Master#24"] = DialogueType("Conversation with Aurez",
                                             "You haven't found him? Just try to search deep into the west forest!",
                                             "1. Ah, let me try again..",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#23"] = DialogueType("Conversation with Aurez",
                                             "Oh, you found him! Investigate him for more information..",
                                             "1. I got it Aurez!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#22"] = DialogueType("Conversation with Aurez",
                                             "Great job on the wolf fangs. But we have a new quest for you. A mysterious journeyman has been spotted in the forest to the east. We're not sure what he's doing there, but we need you to find him and report back.",
                                             "1. Oh, this is a real adventure to the west forest! I'will go right away!",
                                             "2. What if he attack me, I'm not gonna do it...",
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gQuestLog->giveQuest(8);
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#21"] = DialogueType("Conversation with Aurez",
                                             "You need 10 wolf's fangs to complete this quest. The wolves can be found in the west of the town. Be careful adventure!",
                                             "1. I'll be right back!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#20"] = DialogueType("Conversation with Aurez",
                                             "Good job on reaching level 7. But we have a problem with wolves in the forest. They've been attacking travelers and livestock alike. We need you to hunt them down and bring back 10 of their fangs. They can be found in the forest to the west of the town. Be careful, they're ferocious creatures.",
                                             "1. I accept the quest sir!",
                                             "2. This quest is too hard for me. Maybe I should get back to traning!",
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gQuestLog->giveQuest(7);
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#19"] = DialogueType("Conversation with Aurez",
                                             "Your level is too low at the moment! Advance to Lv. 7 and come back here adventurer!",
                                             "1. Oh, I will come back when I reach Lv 7.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#18"] = DialogueType("Conversation with Aurez",
                                             "Nice work on the green slimes. But you're going to need to be tougher if you want to survive out there. I want you to level up to level 7. Do whatever quests you need to, or simply go out and fight monsters until you reach the milestone.",
                                             "1. Oh, I will come back when I reach Lv 7.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gQuestLog->giveQuest(6);
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
     dialogueList["Morwag#3"] = DialogueType("Conversation with Morwag",
                                             "Well, I suppose I could offer you some advice. But don't expect any hand-holding or coddling. If you want to learn from me, you'll have to prove yourself worthy of my time and expertise. Come back here when you level 20!",
                                             "1. Thank you, Morwag. I won't let you down.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gQuestLog->mVariable[2] = 1;
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Morwag");
    dialogueList["Morwag#2"] = DialogueType("Conversation with Morwag",
                                             "I don't train anyone. I'm retired for a reason. What makes you think I would take on an apprentice?",
                                             "1. I understand that you're retired, but I'm just looking for some guidance. You have a lot of knowledge and experience, and I'm willing to learn from you in any way I can.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Morwag#3");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Morwag");
    dialogueList["Morwag Lv. 37"] = DialogueType("Conversation with Morwag",
                                             "(gruffly) What do you want?",
                                             "1. I'm an adventurer looking to improve my skills, and I heard that you're a retired warrior with a lot of experience. I was hoping you could teach me a thing or two.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Morwag#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Morwag");
    dialogueList["Irish#11"] = DialogueType("Conversation with Irish",
                                             "1. No problem. Just be careful out there, and don't let his gruff exterior discourage you. I have a feeling you could learn a lot from him.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{},
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#10"] = DialogueType("Conversation with Irish",
                                             "Just head towards the outskirts of town, there's a small tent near the forest. That's where he lives. But be warned, he's not the friendliest of people, and he's not easily impressed. You'll have to prove yourself if you want him to take you seriously.",
                                             "1. I understand. Thank you for the information, Irish.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#11");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#9"] = DialogueType("Conversation with Irish",
                                             "Well, he's a bit of a recluse these days, but he used to be one of the strongest warriors in the land. He's got a lot of experience and knowledge that he could pass on to someone like you.",
                                             "1. That sounds like just what I need. How do I go about finding him?",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#10");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#8"] = DialogueType("Conversation with Irish",
                                             "Actually, there's one that comes to mind. His name is Morwag, he's a retired warrior who used to be quite the force to be reckoned with. He's got a scar over his eye, hard to miss him.",
                                             "1. Oh can you tell me more about him?",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#9");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#6"] = DialogueType("Conversation with Irish",
                                             "Ah, I see. Well, good luck to you on your adventures. And if you ever need any help, don't hesitate to ask.",
                                             "1. Thank you, I appreciate it. It was nice meeting you, Irish.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#5"] = DialogueType("Conversation with Irish",
                                             "Thank you, I take my duties very seriously. But enough about me, what brings you to our town?",
                                             "1. I'm actually here to complete some quests and hopefully make a name for myself as an adventurer.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#6");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#4"] = DialogueType("Conversation with Irish",
                                             "There have been a few instances where I've had to use my training to diffuse tense situations. But I've always been able to handle them.",
                                             "1. It sounds like you're really good at your job.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#5");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#3"] = DialogueType("Conversation with Irish",
                                             "It's definitely a unique experience, being the only female guard. But I've always been good at fighting and protecting people, so it was a natural fit for me.",
                                             "1. That's impressive. Have you faced any particularly tough challenges while on guard duty?",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#4");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish#2"] = DialogueType("Conversation with Irish",
                                             "Of course, I'm Irish, the only female guard in town. What do you want to know?",
                                             "1. Well, I was curious about what it's like being a guard in this town.",
                                             "2. Is there anyone that is still living in the town but is hard to find?",
                                             "3. No, there is nothing *hehe.",
                                             NULL,
                                             []{
                                                Play("Irish#3");
                                             },
                                             []{
                                                 Play("Irish#8");
                                                },
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             "Face-Irish");
    dialogueList["Irish Lv. 12"] = DialogueType("Player approach Irish!",
                                             "You said: Hello there, I was wondering if I could ask you a few questions.",
                                             "* Irish reply",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Irish#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "");
    dialogueList["Athur#5"] = DialogueType("Conversation with Athur",
                                             "Suit yourself. Well, it was nice meeting you. If you have any more questions, don't hesitate to ask.",
                                             "* Shake Athur's hand and go exploring!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Athur");
    dialogueList["Athur#4"] = DialogueType("Conversation with Athur",
                                             "Just be respectful to the townsfolk, and they'll be respectful to you. Oh, and if you're interested in joining the guard, we're always looking for new recruits. You look like you could handle yourself in a fight.",
                                             "1. Thanks for the offer, but I think I'll stick to adventuring for now.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Athur#5");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Athur");
    dialogueList["Athur#3"] = DialogueType("Conversation with Athur",
                                             "That's the spirit. And if you see any suspicious activity, don't hesitate to report it to me or one of the other guards.",
                                             "1. Will do. Is there anything else I should know?",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Athur#4");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Athur");
    dialogueList["Athur#2"] = DialogueType("Conversation with Athur",
                                             "Hmm, well, this is generally a peaceful town. But as a guard, I have to be prepared for anything. There have been a few reports of goblin sightings near the outskirts of town, so you might want to be careful if you plan on venturing out there.",
                                             "1. Goblins, huh? I'll make sure to keep an eye out.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Athur#3");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Athur");
    dialogueList["Athur Lv. 17"] = DialogueType("Conversation with Athur",
                                             "Ah, welcome to our humble town. I'm Athur, one of the town guards. What do you want to know?",
                                             "1. Well, I was wondering if there's anything I should be aware of while I'm here.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Play("Athur#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Athur");
    dialogueList["July#4"] = DialogueType("Conversation with July",
                                             "No problem. And if you ever want to join us on an adventure, just let us know!",
                                             "1. Yeah, we're always up for a good quest. We'll see you around!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-July");
    dialogueList["July#3"] = DialogueType("Conversation with July",
                                             "And if you're looking for adventure, you should talk to the guild master. He's always looking for people to go on quests.",
                                             "1. Thanks for the information. It's good to know where everything is.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("July#4");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-July");
    dialogueList["Peeper#3"] = DialogueType("Conversation with Peeper",
                                             "Sure thing. The town is pretty small, but it has everything you need. There's a blacksmith where you can buy weapons and armor, a potion shop where you can buy healing items, and even a library where you can read up on the history of this world.",
                                             "*July also talk..",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("July#3");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Peeper");
    dialogueList["Peeper#2"] = DialogueType("Conversation with Peeper",
                                             "That's right. We've been exploring this world for a while now, and we know a lot of useful things. If you have any questions, don't hesitate to ask.",
                                             "1. Actually, I was hoping you could tell me a bit more about the town.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Peeper#3");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Peeper");
    dialogueList["July#2"] = DialogueType("Conversation with July",
                                             "Awesome! Welcome to our world. We're happy to help you out in any way we can.",
                                             "*Peeper also talk..",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Peeper#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-July");
    dialogueList["Peeper Lv. 4"] = DialogueType("Conversation with Peeper",
                                             "Nice to meet you I'm Peeper. What brings you here?",
                                             "*July also talk...",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("July#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Peeper");
    dialogueList["July Lv. 3"] = DialogueType("Conversation with July",
                                             "Nice to meet you I'm July. What brings you here?",
                                             "1. I'm new to this world, and I was told to come and meet you two.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("July#2");
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-July");
    dialogueList["Guild Master#17"] = DialogueType("Conversation with Aurez",
                                             "You haven't slayed 10 green slime yet! Keep going adventurer!",
                                             "1. Oh, I think I forgot to count again! I will continue then!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#16"] = DialogueType("Conversation with Aurez",
                                             "Good, come back when you finish, adventurer",
                                             "1. Okay, I got it!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#15"] = DialogueType("Conversation with Aurez",
                                             "You're doing great so far. Now it's time to take on some stronger foes. You need to defeat 10 green slimes in the forest.",
                                             "1. Wow, that sounds really fun! This is such an adventure.",
                                             "2. This is too tough, I will be back later.",
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gQuestLog->giveQuest(5);
                                                Play("Guild Master#16");
                                             },
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#14"] = DialogueType("Conversation with Aurez",
                                             "I have heard you didn't meet everybody yet! Just make sure you don't miss anyone adventurer!",
                                             "1. Oh, maybe there are someone I haven't talked to! *Quickly walk away.. ",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#13"] = DialogueType("Conversation with Aurez",
                                             "Don't worry, everyone here are very friendly, you should go meet July and Peeper, they are such good kids!",
                                             "1. Uhh..., alright let me give a try! ",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 QuestLog::giveQuest(4);
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#12"] = DialogueType("Conversation with Aurez",
                                             "You should go meet July and Peeper, they are such good kids!",
                                             "1. That sounds great. I'll go now! ",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 QuestLog::giveQuest(4);
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#11"] = DialogueType("Conversation with Aurez",
                                             "You're doing great. As an adventurer, it's important to establish good relationships with NPCs. Your next quest is to simply say hello to a some NPC in the town square, come back here when you feel like you have meet every body in the town!",
                                             "1. Alright, who shall I meet first? ",
                                             "2. I'm too shy to meet new people...",
                                             "3. I think I might go back to training, kill some slime.. maybe.",
                                             NULL,
                                             []{
                                                Play("Guild Master#12");
                                             },
                                             []{
                                                Play("Guild Master#13");
                                             },
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#10"] = DialogueType("Conversation with Aurez",
                                             "Did you forgot to buy a small HP potion from Ryn's store, adventurer?",
                                             "1. Ahh, I did forget to buy one. I will be back soon!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#9"] = DialogueType("Conversation with Aurez",
                                             "Excellent! This is a really simple quest, so see you later adventurer!",
                                             "1. See you later Aurez!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#8"] = DialogueType("Conversation with Aurez",
                                             "Excellent work. Your next task is to purchase a small HP potion from Ryn's shop, her shop is in front of the guild house. It will come in handy for future quests.!",
                                             "1. Wow, thanks Aurez!! Let's grab some potion!",
                                             "2. No, I will save some golds and buy those later!",
                                             NULL,
                                             NULL,
                                             []{
                                                 QuestLog::giveQuest(3);
                                                 Play("Guild Master#9");
                                                },
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#7"] = DialogueType("Conversation with Aurez",
                                             "You don't have enough slime phlegm my friend! Comeback here when you have 5 blue slime phlegms adventurer!",
                                             "1. Ahh damm, I thought this was enough! Be back soon sir!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");

    dialogueList["Guild Master#6"] = DialogueType("Conversation with Aurez",
                                             "You are very brave adventurer! You will get what you are deserved!",
                                             "1. I'm will come back soon, I promise!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");

    dialogueList["Guild Master#5"] = DialogueType("Conversation with Aurez",
                                             "Excellent work on your training. Now it's time to put your skills to the test. We have a problem with some blue slimes that have been attacking travelers on the road. We need you to hunt down and defeat 5 of them. Bring back their phlegm as proof of your success.",
                                             "1. That seems challenging, but nothing can stop me. I'm in sir!",
                                             "2. This quest is too hard for me, I will get stronger and come back later!",
                                             NULL,
                                             NULL,
                                             []{
                                                 QuestLog::giveQuest(2);
                                                 Play("Guild Master#6");
                                                },
                                             []{
                                                    Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#4"] = DialogueType("Conversation with Aurez",
                                             "You haven't defeated 10 dummies yet! Train harder adventurer!",
                                             "1. Oh, my bad. I will get back training!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#3"] = DialogueType("Conversation with Aurez",
                                             "Nice, come back to see me when you finish!",
                                             "1. Got it sir!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#2"] = DialogueType("Conversation with Aurez",
                                             " Ah, yes. Leiea is one of our most experienced adventurers. It's good to see she's helping out new arrivals. I'm the guild master, and I have plenty of tasks that need doing. But first, we need to see what you're capable of. Your quest is to hone your combat abilities by attacking 10 practice dummies.",
                                             "1. I'm ready, let's do it!",
                                             NULL,
                                             "2. I think I'm gonna take a look around a bit!",
                                             NULL,
                                             []{
                                                  QuestLog::giveQuest(1);
                                                  Play("Guild Master#3");
                                                },
                                             []{},
                                             []{
                                                Game::gDialogue->hideWindow();
                                             },
                                             []{},
                                             "Face-Aurez");
    dialogueList["Guild Master#1"] = DialogueType("Conversation with Aurez",
                                             "Hello adventurer! I'm Aurez - the guild master. What can I help you today!",
                                             "1. Hello, I was told to come see you by a green-haired adventurer named Leiea. She said you could help me get started with some quests.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Guild Master#2");
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Aurez");

    dialogueList["Leiea: Introduce#3"] = DialogueType("Conversation with Leiea",
                                             "Great! It's not far from here. Just head straight down this path until you reach the town gates. Once you're inside, the guild hall is on the left side of the main square. Just tell the guild master that Leiea sent you and he'll give you all the details. Good luck adventurer!",
                                             "1. Thank you so much, Leiea. I'll make sure to do my best on this quest.",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Leiea");
    dialogueList["Leiea: Introduce#2"] = DialogueType("Conversation with Leiea",
                                             " I'm glad you think so! There's so much to see and do here. The guild master in the nearby town is looking for adventurers to help with a quest. Would you be interested?",
                                             "1. Absolutely! I've always wanted to go on a real adventure.",
                                             "2. No I think I'm good.",
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Leiea: Introduce#3");
                                                },
                                             []{
                                                Game::gDialogue->hideWindow();
                                                },
                                             []{},
                                             []{},
                                             "Face-Leiea");

    dialogueList["Leiea: Introduce#1"] = DialogueType("Conversation with Leiea",
                                             "You're in Masuguno Land! This is a fantasy world , there are magic, and all sorts of creatures here. My name is Leiea!",
                                             "1. Hi Leiea!. I can't believe I'm in a fantasy world... this is incredible!",
                                             NULL,
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Leiea: Introduce#2");
                                                },
                                             []{},
                                             []{},
                                             []{},
                                             "Face-Leiea");

    dialogueList["Leiea Lv. 6"] = DialogueType("Conversation with Leiea",
                                             "Hello there! Are you lost?",
                                             "1. Yes, I think I am. I'm not from around here. What is this place?",
                                             "2. No, I think I know where I'm going!",
                                             NULL,
                                             NULL,
                                             []{
                                                 Play("Leiea: Introduce#1");
                                                },
                                             []{
                                                 Game::gDialogue->hideWindow();
                                                 },
                                             []{},
                                             []{},
                                             "Face-Leiea");
}

