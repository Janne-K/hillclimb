#ifndef __HILLCLIMB_ROAD_H__
#define __HILLCLIMB_ROAD_H__

//Includes
#include <vector>
#include <HillClimbUtility.h>

namespace hillclimb {
    class HillClimbRoad {
    public:
        /*
        const int MAX_PART_COUNT = 100;
        const double X_ROAD_START = 0.0;
        const double Y_ROAD_START = 300.0;
        const double DEFAULT_ROAD_LENGTH = 20.0;*/
        
        HillClimbRoad(const double winWidth, const double winHeight);
        void move(const double x);
        std::vector <Coordinates> getPartCoords();
        int getPartCount();
        void reset();
    private:
       std::vector<Coordinates> partCoords;
       void addPart(double x, double y);
       //calculateNewPartX(prevPartX)
       double calculateNewPartY();
       void generatePartsAhead();
       //deletePartsBehind()
    };
}
/*
class HillClimbRoad
   public
     MAX_PART_COUNT
     X_ROAD_START
     Y_ROAD_START
     DEFAULT_ROAD_LENGTH

     HillClimbRoad(winWidth, winHeight)
     move(x)
     getPartCoords()
     getPartCount()
     reset()
   private
       partCoords
       addPart(x, y)
       calculateNewPartX(prevPartX)
       double calculateNewPartY()
       void generatePartsAhead()
       deletePartsBehind()
*/
#endif // __HILLCLIMB_ROAD_H__