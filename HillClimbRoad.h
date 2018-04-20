#ifndef __HILLCLIMB_ROAD_H__
#define __HILLCLIMB_ROAD_H__

//Includes
#include <vector>
#include <HillClimbUtility.h>

namespace hillclimb {
    extern const int MAX_PART_COUNT;
    extern const double X_ROAD_START;
    extern const double Y_ROAD_START;
    extern const double DEFAULT_ROAD_LENGTH;
    
    class HillClimbRoad {
    public:
        
        HillClimbRoad(const double winWidth, const double winHeight);
        void move(const double x);
        std::vector <Coordinates> getPartCoords();
        int getPartCount();
        void reset();
    private:
       std::vector<Coordinates> partCoords;
       void addPart(double x, double y);
       double calculateNewPartX(const double prevPartX);
       double calculateNewPartY();
       void generatePartsAhead();
       void deletePartsBehind();
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