#include "Window.h"

Window::Window() {}
Window::~Window() {}

bool Window::isActive() {return active;}
bool Window::isHide() {return hide;}
void Window::destroy() {active = false;}
void Window::showWindow() {hide = false;}
void Window::hideWindow() {hide = true;}
void Window::Toggle() {hide = !hide;}
