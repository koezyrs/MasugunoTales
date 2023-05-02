#include "Dialogue.h"

Dialogue::Dialogue(int _x, int _y, int _width, int _height, const char* title, std::string facefile, const char* content)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height)

{
    DialogueBox = TextureManager::GetTexture("Dialogue");
    Face = TextureManager::GetTexture(facefile); // (x,y) = (24,40)
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 461, _y + 5, 13, 13, [this]{Window::hideWindow(); });
    dialogueTitle = new Label(GAME_FONT, title, 10, _x + 5, _y + 5, SDL_Color{255,255,255},320);
    dialogueContent = new Label(GAME_FONT, content, 10, _x + 134, _y + 45, SDL_Color{255,255,255}, 320);
    dialogueOption1 = new Label(GAME_FONT, "1.", 10, _x + 25, _y + 145, SDL_Color{0,0,0}, 430);
    dialogueOption2 = new Label(GAME_FONT, "2.", 10, _x + 25, _y + 160, SDL_Color{0,0,0}, 430);
    dialogueOption3 = new Label(GAME_FONT, "3.", 10, _x + 25, _y + 175, SDL_Color{0,0,0}, 430);
    dialogueOption4 = new Label(GAME_FONT, "4.", 10, _x + 25, _y + 190, SDL_Color{0,0,0}, 430);
    srcRect = {0,0, mWidth, mHeight};
    destRect = {static_cast<int> (position.x), static_cast<int> (position.y), mWidth, mHeight};
    faceSrcRect ={0, 0, 96, 96};
    faceDestRect ={_x + 24, _y + 40, 96, 96};
}

Dialogue::~Dialogue()
{
    delete closeButton;
    delete dialogueTitle;
    delete dialogueContent;
    delete dialogueOption1;
    delete dialogueOption2;
    delete dialogueOption3;
    delete dialogueOption4;
    DialogueBox = NULL;
}

void Dialogue::Update()
{
    if(!isHide())
    {
        closeButton->handleEvent(&Game::event);
        dialogueOption1->handleEvent(&Game::event);
        dialogueOption2->handleEvent(&Game::event);
        dialogueOption3->handleEvent(&Game::event);
        dialogueOption4->handleEvent(&Game::event);
    }
}

void Dialogue::Render()
{
    if(!isHide())
    {
        TextureManager::Draw(DialogueBox, srcRect, destRect);
        TextureManager::Draw(Face, faceSrcRect, faceDestRect);
        dialogueTitle->Render();
        dialogueContent->Render();
        dialogueOption1->Render();
        dialogueOption2->Render();
        dialogueOption3->Render();
        dialogueOption4->Render();
        closeButton->Render();
    }
}

void Dialogue::setFace(std::string faceImg)
{
    Face = NULL;
    Face = TextureManager::GetTexture(faceImg);
}

void Dialogue::setTitleLabel(const char* title)
{
    dialogueTitle->Reset();
    dialogueTitle = new Label(GAME_FONT, title, 10, position.x + 5, position.y + 5, White, 320);
}

void Dialogue::setContentLabel(const char* content)
{
    dialogueContent->Reset();
    dialogueContent = new Label(GAME_FONT, content, 10, position.x + 134, position.y + 45, White, 320);

}

void Dialogue::setOption1(const char* text, std::function<void()> func)
{
    dialogueOption1->Reset();
    if(text != NULL) dialogueOption1 = new Label(GAME_FONT, text, 10, position.x + 25, position.y + 145, SDL_Color{0,0,0}, 430, true, func);
    else dialogueOption1 = new Label(GAME_FONT, " ", 10, position.x + 25, position.y + 145, SDL_Color{0,0,0}, 430);
}

void Dialogue::setOption2(const char* text, std::function<void()> func)
{
    dialogueOption2->Reset();
    if(text != NULL) dialogueOption2 = new Label(GAME_FONT, text, 10, position.x + 25, position.y + 160, SDL_Color{0,0,0}, 430, true, func);
    else dialogueOption2 = new Label(GAME_FONT, " ", 10, position.x + 25, position.y + 160, SDL_Color{0,0,0}, 430);
}

void Dialogue::setOption3(const char* text, std::function<void()> func)
{
    dialogueOption3->Reset();
    if(text != NULL) dialogueOption3 = new Label(GAME_FONT, text, 10, position.x + 25, position.y + 175, SDL_Color{0,0,0}, 430, true, func);
    else dialogueOption3 = new Label(GAME_FONT, " ", 10, position.x + 25, position.y + 175, SDL_Color{0,0,0}, 430);
}

void Dialogue::setOption4(const char* text, std::function<void()> func)
{
    dialogueOption4->Reset();
    if(text != NULL) dialogueOption4 = new Label(GAME_FONT, text, 10, position.x + 25, position.y + 190, SDL_Color{0,0,0}, 430, true, func);
    else dialogueOption4 = new Label(GAME_FONT, " ", 10, position.x + 25, position.y + 190, SDL_Color{0,0,0}, 430);
}
