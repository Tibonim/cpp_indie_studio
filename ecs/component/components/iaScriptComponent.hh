#pragma once

#include <string>
#include "entityType.hh"

namespace	ecs {
  struct	iaScriptComponent {
    entity	id;
    std::string	script;
  };
}
