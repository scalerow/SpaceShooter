#include "components.h"
#include <raylib.h>

using namespace Components;

struct ListObject;

ListBox::ListBox() : Events{}
{
}

ListBox::~ListBox()
{
}

void ListBox::ListBoxInitialize()
{
    if (inputObject.size() == 0)
    {
        return;
    }
    textActionColor = ColorAlpha(textColor, 120);
    textActiveColor = textColor;
    if (clickableRecs.size() < inputObject.size())
    {
        listRectangle.width = width;
        for (int i = 0; i < inputObject.size(); i++)
        {
            float rectHeight = (inputObject.size() * fontSize) + (8 * inputObject.size());
            Rectangle lineRec = {position.x, (position.y) + ((fontSize + 5) * inputObject[i].key), (float)width, rectHeight};
            clickableRecs.push_back(lineRec);
        }
    }
    float rectHeight = (inputObject.size() * fontSize) + (8 * inputObject.size());
    listRectangle = {position.x, position.y, (float)width, rectHeight};
}

bool ListBox::ListBoxAction(ListObject &obj)
{
    mousePoint = GetMousePosition();

    HandleRectangleEvent(
        clickableRecs[obj.key], eventData.Callback);

    if (eventData.Callback.)
    {
        itemClicked.key = obj.key;
        itemClicked.value = obj.value;
        textActiveColor = textActionColor;
        return event.click;
    }
    else
    {
        return false;
    }
    if (event.hover)
    {
        textActiveColor = textActionColor;
    }
    else
    {
        textActiveColor = textColor;
    }
}

void ListBox::ListBoxDrawItem(ListObject &obj)
{
    Vector2 linePos = {position.x, (position.y + 10) + ((fontSize + 5) * obj.key)};
    if (includeIndex)
    {
        char indexString[5 + sizeof(char)] = "";
        sprintf(indexString, "%d", obj.key);
        DrawText(indexString, linePos.x + 10, linePos.y, fontSize, textActiveColor);
    }
    int valueWidth = MeasureText(obj.value.c_str(), fontSize);
    DrawText(obj.value.c_str(), (linePos.x - 10) + (listRectangle.width - valueWidth), linePos.y, fontSize, textActiveColor);
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

    for (int i = 0; i < inputObject.size(); i++)
    {
        ListBoxAction(inputObject[i]);
        ListBoxDrawItem(inputObject[i]);
    }
}

Events::Events() {}
Events::~Events() {}

struct Events::DefaultEvent;

void Events::HandleRectangleEvent(Rectangle &hitBox, DefaultEvent &event, const std::function<void()> &verifyEvent)
{
    event.click = false;
    event.hover = false;

    mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, hitBox))
    {

        event.hover = true;
        verifyEvent(rectangeEvent);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            event.click = true;
            verifyEvent(rectangeEvent);
        }
    }
}

void Clicking()
{
    printf("I've clicked something");
}
