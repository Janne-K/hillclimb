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
        double getTransitionX(double dt);
        double getAngle();
        bool touchesRoad();
        void reset();
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
        //std::shared_ptr<HillClimbCarWheel> leftWheel;
        //std::shared_ptr<HillClimbCarWheel> rightWheel;
        //roadPartsTouching
    
        void updatePosY(double dt);
        void updateVelocityY(double dt);
        void updateVelocityX(double dt);
        void updateAccelerations(double dt);
        void updateAngle(double dt);
        void updateAngularVelocity(double dt);
        void updateAngularAcceleration(double dt);
        void updateRoadPartsTouching();
        void updateWheels(std::shared_ptr<HillClimbRoad> road);
    };
}

/* includes 

namespace

    class HillClimbCar
      public
        HillClimbCar(x, y, scale)
        update(road, dt)
        updateThrottle(dthrottle)
        getPositionY()
        getTransitionX(dt)
        getAngle()
        touchesRoad()
        reset(y)
      private
        X_POS
        SCALE
        y
        v_x
        v_y
        a_x
        a_y
        angle
        v_ang
        a_ang
        throttle
        leftWheel
        rightWheel
        roadPartsTouching
    
        updatePosY(dt)
        updateVelocityY(dt)
        updateVelocityX(dt)
        updateAccelerations(dt)
        updateAngle(dt)
        updateAngularVelocity(dt)
        updateAngularAcceleration(dt)
        updateRoadPartsTouching()
        updateWheels(road)

*/
#endif // __HILLCLIMB_CAR_H__