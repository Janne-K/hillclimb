#include "HillClimbRoad.h"

namespace hillclimb {
    const double ROAD_LENGTH_FACTOR = 2.0;
    
    HillClimbRoad::HillClimbRoad(const double winWidth, const double winHeight) {
        
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
