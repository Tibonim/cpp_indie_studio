#pragma once

#include "entityType.hh"

namespace	ecs {
  struct	potionComponent {
    entity	id;
    float	value;
    bool	isUsed;
  };
}
