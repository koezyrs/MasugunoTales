#include "Item.h"

Item::Item(int _item_id, std::string spriteName, int _maxStack, const char* _itemTag, std::string _itemName, std::string _description,int _buyPrice, int _sellPrice, std::function<void()> func)
: item_id(_item_id), maxStack(_maxStack), currentStack(1), itemTag(_itemTag), itemName(_itemName), description(_description), buyPrice(_buyPrice), sellPrice(_sellPrice), ItemFunction([this, func] {func();})
{
    itemSprite = TextureManager::GetTexture(spriteName);
}

SDL_Texture* Item::getItemSprite()
{
    return itemSprite;
}

void Item::Perform()
{
    ItemFunction();
}

bool Item::isActive()
{
    return active;
}

void Item::destroy()
{
    active = false;
}

Item::~Item()
{
    itemSprite = NULL;
}
