#include "CSystem.hpp"
#include "../../Ants/Worker/CWorker.hpp"
#include "../../Ants/Queen/CQueen.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

CSystem::CSystem() 
    : m_totalDuration(0.0f), 
      m_workerCount(0), 
      m_collectedResources(100),   // Stock initial de survie
      m_foodTimer(0.0f),
      m_consumptionTimer(0.0f),
      m_birthTimer(0.0f)
{
    // Initialisation de la graine aléatoire
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Premier délai avant l'apparition de nourriture (3 à 5 sec)
    m_nextSpawnDelay = 3.0f + static_cast<float>(std::rand() % 201) / 100.0f;

    // --- CRÉATION DE LA COLONIE INITIALE ---
    float qX = 640.0f, qY = 360.0f;
    // Ajout de la Reine au centre
    m_ants.push_back(std::make_unique<CQueen>(qX, qY));

    // Ajout des 15 ouvrières de départ autour de la reine
    for(int i = 0; i < 15; ++i) {
        float oX = static_cast<float>((std::rand() % 100) - 50);
        float oY = static_cast<float>((std::rand() % 100) - 50);
        m_ants.push_back(std::make_unique<CWorker>(qX + oX, qY + oY));
        m_workerCount++;
    }

    // Génération de 5 gisements de nourriture au lancement
    spawnFood(5);
}

void CSystem::update(float deltaTime) {
    m_totalDuration += deltaTime;

    // --- 1. GESTION DE LA CONSOMMATION ET DE LA FAMINE (Toutes les 10s) ---
    m_consumptionTimer += deltaTime;
    if (m_consumptionTimer >= 10.0f) {
        int totalAnts = static_cast<int>(m_ants.size());
        
        // Si on a assez de ressources pour nourrir tout le monde
        if (m_collectedResources >= totalAnts) {
            m_collectedResources -= totalAnts;
        } 
        // Sinon, c'est la famine : une ouvrière meurt par ressource manquante
        else {
            int missingResources = totalAnts - m_collectedResources;
            m_collectedResources = 0; // On vide le stock

            int deaths = 0;
            auto it = m_ants.begin();
            while (it != m_ants.end() && deaths < missingResources) {
                // On ne tue que les ouvrières, pas la Reine
                if (dynamic_cast<CWorker*>(it->get())) {
                    it = m_ants.erase(it); 
                    deaths++;
                    m_workerCount--;
                } else {
                    ++it;
                }
            }
        }
        m_consumptionTimer = 0.0f;
    }

    // --- 2. GESTION DE LA NAISSANCE (Toutes les 10s) ---
    m_birthTimer += deltaTime;
    if (m_birthTimer >= 10.0f) {
        // Condition : Ressources >= 2 * Nombre de fourmis total
        if (m_collectedResources >= (static_cast<int>(m_ants.size()) * 2)) {
            float offX = static_cast<float>((std::rand() % 40) - 20);
            float offY = static_cast<float>((std::rand() % 40) - 20);
            
            // Création d'une nouvelle ouvrière près de la Reine
            m_ants.push_back(std::make_unique<CWorker>(640.0f + offX, 360.0f + offY));
            m_collectedResources -= 5; // Coût de "fabrication"
            m_workerCount++;
        }
        m_birthTimer = 0.0f;
    }

    // --- 3. GESTION DE L'APPARITION DE NOURRITURE ---
    m_foodTimer += deltaTime;
    if (m_foodTimer >= m_nextSpawnDelay) {
        spawnFood(1);
        m_foodTimer = 0.0f;
        m_nextSpawnDelay = 3.0f + static_cast<float>(std::rand() % 201) / 100.0f;
    }

    // --- 4. LOGIQUE INDIVIDUELLE DES FOURMIS ---
    for (auto& ant : m_ants) {
        CWorker* worker = dynamic_cast<CWorker*>(ant.get());
        if (worker) {
            // ÉTAT : RECHERCHE DE NOURRITURE
            if (!worker->hasFood()) {
                float detectionRadius = 30.0f; // Rayon de vision demandé

                for (auto it = m_foods.begin(); it != m_foods.end(); ) {
                    sf::Vector2f diff = it->getPosition() - worker->getPosition();
                    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
                    
                    // Si nourriture détectée : on fonce vers elle (Vitesse 65)
                    if (dist < detectionRadius) {
                        sf::Vector2f dir = it->getPosition() - worker->getPosition();
                        worker->setPosition(worker->getPosition() + (dir / dist) * 65.0f * deltaTime);
                    }

                    // Si contact (moins de 10px) : on ramasse
                    if (dist < 10.0f) {
                        worker->setHasFood(true);
                        it->decreaseQuantity(); // On puise dans le gisement (50 unités)
                        
                        // Si le gisement est vide, on le supprime
                        if (it->getQuantity() <= 0) {
                            it = m_foods.erase(it);
                            continue;
                        }
                    }
                    ++it;
                }
            } 
            // ÉTAT : TRANSPORT VERS LA REINE (640, 360)
            else {
                sf::Vector2f qPos(640.0f, 360.0f);
                sf::Vector2f diffQ = worker->getPosition() - qPos;
                float distQ = std::sqrt(diffQ.x * diffQ.x + diffQ.y * diffQ.y);
                
                // Si arrivée à la Reine : on dépose la ressource
                if (distQ < 15.0f) {
                    worker->setHasFood(false);
                    m_collectedResources++;
                }
            }
        }
        // Mise à jour du mouvement (aléatoire ou retour programmé)
        ant->update(deltaTime);
    }
}

void CSystem::spawnFood(int count) {
    for (int i = 0; i < count; ++i) {
        // Position aléatoire sécurisée sur la fenêtre
        float x = static_cast<float>(std::rand() % 1200 + 40);
        float y = static_cast<float>(std::rand() % 600 + 80);
        m_foods.emplace_back(x, y);
    }
}