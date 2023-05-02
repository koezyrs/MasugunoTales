// System Include
#include <math.h>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Login/Login.h"
#include "Register/Register.h"
#include "TextureManager.h"
#include "MixerManager.h"
#include "Map.h"
#include "MapManager.h"
#include "Collision.h"
#include "Entity.h"
#include "Actor.h"
#include "Monster.h"
#include "Item.h"
#include "Equipment.h"

// GUI Include
#include "Window.h"
#include "Dialogue.h"
#include "DialogueManager.h"
#include "Inventory.h"
#include "CharacterInformation.h"
#include "HUD.h"
#include "Hotbar.h"
#include "QuestLog.h"
#include "Shop.h"
#include "Ranking.h"

// Database
#include "Database/MonsterDB.h"
#include "Database/SkillDB.h"
#include "Database/EquipmentDB.h"
#include "Database/ItemDB.h"
#include "Database/QuestDB.h"
#include "Database/ShopDB.h"

// Settings
#include "Settings.h"

SESSION_GAME Game::session;
MYSQL* Game::conn;
SDL_Event Game::event;
SDL_Renderer* Game::gRenderer;
SDL_Rect Game::gCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

std::shared_ptr<Map> Game::currentMap;
std::unique_ptr<Actor> Game::gPlayer;
std::unique_ptr<Dialogue> Game::gDialogue;
std::unique_ptr<Inventory> Game::gInventory;
std::unique_ptr<HUD> Game::gHUD;
std::unique_ptr<Hotbar> Game::gHotbar;
std::unique_ptr<CharacterInformation> Game::gCharacterInformation;
std::unique_ptr<QuestLog> Game::gQuestLog;
std::unique_ptr<Shop> Game::gShop;
std::unique_ptr<Ranking> Game::gRanking;

Game::Game() {
    session = INIT;
};

Game::~Game(){};

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        cout << "Unable to initialize SDL! SDL_Error: " << SDL_GetError() << endl;
        session = CLEAR;
        return;
    }

    if(IMG_Init(IMG_INIT_PNG) < 0){
        cout << "Unable to initialize IMG! IMG_Error: " << IMG_GetError() << endl;
        session = CLEAR;
        return;
    }

    if(TTF_Init() < 0){
        cout << "Unable to initialize TTF! TTF_Error: " << TTF_GetError() << endl;
        session = CLEAR;
        return;
    }

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0){
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        session = CLEAR;
        return;
    }

    // Create window
    gWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        cout << "Unable to create Window! SDL_Error: " << SDL_GetError() << endl;
        session = CLEAR;
        return;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL){
        cout << "Unable to create Renderer! SDL_Error: " << SDL_GetError() << endl;
        session = CLEAR;
        return;
    }
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    srand(time(0));

    session = LOAD_RESOURCES;
    return;
}

void Game::loadResources()
{
    // GUI
    TextureManager::LoadTexture("data files/graphics/gui/Login.png", "Login");
    TextureManager::LoadTexture("data files/graphics/gui/LoginButtonOut.png", "LoginButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/LoginButtonOver.png", "LoginButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/ExitButtonOut.png", "ExitButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/ExitButtonOver.png", "ExitButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/Register.png", "Register");
    TextureManager::LoadTexture("data files/graphics/gui/RegistButtonOut.png", "RegistButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/RegistButtonOver.png", "RegistButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/BackButtonOut.png", "BackButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/BackButtonOver.png", "BackButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/8.png", "CloseButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/9.png", "CloseButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/Dialogue.png", "Dialogue");
    TextureManager::LoadTexture("data files/graphics/gui/CharacterInformation.png", "CharacterInformation");
    TextureManager::LoadTexture("data files/graphics/gui/Hotbar.png", "Hotbar");
    TextureManager::LoadTexture("data files/graphics/gui/HUDBars.png", "HUDBars");
    TextureManager::LoadTexture("data files/graphics/gui/HUDBase.png", "HUDBase");
    TextureManager::LoadTexture("data files/graphics/gui/Inventory.png", "Inventory");
    TextureManager::LoadTexture("data files/graphics/gui/Quest.png", "Quest");
    TextureManager::LoadTexture("data files/graphics/gui/HPBar.png", "HPBar");
    TextureManager::LoadTexture("data files/graphics/gui/Target.png", "Target");
    TextureManager::LoadTexture("data files/graphics/gui/TargetHPBar.png", "TargetHPBar");
    TextureManager::LoadTexture("data files/graphics/gui/48.png", "AddButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/49.png", "AddButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/Shop.png", "Shop");
    TextureManager::LoadTexture("data files/graphics/gui/AcceptButtonOut.png", "AcceptButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/AcceptButtonOver.png", "AcceptButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/58.png", "BuyButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/56.png", "BuyButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/59.png", "SellButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/57.png", "SellButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/DescriptionBox.png", "DescriptionBox");
    TextureManager::LoadTexture("data files/graphics/gui/Ranking.png", "Ranking");
    TextureManager::LoadTexture("data files/graphics/gui/PowerButtonOut.png", "PowerButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/PowerButtonOver.png", "PowerButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/GoldButtonOut.png", "GoldButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/GoldButtonOver.png", "GoldButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/LevelButtonOut.png", "LevelButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/LevelButtonOver.png", "LevelButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/ItemButtonOut.png", "ItemButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/EquipButtonOut.png", "EquipButtonOut");
    TextureManager::LoadTexture("data files/graphics/gui/ItemButtonOver.png", "ItemButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/EquipButtonOver.png", "EquipButtonOver");
    TextureManager::LoadTexture("data files/graphics/gui/Howtoplay_1.png", "GuidePage1");
    TextureManager::LoadTexture("data files/graphics/gui/Howtoplay_2.png", "GuidePage2");

    // Map
    TextureManager::LoadTexture("data files/maps/map01.png", "Map01");
    TextureManager::LoadTexture("data files/maps/map01_above_player.png", "Map01_Overlay");
    TextureManager::LoadTexture("data files/maps/map02.png", "Map02");
    TextureManager::LoadTexture("data files/maps/map02_above_player.png", "Map02_Overlay");
    TextureManager::LoadTexture("data files/maps/map03.png", "Map03");
    TextureManager::LoadTexture("data files/maps/map03_above_player.png", "Map03_Overlay");
    TextureManager::LoadTexture("data files/maps/map04.png", "Map04");
    TextureManager::LoadTexture("data files/maps/map04_above_player.png", "Map04_Overlay");
    TextureManager::LoadTexture("data files/maps/map05.png", "Map05");

    // Sprite
    TextureManager::LoadTexture("data files/graphics/characters/Player.png", "Sprite-Player");
    TextureManager::LoadTexture("data files/graphics/characters/BossDragon.png", "Sprite-BossDragon");
    TextureManager::LoadTexture("data files/graphics/characters/Dummy.png", "Sprite-Dummy");
    TextureManager::LoadTexture("data files/graphics/characters/24.png", "Sprite-BlueSlime");
    TextureManager::LoadTexture("data files/graphics/characters/21.png", "Sprite-GreenSlime");
    TextureManager::LoadTexture("data files/graphics/characters/15.png", "Sprite-Leiea");
    TextureManager::LoadTexture("data files/graphics/characters/35.png", "Sprite-Aurez");
    TextureManager::LoadTexture("data files/graphics/characters/5.png", "Sprite-Ryn");
    TextureManager::LoadTexture("data files/graphics/characters/34.png", "Sprite-Zeph");
    TextureManager::LoadTexture("data files/graphics/characters/43.png", "Sprite-Cephur");
    TextureManager::LoadTexture("data files/graphics/characters/173.png", "Sprite-Athur");
    TextureManager::LoadTexture("data files/graphics/characters/8.png", "Sprite-July");
    TextureManager::LoadTexture("data files/graphics/characters/7.png", "Sprite-Peeper");
    TextureManager::LoadTexture("data files/graphics/characters/6.png", "Sprite-Irish");
    TextureManager::LoadTexture("data files/graphics/characters/4.png", "Sprite-Morwag");
    TextureManager::LoadTexture("data files/graphics/characters/14.png", "Sprite-Wolf");
    TextureManager::LoadTexture("data files/graphics/characters/58.png", "Sprite-MysteryMan");
    TextureManager::LoadTexture("data files/graphics/characters/124.png", "Sprite-Goblin");
    TextureManager::LoadTexture("data files/graphics/characters/137.png", "Sprite-Grasswyrm");
    TextureManager::LoadTexture("data files/graphics/characters/129.png", "Sprite-CarnivorousPetal");
    TextureManager::LoadTexture("data files/graphics/characters/122.png", "Sprite-Baconator");
    TextureManager::LoadTexture("data files/graphics/characters/106.png", "Sprite-Minator");
    TextureManager::LoadTexture("data files/graphics/characters/119.png", "Sprite-BayouBehemoth");
    TextureManager::LoadTexture("data files/graphics/characters/16.png", "Sprite-NightwingDevastator");

    // Faces
    TextureManager::LoadTexture("data files/graphics/faces/35.png", "Face-Aurez");
    TextureManager::LoadTexture("data files/graphics/faces/15.png", "Face-Leiea");
    TextureManager::LoadTexture("data files/graphics/faces/7.png", "Face-Peeper");
    TextureManager::LoadTexture("data files/graphics/faces/8.png", "Face-July");
    TextureManager::LoadTexture("data files/graphics/faces/173.png", "Face-Athur");
    TextureManager::LoadTexture("data files/graphics/faces/6.png", "Face-Irish");
    TextureManager::LoadTexture("data files/graphics/faces/4.png", "Face-Morwag");
    TextureManager::LoadTexture("data files/graphics/faces/58.png", "Face-MysteryMan");

    //Equipment
    TextureManager::LoadTexture("data files/graphics/items/2.png", "Equip-AssasinDagger");
    TextureManager::LoadTexture("data files/graphics/weapons/beginner_staff.png", "Equip-BeginnerStaff");
    TextureManager::LoadTexture("data files/graphics/weapons/long_sword.png", "Equip-LongSword");
    TextureManager::LoadTexture("data files/graphics/weapons/light_sword.png", "Equip-LightSword");
    TextureManager::LoadTexture("data files/graphics/weapons/flame_blade.png", "Equip-FlameBlade");
    TextureManager::LoadTexture("data files/graphics/weapons/flame_staff.png", "Equip-FlameStaff");
    TextureManager::LoadTexture("data files/graphics/weapons/water_blade.png", "Equip-WaterBlade");
    TextureManager::LoadTexture("data files/graphics/weapons/water_staff.png", "Equip-WaterStaff");

    TextureManager::LoadTexture("data files/graphics/shield/beginner_shield.png", "Equip-BeginnerShield");
    TextureManager::LoadTexture("data files/graphics/shield/common_shield.png", "Equip-CommonShield");
    TextureManager::LoadTexture("data files/graphics/shield/common2_shield.png", "Equip-Common2Shield");
    TextureManager::LoadTexture("data files/graphics/shield/uncommon_shield.png", "Equip-UncommonShield");

    TextureManager::LoadTexture("data files/graphics/helmet/beginner_helmet.png", "Equip-BeginnerHelmet");
    TextureManager::LoadTexture("data files/graphics/helmet/common_helmet.png", "Equip-CommonHelmet");
    TextureManager::LoadTexture("data files/graphics/helmet/rare2_helmet.png", "Equip-Rare2Helmet");

    TextureManager::LoadTexture("data files/graphics/armor/beginner_armor.png", "Equip-BeginnerArmor");
    TextureManager::LoadTexture("data files/graphics/armor/common_armor.png", "Equip-CommonArmor");
    TextureManager::LoadTexture("data files/graphics/armor/rare_armor.png", "Equip-RareArmor");
    TextureManager::LoadTexture("data files/graphics/armor/rare2_armor.png", "Equip-Rare2Armor");
    TextureManager::LoadTexture("data files/graphics/armor/uncommon_armor.png", "Equip-UncommonArmor");

    TextureManager::LoadTexture("data files/graphics/gloves/beginner_gloves.png", "Equip-BeginnerGloves");
    TextureManager::LoadTexture("data files/graphics/gloves/common_gloves.png", "Equip-CommonGlove");
    TextureManager::LoadTexture("data files/graphics/gloves/uncommon_gloves.png", "Equip-UncommonGlove");

    TextureManager::LoadTexture("data files/graphics/shoes/beginner_shoes.png", "Equip-BeginnerShoes");
    TextureManager::LoadTexture("data files/graphics/shoes/common_shoes.png", "Equip-CommonShoes");
    TextureManager::LoadTexture("data files/graphics/shoes/uncommon_shoes.png", "Equip-UncommonShoes");
    TextureManager::LoadTexture("data files/graphics/shoes/rare_shoes.png", "Equip-RareShoes");

    // Item
    TextureManager::LoadTexture("data files/graphics/items/14.png", "Item-HPPotion");
    TextureManager::LoadTexture("data files/graphics/items/BlueSlimePhlegms.png", "Item-BlueSlimePhlegms");
    TextureManager::LoadTexture("data files/graphics/items/12.png", "Item-MPPotion");
    TextureManager::LoadTexture("data files/graphics/items/13.png", "Item-SyntheticPotion");
    TextureManager::LoadTexture("data files/graphics/items/MediumHPPotion.png", "Item-MedHPPotion");
    TextureManager::LoadTexture("data files/graphics/items/MediumMPPotion.png", "Item-MedMPPotion");
    TextureManager::LoadTexture("data files/graphics/items/MediumPotion.png", "Item-MedSyntheticPotion");
    TextureManager::LoadTexture("data files/graphics/items/BigHPPotion.png", "Item-BigHPPotion");
    TextureManager::LoadTexture("data files/graphics/items/BigMPPotion.png", "Item-BigMPPotion");
    TextureManager::LoadTexture("data files/graphics/items/BigPotion.png", "Item-BigSyntheticPotion");
    TextureManager::LoadTexture("data files/graphics/items/bronze_case.png", "Item-BronzeCase");
    TextureManager::LoadTexture("data files/graphics/items/silver_case.png", "Item-SilverCase");
    TextureManager::LoadTexture("data files/graphics/items/golden_case.png", "Item-GoldenCase");
    TextureManager::LoadTexture("data files/graphics/items/Bronze_key.png", "Item-BronzeKey");
    TextureManager::LoadTexture("data files/graphics/items/Silver_key.png", "Item-SilverKey");
    TextureManager::LoadTexture("data files/graphics/items/Golden_key.png", "Item-GoldenKey");
    TextureManager::LoadTexture("data files/graphics/items/mystery_box.png", "Item-MysteryBox");
    TextureManager::LoadTexture("data files/graphics/items/Teleport_wing.png", "Item-TeleportWing");
    TextureManager::LoadTexture("data files/graphics/items/wolf_fang.png", "Item-WolfFang");
    TextureManager::LoadTexture("data files/graphics/items/goblin_tear.png", "Item-GoblinTear");

    // Skill
    TextureManager::LoadTexture("data files/graphics/animations/13.png", "Skill-Basic Attack");

    session = LOAD_MIX;;
}

void Game::loadMix()
{
    MixerManager::LoadMusic("data files/music/13 Ochakai.mp3", "Map01Music");
    MixerManager::LoadMusic("data files/music/18 Semarikuru Shuumatsu e.mp3", "Map02Music");
    MixerManager::LoadMusic("data files/music/04 Saihate.mp3", "Map03Music");
    MixerManager::LoadMusic("data files/music/16 Yuzurenai Mono.mp3", "Map04Music");
    MixerManager::LoadMusic("data files/music/23 Awakening.mp3", "Map05Music");
    session = LOAD_DATA;
}

void Game::loadData()
{
    // Load all game dialogue
    DialogueManager::LoadDialogue();

    // Load all monster types
    MonsterDB::LoadMonsterDatabase();

    // Load all skill types
    SkillDB::LoadSkillDatabase();

    // Load all item types
    ItemDB::LoadItemDatabase();

    // Load all equipment types
    EquipmentDB::LoadEquipmentDatabase();

    // Load all quest
    QuestDB::LoadQuestDatabase();

    // Load all shop
    ShopDB::LoadShopDatabase();

    // Load all map
    MapManager::LoadMapDatabase();

    loginPanel = new Login();
    registerPanel = new Register();
    session = LOGIN;
}

void Game::loginProcess()
{
    loginPanel->HandleEvent();
    loginPanel->Update();
    loginPanel->Render();
}

void Game::registProcess()
{
    registerPanel->HandleEvent();
    registerPanel->Update();
    registerPanel->Render();
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
        case SDL_QUIT:
            session = SAVE_DATA;
            break;
        default:
            break;
        }

        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Game::gDialogue->hideWindow();
                Game::gInventory->hideWindow();
                Game::gCharacterInformation->hideWindow();
                Game::gShop->hideWindow();
                Game::gRanking->hideWindow();
                break;
            case SDLK_i:
                Game::gInventory->Toggle();
                break;
            case SDLK_c:
                Game::gCharacterInformation->Toggle();
                break;
            default:
                break;
            }
        }
        return;
    }

}

void Game::update()
{
    // Update Game Object
    currentMap->Update();
    gHUD->Update();
    gHotbar->Update();
    if(!gDialogue->isHide()) gDialogue->Update();
    if(!gInventory->isHide()) gInventory->Update();
    if(!gCharacterInformation->isHide()) gCharacterInformation->Update();
    if(!gShop->isHide()) gShop->Update();
    if(!gRanking->isHide()) gRanking->Update();

    // Camera Update
    gCamera.x = gPlayer->getTransformComponent()->position.x - SCREEN_WIDTH / 2;
    gCamera.y = gPlayer->getTransformComponent()->position.y - SCREEN_HEIGHT / 2;
    if(gCamera.x < 0) gCamera.x = 0;
    if(gCamera.y < 0) gCamera.y = 0;
    if(gCamera.x >= gCamera.w) gCamera.x = gCamera.w;
    if(gCamera.y >= gCamera.h) gCamera.y = gCamera.h;
    if(gCamera.x + gCamera.w >= currentMap->getWidth()) gCamera.x = currentMap->getWidth() - gCamera.w;
    if(gCamera.y + gCamera.h >= currentMap->getHeight()) gCamera.y = currentMap->getHeight() - gCamera.h;
    return;
}

void Game::render()
{
    // Clear front buffer
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // Draw here
    currentMap->RenderBottomLayer();
    gPlayer->Render();
    currentMap->RenderUpperLayer();

    if(!gDialogue->isHide()) gDialogue->Render();
    if(!gInventory->isHide()) gInventory->Render();
    if(!gCharacterInformation->isHide()) gCharacterInformation->Render();
    if(!gShop->isHide()) gShop->Render();
    if(!gRanking->isHide()) gRanking->Render();
    gHUD->Render();
    gHotbar->Render();

    // Update screen
    SDL_RenderPresent(gRenderer);

    return;
}

void Game::saveData()
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    int l_actor_id = gPlayer->actor_id;
    std::string actor_id = std::to_string(l_actor_id);
    std::string qstr;
    int qstate;

    std::string level = to_string(gPlayer->mStats->Level);
    std::string experience = to_string(gPlayer->mStats->Experience);
    std::string experience_to_next_level = to_string(gPlayer->mStats->ExperienceToNextLevel);
    std::string strength = to_string(gPlayer->mStats->Strength);
    std::string dexterity = to_string(gPlayer->mStats->Dexterity);
    std::string intelligence = to_string(gPlayer->mStats->Intelligence);
    std::string vitality = to_string(gPlayer->mStats->Vitality);
    std::string agility = to_string(gPlayer->mStats->Agility);
    std::string stats_used = to_string(gPlayer->mStats->StatsUsed);
    std::string stats_available = to_string(gPlayer->mStats->StatsAvailable);
    std::string map_id = to_string(currentMap->id);
    std::string x = to_string(static_cast<int>(gPlayer->getTransformComponent()->position.x));
    std::string y = to_string(static_cast<int>(gPlayer->getTransformComponent()->position.y));
    std::string gold = to_string(gInventory->GetGold());
    std::string skin = "Player";

    // Update actor
    qstr = "";
    qstr += "UPDATE `actors` SET `level`='" + level;
    qstr += "',`experience`='" + experience;
    qstr += "',`experience_to_next_level`='" + experience_to_next_level;
    qstr += "',`strength`='" + strength;
    qstr += "',`dexterity`='" + dexterity;
    qstr += "',`intelligence`='" + intelligence;
    qstr += "',`vitality`='" + vitality;
    qstr += "',`agility`='" + agility;
    qstr += "',`stats_used`='" + stats_used;
    qstr += "',`stats_available`='" + stats_available;
    qstr += "',`map_id`='" + map_id;
    qstr += "',`x`='" + x;
    qstr += "',`y`='" + y;
    qstr += "',`gold`='" + gold;
    qstr += "',`skin`='" + skin;
    qstr += "' WHERE `id` = '" + actor_id + "'";

    qstate = mysql_query(conn, qstr.c_str());
    if(qstate)
    {
        std::cout << "Can not make query! (Can not save actor!)" << std::endl;
    }

    // Update inventory
    for(int i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        std::string slot_id = to_string(i);
        int equipment_id, item_id, item_amount;
        gInventory->FindEquipmentAtSlot(i, &equipment_id);
        gInventory->FindItemAtSlot(i, &item_id, &item_amount);
        qstr = "";
        qstr += "UPDATE `actor_inventory` SET `equipment_id`='" + std::to_string(equipment_id);
        qstr += "',`item_id`='" + std::to_string(item_id);
        qstr += "',`item_amount`='" + std::to_string(item_amount);
        qstr += "' WHERE `slot_id` ='" + slot_id;
        qstr += "' AND `actor_id` ='" + actor_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(qstate)
        {
            std::cout << "Can not make query! (Can not save actor inventory!)" << std::endl;
        }
    }

    // Update player CC's
    for(int i = 0; i < MAX_EQUIPMENT_SLOTS; i++)
    {
        std::string slot_id = to_string(i);
        int equipment_id;
        gCharacterInformation->FindEquipmentAtSlot(i, &equipment_id);
        qstr = "";
        qstr += "UPDATE `actor_character_information` SET `equipment_id`='" + std::to_string(equipment_id);
        qstr += "' WHERE `slot_id` ='" + slot_id;
        qstr += "' AND `actor_id` ='" + actor_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(qstate)
        {
            std::cout << "Can not make query! (Can not save actor CC's!)" << std::endl;
        }
    }

    // Update player variable
    for(auto& v : gQuestLog->mVariable)
    {
        std::string variable_id = std::to_string(v.first);
        std::string variable_value = std::to_string(v.second);
        qstr = "SELECT * FROM `actor_variable` WHERE `actor_id` = '" + actor_id + "' AND `variable_id` = '" + variable_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            // Exist variable
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                qstr = "UPDATE `actor_variable` SET `variable_value` = '" + variable_value;
                qstr += "' WHERE `actor_id` = '" + actor_id + "' AND `variable_id` = '" + variable_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor variable #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_variable(actor_id, variable_id, variable_value) ";
                qstr += "VALUES('" + actor_id + "','" + variable_id + "','" + variable_value + "')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor variable #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor variable #3!)" << std::endl;
        }
    }

    // Update player monster kills
    for(auto& k : gQuestLog->totalMonsterKilled)
    {
        std::string monster_id = std::to_string(k.first);
        std::string amount = std::to_string(k.second);
        qstr = "SELECT * FROM `actor_monster_kills` WHERE `actor_id` = '" + actor_id + "' AND `monster_id` = '" + monster_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                qstr = "UPDATE `actor_monster_kills` SET `amount` = '" + amount;
                qstr += "' WHERE `actor_id` = '" + actor_id + "' AND `monster_id` = '" + monster_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor monster_kills #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_monster_kills(actor_id, monster_id, amount) ";
                qstr += "VALUES('" + actor_id + "','" + monster_id + "','" + amount + "')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor monster_kills #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor monster_kills #3!)" << std::endl;
        }
    }

    // Update player quests
    for(auto& q : gQuestLog->onGoingQuest)
    {
        std::string quest_id = std::to_string(q.first);
        qstr = "SELECT * FROM `actor_quest` WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            // Exist variable
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                if(q.second) qstr = "UPDATE `actor_quest` SET `progress` = '1'";
                else qstr = "UPDATE `actor_quest` SET `progress` = '0'";
                qstr += " WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor on going quest #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_quest(actor_id, quest_id, progress) ";
                if(q.second) qstr += "VALUES('" + actor_id + "','" + quest_id + "','1')";
                else qstr += "VALUES('" + actor_id + "','" + quest_id + "','0')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor on going quest #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor on going quest #3!)" << std::endl;
        }
    }

    for(auto& q : gQuestLog->finishedQuest)
    {
        std::string quest_id = std::to_string(q.first);
        qstr = "SELECT * FROM `actor_quest` WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
        qstate = mysql_query(conn, qstr.c_str());
        if(!qstate)
        {
            res = mysql_store_result(Game::conn);
            row = mysql_fetch_row(res);
            if(row)
            {
                qstr = "UPDATE `actor_quest` SET `progress` = '2'";
                qstr += " WHERE `actor_id` = '" + actor_id + "' AND `quest_id` = '" + quest_id + "'";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor finished quest #1!)" << std::endl;
            }else
            {
                qstr = "INSERT INTO actor_variable(actor_id, quest_id, progress) ";
                qstr += "VALUES('" + actor_id + "','" + quest_id + "','2')";
                qstate = mysql_query(conn, qstr.c_str());
                if(qstate) std::cerr << "Can not make query! (Can not save actor finished quest #2!)" << std::endl;
            }
            mysql_free_result(res);
        }else
        {
            std::cerr << "Can not make query! (Can not save actor finished quest #3!)" << std::endl;
        }
    }

    // Update ranking
    std::string actor_power = std::to_string(gPlayer->mStats->Power);
    std::string actor_gold = std::to_string(gInventory->GetGold());
    std::string actor_level = std::to_string(gPlayer->mStats->Level);
    qstr = "";
    qstr += "UPDATE `actor_ranking` SET `actor_power`='" + actor_power + "',`actor_gold`='" + actor_gold + "',`actor_level`='" +  actor_level ;
    qstr += "' WHERE `actor_id` = '" + actor_id + "'";
    qstate = mysql_query(conn, qstr.c_str());
    if(qstate)
    {
        std::cout << "Can not make query! (Can not save actor ranking!)" << std::endl;
    }

    std::cout << "Player data was saved!" << std::endl;
    session = CLEAR;
}

void Game::clean()
{
    TextureManager::CleanTexture();
    MixerManager::CleanMixer();
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    mysql_close(conn);

    gWindow = NULL;
    gRenderer = NULL;
    conn = NULL;

    delete loginPanel;
    delete registerPanel;
    cout << "Game cleaned" << endl;

    return;
}
