#ifndef CQUEEN_HPP
#define CQUEEN_HPP

#include "../CAnt.hpp"

class CQueen : public CAnt {
public:
    CQueen(float x, float y);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
};

#endif