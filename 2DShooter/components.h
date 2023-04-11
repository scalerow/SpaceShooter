#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>
#include <raylib.h>

namespace Components
{
   struct ListObject
    {
        int key;
        std::string value;
    };

    #ifndef LISTBOX_H
    #define LISTBOX_H
    class ListBox
    {
    private:
        Vector2 mousePoint;
        Events::DefaultEvent event;
        void ListBoxActions(void (*func)());
        void ListBoxDraw();

    public:
        std::vector<ListObject> inputObject;
        std::vector<Rectangle> clickableRecs;
        Vector2 position;
        int width;
        int fontSize; 
        bool includeIndex;
        bool transparent; 
        Color outlineColor = BLACK;
        Color fillColor = WHITE; 
        Color textColor = BLACK;
        ListBox();
        ~ListBox();

        
    };
    #endif

    #ifndef EVENTS_H
    #define EVENTS_H

    class Events
    {
        private: 

        public: 
        Vector2 mousePoint;
        struct DefaultEvent {
            bool hover = false;
            bool click = false;
        };

        Events();
        ~Events();

        DefaultEvent ClickRectangleEvent(Rectangle clickArea);
    };
    #endif
}
#endif