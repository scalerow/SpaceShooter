#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>
#include <functional>
#include "gameobjects.h"

namespace Components
{
#ifndef EVENTS_H
#define EVENTS_H

    class Events
    {
    private:
        Vector2 mousePoint;

    public:
        Events();
        ~Events();

        void HandleRectangleEvent(Rectangle &hitBox, const std::function<void(bool)> &click, const std::function<void(bool)> &hover);
    };
#endif
    struct EventType
    {
        bool hover = false;
        bool click = false;
    };
    struct ListObject
    {
        int key;
        std::string value;
        EventType eventType;
    };
#ifndef LISTBOX_H
#define LISTBOX_H

    /*
    EXAMPLE OF LISTBOX INIT USING DEFAULT COLORS AND SIZE
        Components::ListBox listBox = Components::ListBox(inputObjects, 400, 25, {(screenWidth / 2) - 200, screenHeight / 2}, true);
    */
    class ListBox : public Events
    {
    private:
        std::vector<Rectangle> clickableRecs;
        Rectangle listRectangle;
        Color textActiveColor;
        void ListBoxDrawItem(ListObject &obj, int &lineNumber);
        void ListBoxAction(ListObject &obj, int &index);
        void ListBoxRectangleDraw();

    public:
        std::vector<ListObject> data;
        Vector2 position;
        int width = 500;
        int fontSize = 16;
        bool includeIndex = true;
        bool transparent = false;

        Color textActionColor = ColorAlphaBlend(BLACK, WHITE, DARKGREEN);
        Color outlineColor = GREEN;
        Color fillColor = BLANK;
        Color textColor = GREEN;

        void HandleListBox();
        void ListBoxInitialize();
        ListBox();
        ListBox(std::vector<ListObject> initData, int initWidth, int initFontSize, Vector2 initPosition, bool includeIndex);
        ~ListBox();
    };
#endif

}
#endif