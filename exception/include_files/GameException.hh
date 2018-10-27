#pragma once

#include "CustomException.hh"

namespace	indie {
  class		GameException : public CustomException {
  public:
    GameException(std::string const& message);
  };
}
