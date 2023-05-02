#pragma once
#ifndef Login_h
#define Login_h

#include <string>

#include "../Game.h"
#include "../InputBox.h"
#include "../Button.h"
#include "../TextureManager.h"
#include "../Map.h"
#include "../Actor.h"
#include "../Dialogue.h"
#include "../Inventory.h"
#include "../CharacterInformation.h"
#include "../HUD.h"
#include "../Hotbar.h"
#include "../QuestLog.h"
#include "../Shop.h"
#include "../Ranking.h"
#include "../MapManager.h"

class Login
{
public:
    Login();
    ~Login();
    void HandleEvent();
    void Update();
    void Render();
private:
    SDL_Color Black = {0,0,0};
    void LoginButon();
    void ExitButton();
    void RegistButton();
    void setMessage(std::string text);
    void LoadGameDatabase(std::string _account_id);
    SDL_Texture* loginPanelTexture;
    InputBox* username_input;
    InputBox* password_input;
    Button* button_login;
    Button* button_exit;
    Button* button_register;
    Label* systemMessageText;
};

#endif // Login_h
