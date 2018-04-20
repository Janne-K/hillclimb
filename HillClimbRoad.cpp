#include "HillClimbRoad.h"

namespace hillclimb {
    const int MAX_PART_COUNT = 10;
    const double X_ROAD_START = 0.0;
    const double Y_ROAD_START = 600.0;
    const double DEFAULT_ROAD_LENGTH = 200.0;
    const double ROAD_LENGTH_FACTOR = 2.0;
    
    HillClimbRoad::HillClimbRoad(const double winWidth, const double winHeight) {
        
    }
    
    void HillClimbRoad::move(const double x) {
        for (auto& coords: this->partCoords) {
            coords.x -= x;
        }
        this->deletePartsBehind();
        this->generatePartsAhead();
    }
    
    int HillClimbRoad::getPartCount() {
        return static_cast<int>(this->partCoords.size());
    }
    
    std::vector <Coordinates> HillClimbRoad::getPartCoords() {
        return this->partCoords;
    }
    
    void HillClimbRoad::addPart(double x, double y) {
        Coordinates partCoord = {
            .x = x,
            .y = y
        };
        this->partCoords.push_back(partCoord);
    }
    
    double HillClimbRoad::calculateNewPartX(const double prevPartX) {
        double length = DEFAULT_ROAD_LENGTH * ROAD_LENGTH_FACTOR;
        return prevPartX + length;
    }
    
    double HillClimbRoad::calculateNewPartY() {
        return cocos2d::RandomHelper::random_real(Y_ROAD_START - 200.0,
                Y_ROAD_START + 200.0);
    }
    
    void HillClimbRoad::generatePartsAhead() {
        const int partsToGenerate = MAX_PART_COUNT - this->getPartCount();
        for (int i = 0; i < partsToGenerate; ++i) {
            Coordinates lastCoord = partCoords.back();
            addPart(calculateNewPartX(lastCoord.x), calculateNewPartY());
        }
    }
    
    void HillClimbRoad::deletePartsBehind() {
        while (partCoords.front().x < -DEFAULT_ROAD_LENGTH * ROAD_LENGTH_FACTOR) {
            partCoords.erase(partCoords.begin());
        }
    }
    
    void HillClimbRoad::reset() {
        partCoords.clear();
        this->addPart(X_ROAD_START, Y_ROAD_START);
        this->addPart(X_ROAD_START + DEFAULT_ROAD_LENGTH, Y_ROAD_START);
        this->generatePartsAhead();
    }
}
/* Includes

namespace

   ROAD_LENGHT_FACTOR = choose some road length factor

   HillClimbRoad constructor

   function getPartCount

   function getPartCoords

   function addPart

   function calculateNewPartX {
       randomize length of the new part using some factor
   }

   function calculateNewPartY {
       randomize y position of the end point of the new part
   }

   function generatePartsAhead {
      generate parts as many as MAX_PART_COUNT - currentPartCount
   }

   deletePartsBehind() {
      delete parts whose x < -DEFAULT_ROAD_LENGTH * ROAD_LENGTH_FACTOR
   }

   move(x) {
       move the x's of parts
       deletePartsBehind
       generatePartsAhead
   }

   reset
       clear partCoords
       add two horizontal parts
       generatePartsAhead
   }
*/
