#include "MapManager.h"

std::map<int, std::vector<std::vector<Tile>>> MapManager::mapBase;
std::map<int, std::shared_ptr<Map>> MapManager::mapDatabase;
void MapManager::LoadMap(int map_id)
{
    Game::gPlayer->getKeyboardController()->unsetTarget();
    Game::currentMap = mapDatabase[map_id];
    switch(map_id)
    {
    case 1:
        MixerManager::PlayMusic("Map01Music");
        break;
    case 2:
        MixerManager::PlayMusic("Map02Music");
        break;
    case 3:
        MixerManager::PlayMusic("Map03Music");
        break;
    case 4:
        MixerManager::PlayMusic("Map04Music");
        break;
    case 5:
        MixerManager::PlayMusic("Map05Music", 20);
        break;
    default:
        break;
    }
}

std::vector<std::vector<Tile>> MapManager::setupMap(const char* msgnFile, int sizeX, int sizeY)
{
    std::fstream fileContainCoordiate;
    char tile;

    std::vector<std::vector<Tile>> res;

    fileContainCoordiate.open(msgnFile);
    for(int y = 0; y < sizeY; y++)
    {
        std::vector<Tile> tmp;
        for(int x = 0 ; x < sizeX; x++)
        {
            fileContainCoordiate.get(tile);
            int id = atoi(&tile);
            if(id == 1)
            {
                Tile tmpTile = Tile(static_cast<float>(x), static_cast<float>(y), true);
                tmp.push_back(tmpTile);
            }else
            {
                Tile tmpTile = Tile(static_cast<float>(x), static_cast<float>(y), false);
                tmp.push_back(tmpTile);
            }
            fileContainCoordiate.ignore();
        }
        fileContainCoordiate.ignore();
        res.push_back(tmp);
    }
    fileContainCoordiate.close();
    return res;
}

void MapManager::LoadMapDatabase()
{
    // Map Base
    mapBase[1] = setupMap("data files/maps/map01.msgn", 50, 30);
    mapBase[2] = setupMap("data files/maps/map02.msgn", 33, 21);
    mapBase[3] = setupMap("data files/maps/map03.msgn", 61, 32);
    mapBase[4] = setupMap("data files/maps/map04.msgn", 60, 33);
    mapBase[5] = setupMap("data files/maps/map05.msgn", 32, 19);

    // Map database
    mapDatabase[1] = std::make_shared<Map>(1, "Map01", "Map01_Overlay");
    mapDatabase[2] = std::make_shared<Map>(2, "Map02", "Map02_Overlay");
    mapDatabase[3] = std::make_shared<Map>(3, "Map03", "Map03_Overlay");
    mapDatabase[4] = std::make_shared<Map>(4, "Map04", "Map04_Overlay");
    mapDatabase[5] = std::make_shared<Map>(5, "Map05", "");

    // Load data
    LoadMap1();
    LoadMap2();
    LoadMap3();
    LoadMap4();
    LoadMap5();
}

void MapManager::LoadMap1()
{
    mapDatabase[1]->AddNPC(8 * 32, 4 * 32, "Sprite-Leiea", "Leiea Lv. 6");
    mapDatabase[1]->AddEvent(10 * 32, 14 * 32, "",[]
                                {
                                    LoadMap(2);
                                    Game::gPlayer->setPosition(16 * 32, 19 * 32);
                                });
    mapDatabase[1]->AddEvent(-1 * 32, 23 * 32, "",[]
                                {
                                    LoadMap(3);
                                    Game::gPlayer->setPosition(59 * 32, 17 * 32);
                                });
    mapDatabase[1]->AddEvent(-1 * 32, 24 * 32, "",[]
                                {
                                    LoadMap(3);
                                    Game::gPlayer->setPosition(59 * 32, 18 * 32);
                                });
    mapDatabase[1]->AddEvent(35 * 32, 30 * 32, "",[]
                                {
                                    LoadMap(4);
                                    Game::gPlayer->setPosition(27 * 32, 0 * 32);
                                });
    mapDatabase[1]->AddEvent(12 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});
    mapDatabase[1]->AddEvent(13 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});
    mapDatabase[1]->AddEvent(14 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});
    mapDatabase[1]->AddEvent(15 * 32, 17 * 32 + 5, "",[]{OpenRankingBoard();});


    mapDatabase[1]->AddMonster(21*32,6*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(15*32,4*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(5*32,3*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(10*32,3*32,1,mapBase[1]);
    mapDatabase[1]->AddMonster(18*32,4*32,1,mapBase[1]);

    mapDatabase[1]->AddMonster(45*32,26*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(42*32,22*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(39*32,26*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(42*32,19*32,2,mapBase[1]);
    mapDatabase[1]->AddMonster(46*32,19*32,2,mapBase[1]);


    mapDatabase[1]->AddMonster(22 * 32, 19 * 32, 3, mapBase[1]);
    mapDatabase[1]->AddMonster(24 * 32, 19 * 32, 3, mapBase[1]);
    mapDatabase[1]->AddMonster(26 * 32, 19 * 32, 3, mapBase[1]);
    mapDatabase[1]->AddMonster(26 * 32, 17 * 32, 3, mapBase[1]);

    mapDatabase[1]->AddNPC(9 * 32, 25 * 32 - 17, "Sprite-Ryn", "Ryn");
    mapDatabase[1]->AddEvent(9 * 32, 25 * 32 + 5, "",[]{OpenShop(1);});

    mapDatabase[1]->AddNPC(23 * 32, 16 * 32 - 17, "Sprite-Zeph", "Zeph");
    mapDatabase[1]->AddEvent(23 * 32, 16 * 32 + 5, "",[]{OpenShop(2);});

    mapDatabase[1]->AddNPC(3 * 32, 19 * 32 - 17, "Sprite-Cephur", "Cephur");
    mapDatabase[1]->AddEvent(3 * 32, 19 * 32 + 5, "",[]{OpenShop(3);});

    mapDatabase[1]->AddNPC(19 * 32, 28 * 32, "Sprite-July", "July Lv. 3");
    mapDatabase[1]->AddNPC(21 * 32, 28 * 32, "Sprite-Peeper", "Peeper Lv. 4");
    mapDatabase[1]->AddNPC(16 * 32, 14 * 32, "Sprite-Athur", "Athur Lv. 17");
    mapDatabase[1]->AddNPC(19 * 32, 14 * 32, "Sprite-Irish", "Irish Lv. 12");
}

void MapManager::LoadMap2()
{
    mapDatabase[2]->AddEvent(16 * 32, 20 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(10 * 32, 16 * 32);
                                });
    mapDatabase[2]->AddNPC(16 * 32, 9 * 32, "Sprite-Aurez", "Aurez Lv. 50");
    mapDatabase[2]->AddEvent(16 * 32, 10 * 32 + 5, "",[]
                                {
                                    GuildMasterConversation();
                                });

}

void MapManager::LoadMap3()
{
    mapDatabase[3]->AddEvent(60 * 32, 17 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(0 * 32, 23 * 32);
                                });
    mapDatabase[3]->AddEvent(60 * 32, 18 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(0 * 32, 24 * 32);
                                });

    mapDatabase[3]->AddNPC(54 * 32, 24 * 32, "Sprite-Morwag", "Morwag Lv. 37");
    mapDatabase[3]->AddNPC(3 * 32, 14 * 32, "Sprite-MysteryMan", "Lv. ???");

    mapDatabase[3]->AddMonster(48*32,3*32,4,mapBase[3]);
    mapDatabase[3]->AddMonster(55*32,5*32,4,mapBase[3]);
    mapDatabase[3]->AddMonster(49*32,6*32,4,mapBase[3]);
    mapDatabase[3]->AddMonster(52*32,4*32,4,mapBase[3]);
    mapDatabase[3]->AddMonster(46*32,7*32,4,mapBase[3]);

    mapDatabase[3]->AddMonster(19*32,22*32,5,mapBase[3]);
    mapDatabase[3]->AddMonster(15*32,23*32,5,mapBase[3]);
    mapDatabase[3]->AddMonster(16*32,27*32,5,mapBase[3]);
    mapDatabase[3]->AddMonster(20*32,27*32,5,mapBase[3]);
    mapDatabase[3]->AddMonster(9*32,21*32,5,mapBase[3]);

    mapDatabase[3]->AddMonster(6*32,4*32,6,mapBase[3]);
    mapDatabase[3]->AddMonster(5*32,7*32,6,mapBase[3]);
    mapDatabase[3]->AddMonster(14*32,5*32,6,mapBase[3]);
    mapDatabase[3]->AddMonster(18*32,5*32,6,mapBase[3]);
    mapDatabase[3]->AddMonster(9*32,6*32,6,mapBase[3]);

    mapDatabase[3]->AddMonster(24*32,7*32,7,mapBase[3]);
    mapDatabase[3]->AddMonster(29*32,8*32,7,mapBase[3]);
    mapDatabase[3]->AddMonster(23*32,18*32,7,mapBase[3]);
    mapDatabase[3]->AddMonster(29*32,19*32,7,mapBase[3]);
    mapDatabase[3]->AddMonster(22*32,11*32,7,mapBase[3]);
}

void MapManager::LoadMap4()
{
    mapDatabase[4]->AddEvent(27 * 32, -1 * 32, "",[]
                                {
                                    LoadMap(1);
                                    Game::gPlayer->setPosition(35 * 32, 29 * 32);
                                });
    mapDatabase[4]->AddEvent(47 * 32, 20 * 32, "",[]
                                {
                                    LoadMap(5);
                                    Game::gPlayer->setPosition(16 * 32, 17 * 32);
                                });
    mapDatabase[4]->AddMonster(25*32,8*32,8,mapBase[4]);
    mapDatabase[4]->AddMonster(35*32,9*32,8,mapBase[4]);
    mapDatabase[4]->AddMonster(23*32,14*32,8,mapBase[4]);
    mapDatabase[4]->AddMonster(38*32,11*32,8,mapBase[4]);
    mapDatabase[4]->AddMonster(29*32,8*32,8,mapBase[4]);

    mapDatabase[4]->AddMonster(6*32,14*32,9,mapBase[4]);
    mapDatabase[4]->AddMonster(11*32,18*32,9,mapBase[4]);
    mapDatabase[4]->AddMonster(15*32,20*32,9,mapBase[4]);
    mapDatabase[4]->AddMonster(4*32,23*32,9,mapBase[4]);
    mapDatabase[4]->AddMonster(15*32,25*32,9,mapBase[4]);

    mapDatabase[4]->AddMonster(32*32,21*32,10,mapBase[4]);
    mapDatabase[4]->AddMonster(36*32,25*32,10,mapBase[4]);
    mapDatabase[4]->AddMonster(25*32,24*32,10,mapBase[4]);
    mapDatabase[4]->AddMonster(22*32,27*32,10,mapBase[4]);
    mapDatabase[4]->AddMonster(39*32,26*32,10,mapBase[4]);

    mapDatabase[4]->AddMonster(46*32,23*32,11,mapBase[4]);
    mapDatabase[4]->AddMonster(54*32,22*32,11,mapBase[4]);
    mapDatabase[4]->AddMonster(51*32,27*32,11,mapBase[4]);
    mapDatabase[4]->AddMonster(41*32,26*32,11,mapBase[4]);
    mapDatabase[4]->AddMonster(55*32,18*32,11,mapBase[4]);

}

void MapManager::LoadMap5()
{
    mapDatabase[5]->AddEvent(16 * 32, 18 * 32, "",[]
                                {
                                    LoadMap(4);
                                    Game::gPlayer->setPosition(47 * 32, 21 * 32);
                                });
}


void MapManager::OpenRankingBoard()
{
    if((Game::event.type == SDL_KEYDOWN))
    {
        switch(Game::event.key.keysym.sym )
        {
            case SDLK_LCTRL: Game::gRanking->showWindow(); break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
                Game::gRanking->hideWindow();
                break;
            default:
                break;
        }
    }
}

void MapManager::GuildMasterConversation()
{
    if((Game::event.type == SDL_KEYDOWN))
    {
        switch(Game::event.key.keysym.sym )
        {
            case SDLK_LCTRL: QuestLog::GuildMasterGiveQuest(); break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
                Game::gDialogue->hideWindow();
                break;
            default:
                break;
        }
    }
}

void MapManager::OpenShop(int shop_id)
{
    if((Game::event.type == SDL_KEYDOWN))
    {
        switch(Game::event.key.keysym.sym )
        {
            case SDLK_LCTRL: Game::gShop->OpenShop(shop_id); break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
                Game::gShop->hideWindow();
                break;
            default:
                break;
        }
    }
}
