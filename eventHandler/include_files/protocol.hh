#pragma once

#include <entityType.hh>

namespace	event {
  struct	eventProtocol {
    int		keyCode;
    ecs::entity	id;
    bool	isPressed;
  };
}
