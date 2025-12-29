#include "system/display/display.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

Display::Display(unsigned int width, unsigned int height, const char* title)
    : m_window(sf::VideoMode({width, height}), title)   // SFML 3 : Vector2u
{
    m_window.setFramerateLimit(60);
}

bool Display::isOpen() const
{
    return m_window.isOpen();
}

void Display::handleEvents()
{
    // SFML 3 : pollEvent() renvoie std::optional<sf::Event>
    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void Display::render()
{
    m_window.clear(sf::Color::Black);
    m_window.display();
}
