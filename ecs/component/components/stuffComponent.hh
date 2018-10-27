#pragma once

#include <vector>
#include "entityType.hh"

namespace	ecs {
  typedef std::vector<entity>	ownedList;

  struct	stuffComponent {
    entity	id;
    ownedList	owned;
  };
}
