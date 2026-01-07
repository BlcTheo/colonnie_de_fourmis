#ifndef CDISPLAY_HPP
#define CDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <memory>

// Forward declaration (Déclaration anticipée) : 
// Indique au compilateur que la classe CSystem existe sans inclure son .hpp.
// Cela permet de briser les dépendances circulaires entre CSystem et CDisplay.
class CSystem;

/**
 * @class CDisplay
 * @brief Gère la fenêtre de rendu, l'affichage des entités et l'interface utilisateur (HUD).
 */
class CDisplay {
private:
    // --- Propriétés de la fenêtre ---
    sf::RenderWindow m_window;  // Objet principal de SFML pour gérer la fenêtre et le rendu
    unsigned int m_width;       // Largeur de la fenêtre en pixels
    unsigned int m_height;      // Hauteur de la fenêtre en pixels
    std::string m_title;        // Titre affiché sur la barre de titre de la fenêtre

    // --- Éléments visuels de l'interface (HUD) ---
    sf::Font m_font;            // Police de caractères utilisée pour les textes
    
    // Utilisation de std::optional pour le texte :
    // Très utile avec SFML 3 pour s'assurer que l'objet texte n'est créé 
    // qu'une fois que la police est chargée avec succès.
    std::optional<sf::Text> m_statsText; 

    // Barre rectangulaire en haut de l'écran pour servir de fond aux statistiques
    sf::RectangleShape m_topBar;

public:
    /**
     * @brief Constructeur de la classe Display
     * @param width Largeur par défaut 1280
     * @param height Hauteur par défaut 720
     * @param title Titre de la simulation
     */
    CDisplay(unsigned int width = 1280, unsigned int height = 720, std::string title = "Simulation Colonie de Fourmis");
    
    /**
     * @brief Vérifie si la fenêtre est toujours ouverte (utile pour la boucle principale)
     * @return true si la fenêtre est active, false sinon.
     */
    bool isOpen() const;

    /**
     * @brief Analyse et traite les événements système (clavier, souris, clic sur fermer)
     */
    void handleEvents();

    /**
     * @brief Dessine l'ensemble de la simulation à l'écran
     * @param simulation Référence constante vers le système pour accéder aux données sans les modifier
     */
    void render(const CSystem& simulation); 
};

#endif