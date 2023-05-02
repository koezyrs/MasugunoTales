#pragma once
#ifndef Register_h
#define Register_h

#include <string>

#include "../Game.h"
#include "../InputBox.h"
#include "../Button.h"
#include "../TextureManager.h"

class Register
{
public:
    Register();
    ~Register();
    void HandleEvent();
    void Update();
    void Render();
private:
    SDL_Color Black = {0,0,0};
    void RegistButon();
    void BackButton();
    void setMessage(std::string text);
    bool checkSpecialSymbol(std::string text);
    SDL_Texture* registPanelTexture;
    InputBox* username_input;
    InputBox* password_input;
    InputBox* retype_password_input;
    InputBox* email_input;
    Button* button_regist;
    Button* button_back;
    Label* systemMessageText;
};

#endif // Register_h

