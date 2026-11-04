#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <vector>
#include "Floor.h"
#include "entities/Monster.h"

class Progression {
private:
    std::vector<Floor*> floors;
    int current_floor;

public:
    Progression();
    ~Progression();

    void initializeFloors();
    Floor* getCurrentFloor() const;
    bool nextFloor();
    int getCurrentFloorNumber() const { return current_floor; }
    bool isGameComplete() const { return current_floor > 10; }
    
    // Monster factory
    static Monster* createMonsterForFloor(int floor_num);
};

#endif
