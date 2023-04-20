#include "components.h"
#include <raylib.h>

using namespace Components;

struct ListObject;

ListBox::ListBox() : Events{}
{
}
ListBox::ListBox(std::vector<ListObject> initData, int initWidth, int initFontSize, Vector2 initPosition, bool includeIndex) : data(initData), width(initWidth), fontSize(initFontSize), position(initPosition), includeIndex(includeIndex)
{
    ListBoxInitialize();
}

ListBox::~ListBox()
{
}

void ListBox::ListBoxInitialize()
{
    if (data.size() == 0)
    {
        return;
    }
    textActiveColor = textColor;
    if (clickableRecs.size() < data.size())
    {
        listRectangle.width = width;
        for (int i = 0; i < data.size(); i++)
        {
            float rectHeight = (data.size() * fontSize) + (8 * data.size());
            Rectangle lineRec = {position.x, (position.y) + ((fontSize + 5) * data[i].key), (float)width, rectHeight};
            clickableRecs.push_back(lineRec);
        }
    }
    float rectHeight = (data.size() * fontSize) + (8 * data.size());
    listRectangle = {position.x, position.y, (float)width, rectHeight};
}

void ListBox::ListBoxAction(ListObject &obj)
{
    bool isClicked = false;
    bool isHovering = false;

    auto click = [&isClicked](bool click) -> bool
    {
        isClicked = click;
        return click;
    };
    auto hover = [&isHovering](bool hover) -> bool
    {
        isHovering = hover;
        return hover;
    };

    HandleRectangleEvent(
        clickableRecs[obj.key], click, hover);

    if (isClicked)
    {
        itemClicked.key = obj.key;
        itemClicked.value = obj.value;
        textActiveColor = textActionColor;
    }
    else
    {
        textActiveColor = textColor;
    }

    if (isHovering)
    {
        hoveringItem.hovering = true;
        hoveringItem.index = obj.key;
    }
    else
    {
        hoveringItem.hovering = false;
        hoveringItem.index = obj.key;
    }
}

void ListBox::ListBoxDrawItem(ListObject &obj)
{
    bool hovering = hoveringItem.hovering && hoveringItem.index == obj.key;

    Vector2 linePos = {position.x, (position.y + 10) + ((fontSize + 5) * obj.key)};
    if (includeIndex)
    {
        char indexString[5 + sizeof(char)] = "";
        sprintf(indexString, "%d", obj.key);
        DrawText(indexString, linePos.x + 10, linePos.y, fontSize, hovering ? textActionColor : textActiveColor);
    }
    int valueWidth = MeasureText(obj.value.c_str(), fontSize);
    DrawText(obj.value.c_str(), (linePos.x - 10) + (listRectangle.width - valueWidth), linePos.y, fontSize, hovering ? textActionColor : textActiveColor);
}

void ListBox::ListBoxRectangleDraw()
{
    if (!transparent)
    {
        DrawRectangleRec(listRectangle, fillColor);
    }

    DrawRectangleLinesEx(listRectangle, 5, outlineColor);
}

void ListBox::HandleListBox()
{
    ListBoxRectangleDraw();

    for (int i = 0; i < data.size(); i++)
    {
        ListBoxAction(data[i]);
        ListBoxDrawItem(data[i]);
    }
}

Events::Events() {}
Events::~Events() {}

void Events::HandleRectangleEvent(Rectangle &hitBox, const std::function<void(bool)> &click, const std::function<void(bool)> &hover)
{
    mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, hitBox))
    {

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            click(true);
        }
        else
        {
            hover(true);
            click(false);
        }
    }
    else
    {
        hover(false);
    }
}

void Clicking()
{
    printf("I've clicked something");
}
