#pragma once

#include "entityType.hh"

namespace	ecs {
  struct	graphicComponent {
    entity	id;
    std::string	meshName;
    std::string	textureName;
    std::string	animationName;
  };
}
