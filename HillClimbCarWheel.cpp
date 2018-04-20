#include "HillClimbCarWheel.h"

namespace hillclimb {
    HillClimbCarWheel::HillClimbCarWheel(double x_offset, double y_offset, double radius)
            : OFFSET({x_offset, y_offset}), RADIUS(radius) {};

    double HillClimbCarWheel::getForceX() {
        return this->force_x;
    }
    
    double HillClimbCarWheel::getForceY() {
        return this->force_y;
    }
    
    std::vector<RoadPartTouching> HillClimbCarWheel::getRoadPartsTouching() {
        return roadPartsTouching;
    }

    void HillClimbCarWheel::updatePosX(const double carX, const double carAngle) {
        this->x = carX + this->OFFSET.x;
    }

    void HillClimbCarWheel::updatePosY(const double carY, const double carAngle) {
        this->y = carY + this->OFFSET.y;
    }
    
    bool HillClimbCarWheel::touchesRoad() {
        return !(roadPartsTouching.empty());
    }

    void HillClimbCarWheel::clearPreviousState() {
        this->force_x = 0.0;
        this->force_y = 0.0;
        this->roadPartsTouching.clear();
       
    }
    void HillClimbCarWheel::updateForces(double throttle) {
        if (roadPartsTouching.size() > 0) {
            throttle /= roadPartsTouching.size();
        }
       
        const double FRICTION_CONST = 500.0;
       
        for (auto& roadPart: roadPartsTouching) {
            double slope = roadPart.slope;
            double slopeAngle = std::atan(slope);
            //double slopeAngle = calculateNormalAngleFromSlope(slope);
           
            double friction;
            if (slope >= 0.0) {
                friction = FRICTION_CONST * (slope + 1);
            } else {
                friction = FRICTION_CONST / (abs(slope) + 1);
            }
            double resThrottle = throttle - friction;
           
            std::cout << "Slope angle: " <<  slopeAngle << "\n";
            force_x += std::cos(slopeAngle) * resThrottle;
            force_y += std::sin(slopeAngle) * resThrottle;
            std::cout << force_x << ", " << force_y << "\n";
       /*
        loop through road parts touching
          get slope and slopeAngle
          if slope >= 0
              friction = SOME_FRICTION_CONST * (slope + 1)
          else
              friction = SOME_FRICTION_CONST / (abs(slope) + 1)
          resThrottle = throttle - friction
          increment force_x with cos(slopeAngle) * resThrottle
          increment force_y with sin(slopeAngle) * resThrottle*/
        }
    }

    void HillClimbCarWheel::updateRoadPartsTouching(std::shared_ptr<HillClimbRoad> road) {
        auto partCoords = road->getPartCoords();
        for (int i = 0; i < static_cast<int>(partCoords.size()) - 1; ++i) {
            double distance = calculateDistanceToLineSegment(this->x, this->y,
                    partCoords.at(i), partCoords.at(i + 1));
            if (distance < this->RADIUS) {
                RoadPartTouching partTouching;
                partTouching.slope = calculateSlope(partCoords.at(i), partCoords.at(i + 1));
                partTouching.wheelSubmersion = this->RADIUS - distance;
                this->roadPartsTouching.push_back(partTouching);
            }
        }
    }

    void HillClimbCarWheel::updateState(double throttle, Coordinates carPos,
            double carAngle, std::shared_ptr<HillClimbRoad> road) {
        this->updatePosX(carPos.x, carAngle);
        this->updatePosY(carPos.y, carAngle);
        this->updateRoadPartsTouching(road);
        this->updateForces(throttle);
   }

}