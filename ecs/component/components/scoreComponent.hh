#pragma once

#include "entityType.hh"

namespace	ecs {
  struct	scoreComponent {
    entity	id;
    std::size_t	value;
  };
}
