#include "CFood.hpp"

// Constructeur : initialise la position et le stock à 50
CFood::CFood(float x, float y) : m_position(x, y), m_quantity(50) {}

void CFood::update(float deltaTime) {
    // Pour l'instant, la nourriture ne bouge pas et ne change pas seule
}

void CFood::draw(sf::RenderWindow& window) const {
    // Calcul du rayon : 2px minimum, 8px maximum quand quantity = 50
    float radius = 2.0f + (static_cast<float>(m_quantity) / 50.0f) * 6.0f;
    
    sf::CircleShape shape(radius);
    
    // Centrage du cercle sur sa position
    shape.setOrigin({radius, radius});
    shape.setPosition(m_position);
    
    // Couleur vert forêt (plus ou moins sombre selon tes goûts)
    shape.setFillColor(sf::Color(50, 205, 50)); 
    
    window.draw(shape);
}

void CFood::decreaseQuantity() {
    if (m_quantity > 0) {
        m_quantity--;
    }
}