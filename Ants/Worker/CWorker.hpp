#ifndef CWORKER_HPP
#define CWORKER_HPP

#include "../CAnt.hpp"

class CWorker : public CAnt {
private:
    bool m_hasFood; // Indique si l'ouvrière transporte une ressource

public:
    // Constructeur : initialise l'ouvrière à une position donnée
    CWorker(float x, float y);

    // Mise à jour de la logique (mouvement aléatoire ou retour reine)
    void update(float deltaTime) override;

    // Rendu graphique (rond noir ou vert)
    void draw(sf::RenderWindow& window) const override;

    // Getters et Setters pour la gestion des ressources
    bool hasFood() const { return m_hasFood; }
    void setHasFood(bool val) { m_hasFood = val; }

    // Permet au système de forcer la position (pour le guidage vers la nourriture)
    void setPosition(const sf::Vector2f& newPos) { m_position = newPos; }
};

#endif