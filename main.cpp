#include <SFML/Graphics.hpp>
#include "system/display/display.hpp"

int main()
{
    Display display(800, 600, "Colonie de fourmis");

    while (display.isOpen()) {
        display.handleEvents();
        display.render();
    }

    return 0;
}
