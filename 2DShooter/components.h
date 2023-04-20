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
    public:
        Vector2 mousePoint;
        Events();
        ~Events();

        void HandleRectangleEvent(Rectangle &hitBox, const std::function<void(bool)> &click, const std::function<void(bool)> &hover);
    };
#endif

    struct ListObject
    {
        int key;
        std::string value;
    };

    struct HoveringItem
    {
        bool hovering = false;
        int index = 0;
    };

#ifndef LISTBOX_H
#define LISTBOX_H

    /*
    EXAMPLE OF LISTBOX INIT USING DEFAULT COLORS AND SIZE
        Components::ListBox myListBox = Components::ListBox();
        myListBox.position = {screenWidth / 2, screenHeight / 2};
        myListBox.inputObject = inputObjects;
        myListBox.fontSize = 40;
        myListBox.ListBoxInitialize();
    */
    class ListBox : public Events
    {
    private:
        Vector2 mousePoint;
        std::vector<Rectangle> clickableRecs;
        Rectangle listRectangle;
        Color textActiveColor;
        void ListBoxDrawItem(ListObject &obj);
        void ListBoxAction(ListObject &obj);
        void ListBoxRectangleDraw();
        HoveringItem hoveringItem;

    public:
        std::vector<ListObject> data;
        ListObject itemClicked;
        Vector2 position;
        int width = 500;
        int fontSize = 16;
        bool includeIndex = true;
        bool transparent = false;

        Color textActionColor = DARKGREEN;
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