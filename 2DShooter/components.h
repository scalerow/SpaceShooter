#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <string>
#include <raylib.h>

namespace CompLib
{
    struct ListObject
    {
        int key;
        std::string value;
    };

    class Components
    {
    private:
        Vector2 mousePoint;

        void ListBoxActions(Rectangle entries[4], void (*func)());
        void ListBoxDraw(std::vector<ListObject> inputObject, Vector2 position, int width, int fontSize, bool includeIndex, bool transparent, Color outlineColor, Color fillColor, Color textColor);

    public:
        Components();
        ~Components();

        void ListBox(std::vector<ListObject> inputObject, Vector2 position, int width, int fontSize, bool includeIndex, bool transparent, Color outlineColor, Color fillColor, Color textColor);
    };

}
#endif