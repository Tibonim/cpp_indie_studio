#pragma once

#include "entityType.hh"

namespace	ecs {
  enum		faction { EVIL = 0, NICE = 1 };

  struct	factionComponent {
    entity	id;
    faction	type;
  };
}
