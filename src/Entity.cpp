#include "Entity.h"

void MovementEntity::calc_move() {
    
    // Determine the delta time:

    uint64_t delta = (SLD_GetPerformanceCounter() - this->last) / this->freq;

    // Determine the new velocity::

    this->x_vel += x_acc * delta;
    this->y_vel += y_acc * delta;

    // Determine the new position:

    this->x_pos += x_vel * delta;
    this->y_pos += y_vel * delta;
}
