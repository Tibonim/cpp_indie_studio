#pragma once

#include "CustomException.hh"

namespace	indie {
  class		CollectionException : public CustomException {
  public:
    CollectionException(std::string const& what);
  };
}
