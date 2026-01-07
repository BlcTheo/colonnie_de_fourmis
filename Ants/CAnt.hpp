#ifndef CANT_HPP
#define CANT_HPP

#include <SFML/Graphics.hpp>

class CAnt {
protected:
    sf::Vector2f m_position;

public:
    CAnt(float x, float y) : m_position(x, y) {}
    virtual ~CAnt() = default;

    virtual void update(float deltaTime) = 0;
    // Cette méthode permet à CDisplay de dessiner n'importe quelle fourmi
    virtual void draw(sf::RenderWindow& window) const = 0; 
    virtual sf::Vector2f getPosition() const { return m_position; }
};

#endif