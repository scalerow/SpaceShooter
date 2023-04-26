#include "components.h"
#include <raylib.h>

using namespace Components;

struct ListObject;
struct EventType;

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

// Initializes and calaculates hitboxes and other data
void ListBox::ListBoxInitialize()
{
    if (data.size() == 0)
    {
        return;
    }
    // Set init color for text
    textActiveColor = textColor;

    // Creates rectangle hitboxes for listbox-data
    if (clickableRecs.size() < data.size())
    {
        listRectangle.width = width;
        for (int i = 0; i < data.size(); i++)
        {
            Rectangle lineRec = {position.x, (position.y + 10.f) + (((float)fontSize + 5.f) * i), (float)width, (float)fontSize};
            clickableRecs.push_back(lineRec);
        }
    }
    float rectHeight = (data.size() * fontSize) + (8 * data.size());
    listRectangle = {position.x, position.y, (float)width, rectHeight};
}

// Handle click and hover events in listbox
void ListBox::ListBoxAction(ListObject &obj, int &index)
{
    auto click = [&](bool click) -> void
    {
        obj.eventType.click = click;
    };
    auto hover = [&](bool hover) -> void
    {
        obj.eventType.hover = hover;
    };

    HandleRectangleEvent(
        clickableRecs[index], click, hover);
}

// Draw items in listbox
void ListBox::ListBoxDrawItem(ListObject &obj, int &lineNumber)
{
    bool action = obj.eventType.click || obj.eventType.hover;

    Vector2 linePos = {position.x, (position.y + 10) + ((fontSize + 5) * lineNumber)};
    if (includeIndex)
    {
        char indexString[5 + sizeof(char)] = "";
        sprintf(indexString, "%d", obj.key);
        DrawText(indexString, linePos.x + 10, linePos.y, fontSize, action ? textActionColor : textActiveColor);
    }
    int valueWidth = MeasureText(obj.value.c_str(), fontSize);
    DrawText(obj.value.c_str(), (linePos.x - 10) + (listRectangle.width - valueWidth), linePos.y, fontSize, action ? textActionColor : textActiveColor);
}

// Draws outline of listbox
void ListBox::ListBoxRectangleDraw()
{
    if (!transparent)
    {
        DrawRectangleRec(listRectangle, fillColor);
    }

    DrawRectangleLinesEx(listRectangle, 5, outlineColor);
}

// Use listbox
void ListBox::HandleListBox()
{
    ListBoxRectangleDraw();

    for (int i = 0; i < data.size(); i++)
    {
        ListBoxAction(data[i], i);
        ListBoxDrawItem(data[i], i);
    }
}

Events::Events() {}
Events::~Events() {}

// Rectangle event handler
void Events::HandleRectangleEvent(Rectangle &hitBox, const std::function<void(bool)> &click, const std::function<void(bool)> &hover)
{
    mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, hitBox))
    {
        hover(true);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            click(true);
        }
        else
        {
            click(false);
        }
    }
    else
    {
        hover(false);
        click(false);
    }
}
