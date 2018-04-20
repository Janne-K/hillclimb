#ifndef __HILLCLIMB_CARWHEEL_H__
#define __HILLCLIMB_CARWHEEL_H__

#include <iostream>
#include <HillClimbUtility.h>
#include <HillClimbRoad.h>

namespace hillclimb {
    struct RoadPartTouching {
        double wheelSubmersion;
        double slope;
    };
    class HillClimbCarWheel {
    public:
        HillClimbCarWheel(double x_offset, double y_offset, double radius);
        double getForceX();
        double getForceY();
        std::vector<RoadPartTouching> getRoadPartsTouching();
        void updateState(double throttle, Coordinates carPos, double carAngle,
                std::shared_ptr<HillClimbRoad> road);
        void clearPreviousState();
    private:
        const Coordinates OFFSET;
        //OFFSET_ANGLE
        const double RADIUS;
        double x;
        double y;
        double force_x;
        double force_y;
        std::vector<RoadPartTouching> roadPartsTouching;
    
        bool touchesRoad();
        void updatePosX(const double carX, const double carAngle);
        void updatePosY(const double carY, const double carAngle);
        void updateRoadPartsTouching(std::shared_ptr<HillClimbRoad> road);
        void updateForces(double throttle);
    };
}

#endif // __HILLCLIMB_CARWHEEL_H__