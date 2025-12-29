#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

class Display {
public:
    Display(unsigned int width = 800, unsigned int height = 600, const char* title = "Fenetre SFML");

    bool isOpen() const;
    void handleEvents();
    void render();

private:
    sf::RenderWindow m_window;
};
