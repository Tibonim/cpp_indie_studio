#pragma once

#include "CustomException.hh"

namespace	indie {
  class		KeyCollectionException : public CustomException {
  public:
    KeyCollectionException(std::string const& what);
  };
}
