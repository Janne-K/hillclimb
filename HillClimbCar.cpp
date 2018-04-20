#include "HillClimbCar.h"

namespace hillclimb {
    HillClimbCar::HillClimbCar(const double x, const double y, const double scale)
            : X_POS(x), y(y), SCALE(scale) {
        leftWheel = std::make_shared<HillClimbCarWheel>(-57.0, -43.0, 18.0);
        rightWheel = std::make_shared<HillClimbCarWheel>(58.0, -43.0, 18.0);
    };
    
    void HillClimbCar::updateThrottle(const double dthrottle) {
        this->throttle += dthrottle;
    }
    
    double HillClimbCar::getTransitionX(const double dt) {
        return this->v_x * dt;
    }
            
    void HillClimbCar::updateVelocityX(const double dt) {
        this->v_x += this->a_x * dt;
    }
    
    void HillClimbCar::updatePosY(const double dt) {
        this->y += this->v_y * dt;
    }
    
    void HillClimbCar::updateVelocityY(const double dt) {
        this->v_y += this->a_y * dt;
    }
    
    void HillClimbCar::updateAccelerations(const double dt) {
        /*
        An algorithm for updating the horizontal and vertical acceleration of the car. Lots of physics and math.
        You can use this or come up with something better.*/

        const double GRAVITY = 200.0;

        double slope;
        double normalAngle;
        double projectionForce;
        double projectionVelocity;
        double supportForce;

        double residualForce;
        double residualVelocity;
        double residualForceAngle;
        double residualVelocityAngle;

        double residualVelocityX = this->v_x;
        double residualVelocityY = this->v_y;
        double residualForceX = this->leftWheel->getForceX() + this->rightWheel->getForceX();
        double residualForceY = this->leftWheel->getForceY() + this->rightWheel->getForceY() - GRAVITY;

        for (auto roadPart: this->roadPartsTouching) {
            slope = roadPart.slope;
            normalAngle = calculateNormalAngleFromSlope(slope);
            residualForce = calculateHypotenuse(residualForceX, residualForceY);
            residualVelocity = calculateHypotenuse(residualVelocityX, residualVelocityY);
            residualForceAngle = calculateAngleFromComponents(residualForceX, residualForceY);
            residualVelocityAngle  = calculateAngleFromComponents(residualVelocityX, residualVelocityY);
            projectionForce = calculateProjection(residualForce, residualForceAngle, normalAngle);
            projectionVelocity = calculateProjection(residualVelocity, residualVelocityAngle, normalAngle);
            if (projectionVelocity + projectionForce * dt > 0) {
                supportForce = projectionVelocity / dt + projectionForce;
                residualForceX -= supportForce * cos(normalAngle);
                residualForceY -= supportForce * sin(normalAngle);
                residualVelocityX += residualForceX * dt;
                residualVelocityY += residualForceY * dt;
            }
        }
        this->a_x = residualForceX;
        this->a_y = residualForceY;
    }
    
    void HillClimbCar::updateAngle(const double dt) {

    }
    
    void HillClimbCar::updateAngularVelocity(const double dt) {

    }
    
    void HillClimbCar::updateAngularAcceleration(const double dt) {
        /*
        Very crude algorithm for the angular acceleration of the car.
        You can use this or come up with something better.

        const double PARALLEL_WITH_ROAD = 0.02;
        const double ALMOST_PARALLEL_WITH_ROAD = 0.05;
        const double DIFF_FACTOR = 200;
        const double ANGULAR_ACCELERATION = 3.0;
        const double STEEP_SLOPE = RIGHT_ANGLE / 4;

        double slope;
        double slopeAngle;
        double angleDiff;
        double angleDiffAbs;

        for (auto roadPart: this->roadPartsTouching) {
            slope = roadPart.slope;
            slopeAngle = atan(slope);
            angleDiff = calculateAngleDiff(slopeAngle, -this->angle);
            angleDiffAbs = std::abs(angleDiff);

            if (angleDiffAbs <= PARALLEL_WITH_ROAD) {
                this->a_ang = -this->v_ang / dt;
            } else if (angleDiffAbs <= ALMOST_PARALLEL_WITH_ROAD) {
                this->a_ang = -this->v_ang / dt - angleDiff * DIFF_FACTOR;
            } else if (angleDiffAbs <= RIGHT_ANGLE / 2 || slope < -STEEP_SLOPE || slope > STEEP_SLOPE) {
                this->a_ang = -angleDiff * ANGULAR_ACCELERATION;
            }
        }*/
    }
    
    void HillClimbCar::updateRoadPartsTouching() {
        roadPartsTouching.clear();
        
        for (auto roadPart: this->leftWheel->getRoadPartsTouching()) {
            roadPartsTouching.push_back(roadPart);
        }
        /*
        combine roadPartsTouching of leftWheel and rightWheel into roadPartsTouching of car
        */
    }
    
    void HillClimbCar::updateWheels(std::shared_ptr<HillClimbRoad> road) {
        this->leftWheel->clearPreviousState();
        this->rightWheel->clearPreviousState();
        this->leftWheel->updateState(this->throttle, {this->X_POS, this->y},
                this->angle, road);
        this->rightWheel->updateState(this->throttle, {this->X_POS, this->y},
                this->angle, road);
        /*
        clear previous state of wheels
        update state of wheels*/
    }
    
    double HillClimbCar::getPositionY() {
        return this->y;
    }
    
    // function getAngle
    
    // function touchesRoad
    
    
    void HillClimbCar::update(std::shared_ptr<HillClimbRoad> road, const double dt) {
        this->updateRoadPartsTouching();
        this->updateWheels(road);
        this->updateAngularAcceleration(dt);
        this->updateAngularVelocity(dt);
        this->updateAngle(dt);
        this->updateAccelerations(dt);
        this->updateVelocityX(dt);
        this->updateVelocityY(dt);
        this->updatePosY(dt);
   }
    
    void HillClimbCar::reset(const double y) {
        this->y = y;
        this->v_x = 0.0;
        this->v_y = 0.0;
        this->a_x = 0.0;
        this->a_y = 0.0;
        this->angle = 0.0;
        this->v_ang = 0.0;
        this->a_ang = 0.0;
        this->throttle = 0.0;
        
        //clear previous state of wheels
    }
}