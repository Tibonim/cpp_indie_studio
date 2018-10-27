#pragma once

#include "CustomException.hh"

namespace       indie {
  class         SaveCollectionException : public CustomException {
  public:
    SaveCollectionException(std::string const& what);
  };
}
