#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>
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
        struct DefaultEvent
        {
            bool hover = false;
            bool click = false;
        };

        Events();
        ~Events();

        DefaultEvent HandleRectangleEvent(Rectangle clickArea);
    };
#endif

    struct ListObject
    {
        int key;
        std::string value;
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
        bool ListBoxAction(ListObject &obj);
        void ListBoxRectangleDraw();

    public:
        std::vector<ListObject> inputObject;
        bool isItemClicked;
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
        ~ListBox();
    };
#endif

}
#endif