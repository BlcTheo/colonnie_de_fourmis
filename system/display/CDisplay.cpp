#include "CDisplay.hpp"
#include "../system/CSystem.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * CONSTRUCTEUR
 * Initialise la fenêtre SFML, charge la police et configure le bandeau de l'interface (HUD).
 */
CDisplay::CDisplay(unsigned int width, unsigned int height, std::string title)
    : m_width(width), m_height(height), m_title(title) 
{
    // Création de la fenêtre de rendu avec une limite de 60 images par seconde
    m_window.create(sf::VideoMode({m_width, m_height}), m_title);
    m_window.setFramerateLimit(60);

    // CHARGEMENT DE LA POLICE
    // On utilise le chemin spécifique à Arch Linux pour DejaVuSans
    if (!m_font.openFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")) {
        std::cerr << "ERREUR : Police système introuvable. Vérifiez l'installation de ttf-dejavu." << std::endl;
    }

    // INITIALISATION DE L'OBJET TEXTE (m_statsText est un std::optional)
    m_statsText.emplace(m_font);
    m_statsText->setCharacterSize(18);
    m_statsText->setFillColor(sf::Color::White); // Couleur par défaut : blanc
    m_statsText->setPosition({15.f, 5.f});       // Positionnement en haut à gauche

    // CONFIGURATION DU BANDEAU NOIR (HUD)
    // On crée un rectangle qui fait toute la largeur de la fenêtre
    m_topBar.setSize({static_cast<float>(m_width), 35.f});
    m_topBar.setFillColor(sf::Color(0, 0, 0, 200)); // Noir avec une légère transparence
}

/**
 * Vérifie si la fenêtre est toujours ouverte
 */
bool CDisplay::isOpen() const {
    return m_window.isOpen();
}

/**
 * Gère les entrées utilisateur (clavier, souris, fermeture de fenêtre)
 */
void CDisplay::handleEvents() {
    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

/**
 * Rendu principal de la simulation
 * @param simulation : Référence vers le système contenant les données (fourmis, nourriture, ressources)
 */
void CDisplay::render(const CSystem& simulation) {
    // Effacement de l'écran avec une couleur "sable" (Beige)
    m_window.clear(sf::Color(245, 222, 179)); 

    // 1. DESSIN DES ENTITÉS DU MONDE
    // On dessine d'abord la nourriture (couche inférieure)
    for (const auto& food : simulation.getFoods()) { 
        food.draw(m_window); 
    }
    
    // On dessine ensuite les fourmis (couche supérieure)
    for (const auto& ant : simulation.getAnts()) { 
        ant->draw(m_window); 
    }

    // 2. DESSIN DE L'INTERFACE (HUD)
    // On dessine le bandeau noir en haut
    m_window.draw(m_topBar);

    // 3. MISE À JOUR ET DESSIN DU TEXTE DES STATISTIQUES
    if (m_statsText.has_value()) {
        size_t antCount = simulation.getAnts().size();
        int resources = simulation.getCollectedResources();

        // Construction dynamique de la chaîne d'affichage
        std::stringstream ss;
        ss << "Ressources: " << resources 
           << " | Temps: " << std::fixed << std::setprecision(1) << simulation.getTotalDuration() << "s"
           << " | Population: " << antCount
           << " | Sources Food: " << simulation.getFoods().size();
        
        m_statsText->setString(ss.str());

        // LOGIQUE D'ALERTE ANTICIPÉE
        // Si les ressources actuelles ne permettent pas de nourrir toute la population
        // lors du prochain cycle de 10 secondes, le texte passe au rouge.
        if (resources < static_cast<int>(antCount)) {
            // Couleur Rouge-Orange pour alerter du danger de famine
            m_statsText->setFillColor(sf::Color(255, 69, 0)); 
        } else {
            // Tout va bien : le stock est suffisant
            m_statsText->setFillColor(sf::Color::White);
        }

        // Dessin final du texte par-dessus le bandeau noir
        m_window.draw(*m_statsText);
    }

    // Affichage du buffer de rendu sur la fenêtre physique
    m_window.display();
}