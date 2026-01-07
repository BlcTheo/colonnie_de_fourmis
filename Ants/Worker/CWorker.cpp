#include "CWorker.hpp"
#include <cstdlib>
#include <cmath>

CWorker::CWorker(float x, float y) : CAnt(x, y), m_hasFood(false) {}

void CWorker::update(float deltaTime) {
    // Vitesse réduite à 50 pixels par seconde (au lieu de 100)
    float speed = 50.0f; 

    if (m_hasFood) {
        // Retour à la reine
        sf::Vector2f target(640.0f, 360.0f);
        sf::Vector2f direction = target - m_position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 2.0f) {
            m_position += (direction / distance) * speed * deltaTime;
        }
    } else {
        // Mouvement aléatoire plus lent
        float moveX = static_cast<float>((std::rand() % 3) - 1);
        float moveY = static_cast<float>((std::rand() % 3) - 1);
        
        m_position.x += moveX * speed * deltaTime;
        m_position.y += moveY * speed * deltaTime;
    }

    // Gestion des bords
    if (m_position.x < 0) m_position.x = 0;
    if (m_position.x > 1280) m_position.x = 1280;
    if (m_position.y < 35) m_position.y = 35; 
    if (m_position.y > 720) m_position.y = 720;
}

void CWorker::draw(sf::RenderWindow& window) const {
    sf::CircleShape body(3.f);
    body.setOrigin({3.f, 3.f});
    body.setPosition(m_position);
    
    // Couleur : Vert si chargée, Noir sinon
    body.setFillColor(m_hasFood ? sf::Color::Green : sf::Color::Black);
    window.draw(body);
}