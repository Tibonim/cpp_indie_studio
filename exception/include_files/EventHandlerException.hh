#pragma once

#include "CustomException.hh"

namespace	indie {
  class		EventHandlerException : public CustomException {
  public:
    EventHandlerException(std::string const& what);
  };
}
