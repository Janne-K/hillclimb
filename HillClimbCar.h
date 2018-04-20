#ifndef __HILLCLIMB_CAR_H__
#define __HILLCLIMB_CAR_H__

#include <HillClimbUtility.h>
#include <HillClimbRoad.h>
#include <HillClimbCarWheel.h>

namespace hillclimb {
    class HillClimbCar {
    public:
        HillClimbCar(const double x, const double y, const double scale);
        void update(std::shared_ptr<HillClimbRoad> road, const double dt);
        void updateThrottle(const double dthrottle);
        double getPositionY();
        double getTransitionX(const double dt);
        double getAngle();
        bool touchesRoad();
        void reset(const double y);
    private:
        const double X_POS;
        const double SCALE;
        double y;
        double v_x;
        double v_y;
        double a_x;
        double a_y;
        double angle;
        double v_ang;
        double a_ang;
        double throttle;
        std::shared_ptr<HillClimbCarWheel> leftWheel;
        std::shared_ptr<HillClimbCarWheel> rightWheel;
        std::vector<RoadPartTouching> roadPartsTouching;
    
        void updatePosY(const double dt);
        void updateVelocityY(const double dt);
        void updateVelocityX(const double dt);
        void updateAccelerations(const double dt);
        void updateAngle(const double dt);
        void updateAngularVelocity(const double dt);
        void updateAngularAcceleration(const double dt);
        void updateRoadPartsTouching();
        void updateWheels(std::shared_ptr<HillClimbRoad> road);
    };
}

#endif // __HILLCLIMB_CAR_H__