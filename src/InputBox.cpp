#include "InputBox.h"

InputBox::InputBox(float x, float y, int width, int height, int characterLimit, bool isPassword)
: position(x,y), Width(width), Height(height), CharacterLimit(characterLimit), IsPassword(isPassword)
{
    inputText = new Label(GAME_FONT, " ", 10, x, y, Black, characterLimit*10, false, []{});
    isFocusText = new Label(GAME_FONT, "|", 10, x, y, Black, 5, false, []{});
    inputValue = "";
    tempPassword = "";
}

InputBox::~InputBox()
{
    delete inputText;
    delete isFocusText;
}

void InputBox::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // check if the mouse is in the button
        if((x < position.x) || (x > position.x + Width) || (y < position.y) || (y > position.y + Height)) inside = false;
        else inside = true;

        if(inside && e->type == SDL_MOUSEBUTTONDOWN) {active = true;}

        if (!inside && e->type == SDL_MOUSEBUTTONDOWN) {active = false;}
    }

    if(active)
    {
        switch(e->type)
        {
        case SDL_TEXTINPUT:
            {
                int n = inputValue.length();
                if(n >= CharacterLimit) break;
                if(!IsPassword){
                    inputValue += e->text.text;
                    inputText->Reset();
                    inputText = new Label(GAME_FONT, inputValue.c_str(), 10, position.x, position.y, Black, CharacterLimit * 10, false, []{});
                    isFocusText->Reset();
                    isFocusText = new Label(GAME_FONT, "|", 10, position.x + inputText->getWidth() + 1, position.y, Black, 5, false, []{});
                }else{
                    inputValue += e->text.text;
                    tempPassword += '*';
                    inputText->Reset();
                    inputText = new Label(GAME_FONT, tempPassword.c_str(), 10, position.x, position.y, Black, CharacterLimit * 10, false, []{});
                    isFocusText->Reset();
                    isFocusText = new Label(GAME_FONT, "|", 10, position.x + inputText->getWidth() + 1, position.y, Black, 5, false, []{});
                }
            }
            break;
        case SDL_KEYDOWN:
            if(e->key.keysym.sym == SDLK_BACKSPACE)
            {
                int n = inputValue.length();
                if(n <= 0) break;
                if(IsPassword)
                {
                    inputValue.erase(n - 1);
                    tempPassword.erase(n - 1);
                    inputText->Reset();
                    inputText = new Label(GAME_FONT, tempPassword.c_str(), 10, position.x, position.y, Black, CharacterLimit * 10, false, []{});
                    isFocusText->Reset();
                    isFocusText = new Label(GAME_FONT, "|", 10, position.x + inputText->getWidth() + 1, position.y, Black, 5, false, []{});
                }else{
                    inputValue.erase(n - 1);
                    inputText->Reset();
                    inputText = new Label(GAME_FONT, inputValue.c_str(), 10, position.x, position.y, Black, CharacterLimit * 10, false, []{});
                    isFocusText->Reset();
                    isFocusText = new Label(GAME_FONT, "|", 10, position.x + inputText->getWidth() + 1, position.y, Black, 5, false, []{});
                }
                if(inputValue.length() == 0)
                {
                    isFocusText->Reset();
                    isFocusText = new Label(GAME_FONT, "|", 10, position.x , position.y, Black, 5, false, []{});
                }
            }
            break;
        }
    }
}

void InputBox::Render()
{
    inputText->Render();
    if(active) isFocusText->Render();
}

void InputBox::setActive()
{
    active = true;
}

void InputBox::deActive()
{
    active = false;
}

bool InputBox::isActive()
{
    return active;
}

void InputBox::toogle()
{
    active = !active;
}

void InputBox::Reset()
{
    inputValue = "";
    tempPassword = "";
    inputText->Reset();
    isFocusText->Reset();
    isFocusText = new Label(GAME_FONT, "|", 10, position.x , position.y, Black, 5, false, []{});
}
