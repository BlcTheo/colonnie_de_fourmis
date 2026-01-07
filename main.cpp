/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "system/display/CDisplay.hpp"
#include "system/system/CSystem.hpp"
#include <SFML/Graphics.hpp>

int main() {
    // 1. Initialisation de l'affichage (Fenêtre + HUD)
    // La fenêtre est créée avec une résolution de 1280x720 par défaut
    CDisplay display;

    // 2. Initialisation du système de simulation
    // Le constructeur de CSystem va créer la Reine, les ouvrières et la nourriture
    CSystem simulation;

    // 3. Horloge pour la gestion du temps (DeltaTime)
    // Essentiel pour que la vitesse de déplacement soit indépendante du processeur
    sf::Clock clock;

    // Boucle principale de l'application
    while (display.isOpen()) {
        
        // --- ÉTAPE A : Gestion des événements (clavier, fermeture fenêtre) ---
        display.handleEvents();

        // --- ÉTAPE B : Calcul du temps écoulé (Delta Time) ---
        // On récupère le temps en secondes écoulé depuis la dernière image
        float deltaTime = clock.restart().asSeconds();

        // --- ÉTAPE C : Mise à jour de la logique ---
        // On met à jour la position des fourmis, les ressources et le chronomètre global
        simulation.update(deltaTime);

        // --- ÉTAPE D : Rendu graphique ---
        // On envoie l'objet simulation complet à la méthode render pour qu'elle puisse
        // lire les positions des entités et les statistiques du HUD
        display.render(simulation);
    }

    return 0;
}