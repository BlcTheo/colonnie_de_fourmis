#ifndef CSYSTEM_HPP
#define CSYSTEM_HPP

#include <vector>
#include <list>
#include <memory>
#include "../../Ants/CAnt.hpp"
#include "../../resources/foods/CFood.hpp"

class CSystem {
private:
    std::vector<std::unique_ptr<CAnt>> m_ants;
    std::list<CFood> m_foods;

    float m_totalDuration;
    int m_workerCount;
    int m_collectedResources;

    float m_foodTimer;         
    float m_nextSpawnDelay;    
    float m_consumptionTimer;  
    float m_birthTimer;        

public:
    CSystem();
    ~CSystem() = default;

    void update(float deltaTime);
    void spawnFood(int count);

    const std::vector<std::unique_ptr<CAnt>>& getAnts() const { return m_ants; }
    const std::list<CFood>& getFoods() const { return m_foods; }
    
    float getTotalDuration() const { return m_totalDuration; }
    int getWorkerCount() const { return m_workerCount; }
    int getCollectedResources() const { return m_collectedResources; }
};

#endif