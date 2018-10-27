#pragma once

#include "entityType.hh"

namespace ecs {
  struct positionComponent {
    entity	id;
    float	x;
    float	y;
    float	z;
  };
}
