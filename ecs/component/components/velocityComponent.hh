#pragma once

#include "entityType.hh"

#define MAX_VELOCITY 2.0f
#define VELOCITY_STEP 0.2f

namespace ecs {
  struct velocityComponent {
    entity	id;
    float	velocity;
    float	boost;
  };
}
