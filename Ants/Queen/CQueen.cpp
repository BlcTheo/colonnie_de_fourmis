#include "CQueen.hpp"

CQueen::CQueen(float x, float y) : CAnt(x, y) {}

void CQueen::update(float deltaTime) {
    //La reine ne bouge pas
}

void CQueen::draw(sf::RenderWindow& window) const {
    sf::CircleShape body(6.f);
    body.setOrigin({6.f, 6.f});
    body.setPosition(m_position);
    body.setFillColor(sf::Color::Blue);
    window.draw(body);
}