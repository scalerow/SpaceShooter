#include "components.h"

using namespace Components;

struct ListObject;

ListBox::ListBox()
{
}

ListBox::ListBox()
{
    ListBoxDraw();
    Rectangle test = {0, 0, 0, 0};
    ListBoxActions(Clicking);
}

ListBox::~ListBox()
{
}

void ListBox::ListBoxActions(void (*func)())
{
    mousePoint = GetMousePosition();
    
    for (int i = 0; 0 <= clickableRecs.size(); i++)
    {   
         Events::DefaultEvent event =  Events::ClickRectangleEvent(clickableRecs[i]);
        if (event.click)
        {
            func();
        }
        if(event.hover)
        {
            BeginBlendMode(BLEND_ADD_COLORS);
                ColorAlphaBlend(textColor, textColor,DARKGRAY);
            EndBlendMode();
        }
    }
}

void ListBox::ListBoxDraw()
{
    int rectHeight = (inputObject.size() * fontSize) + (5 * inputObject.size());
    Rectangle listRect = {position.x, position.y, width, rectHeight};

    if (!transparent)
    {
        DrawRectangleRec(listRect, fillColor);
    }

    DrawRectangleLinesEx(listRect, 5, outlineColor);

    for (int i = 0; i < inputObject.size(); i++)
    {
        if (includeIndex)
        {
            char indexString[5 + sizeof(char)] = "";
            sprintf(indexString, "%d", inputObject[i].key);
            DrawText(indexString, position.x + 10, position.y + ((fontSize + 5) * i), fontSize, textColor);
        }
        int valueWidth = MeasureText(inputObject[i].value.c_str(), fontSize);
        DrawText(inputObject[i].value.c_str(), (position.x - 10) + (listRect.width - valueWidth), position.y + ((fontSize + 5) * i), fontSize, textColor);
    }
}

Events::Events(){}
Events::~Events(){}


struct Events::DefaultEvent;

Events::DefaultEvent Events::ClickRectangleEvent(Rectangle clickArea) 
{
    DefaultEvent rectangeEvent;
    rectangeEvent.click = false;
    rectangeEvent.hover = false;

    mousePoint = GetMousePosition();     
    if(CheckCollisionPointRec(mousePoint, clickArea))
    {
        rectangeEvent.hover = true;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            rectangeEvent.click = true;
        }
    }

    return rectangeEvent;
}

void Clicking()
{
    printf("I've clicked something");
}