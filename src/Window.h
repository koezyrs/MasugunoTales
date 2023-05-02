#pragma once
#ifndef Window_h
#define Window_h

class Window
{
public:
    Window();
    virtual ~Window();
    bool isActive();
    bool isHide();
    void destroy();
    void showWindow();
    void hideWindow();
    void Toggle();
    virtual void Update() = 0;
    virtual void Render() = 0;
private:
    bool hide = true;
    bool active = true;
};

#endif // Window_h
