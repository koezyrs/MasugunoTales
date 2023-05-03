#pragma once

#ifndef Settings_h
#define Settings_h
const char GAME_TITLE[] = "Masuguno Tales";
const char GAME_FONT[] = "data files/font/game.ttf";

/*
const char HOST[] = "127.0.0.1"; // sql12.freemysqlhosting.net
const char DBUSERNAME[] = "admin"; // sql12613641
const char DBPASSWORD[] = "admin"; // CQiXxpa5uh
const char DATABASE[] = "test"; // sql12613641r
*/

const char HOST[] = "sql12.freemysqlhosting.net"; // sql12.freemysqlhosting.net
const char DBUSERNAME[] = "sql12613641"; // sql12613641
const char DBPASSWORD[] = "CQiXxpa5uh"; // CQiXxpa5uh
const char DATABASE[] = "sql12613641"; // sql12613641

const int HOSTPORT = 3306;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 576;
const int GAME_PIXELS = 32;
const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 32;
const int GAME_SCALE = 1;
const int FPS = 60;
const int frameDelay = 1000 / FPS;
const int PLAYER_VELOCITY = 2;
const int MAX_INVENTORY_SLOTS = 35;
const int MAX_EQUIPMENT_SLOTS = 10;
const int MAX_SHOP_SLOTS = 35;
const int MAX_LEVEL = 50;
const int MAX_RANKING_TOP = 10;
const unsigned int flowDistanceMax = 512;
const float NEXT_LEVEL_EXP_RATE = 1.5;
// Enums

enum EQUIPMENT_TAG
{
    WEAPON,
    SHIELD,
    HELMET,
    ARMOR,
    GLOVE,
    SHOES,
    CAPE,
    RING,
    NECKLACE,
    MEDAL
};
#endif // Settings_h
