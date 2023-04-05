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
    }

    class components
    {
    private:
        Vector2 mousePoint;

        void ListBoxActions(Rectangle entries[4], void (*func)());
        Rectangle[] ListBoxDraw(std::vector<ListObject> inputObject, Vector2 position, int width, int fontSize, bool includeIndex, bool transparent,  Color outlineColor, Color fillColor,Color textColor);
    public:
        components(/* args */);
        ~components();

        void ListBox(std::vector<ListObject> inputObject,Vector2 position, int width, int fontSize, bool includeIndex, bool transparent,  Color outlineColor, Color fillColor, Color textColor)
    };
    
    
    
}
#endif