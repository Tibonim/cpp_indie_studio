#pragma once

#include "CustomException.hh"

namespace	indie {
  class		EngineException : public CustomException {
  public:
    EngineException(std::string const& what);
  };
}
