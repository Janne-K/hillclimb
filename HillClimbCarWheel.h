#ifndef __HILLCLIMB_CARWHEEL_H__
#define __HILLCLIMB_CARWHEEL_H__

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
        //getRoadPartsTouching()
        void updateState(double throttle, Coordinates carPos, double carAngle,
                std::shared_ptr<HillClimbRoad> road);
        void clearPreviousState();
    private:
        const Coordinates OFFSET;
        const double RADIUS;
    };
}
    

/* Guards
  
Includes

Namespace

    struct RoadPartTouching
        wheelSubmersion (how much wheel has submerged beneath the surface of the road)
        slope

    class CarWheel
      public
        CarWheel(x_offset, y_offset, radius)
        getForceX()
        getForceY()
        getRoadPartsTouching()
        updateState(throttle, carPos, carAngle, road)
        clearPreviousState()
      private:
        OFFSET
        OFFSET_ANGLE
        RADIUS
        x
        y
        force_x
        force_y
        roadPartsTouching
    
        touchesRoad()
        updatePosX(carX, carAngle)
        updatePosY(carY, carAngle)
        updateRoadPartsTouching(road)
        void updateForces(throttle)

Guards end
*/
#endif // __HILLCLIMB_CARWHEEL_H__