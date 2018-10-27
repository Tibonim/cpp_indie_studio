#pragma once

#include "entityType.hh"

namespace	ecs {
  struct	speedUpComponent {
    entity	id;
    float	value;
    bool	isUsed;
  };
}
