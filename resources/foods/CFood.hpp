#ifndef CFOOD_HPP
#define CFOOD_HPP

#include <SFML/Graphics.hpp>

class CFood {
private:
    sf::Vector2f m_position;
    int m_quantity;

public:
    CFood(float x, float y); // Signature uniquement

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const { return m_position; }
    int getQuantity() const { return m_quantity; }
    void decreaseQuantity();
};

#endif