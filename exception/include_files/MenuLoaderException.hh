#pragma once

#include "CustomException.hh"

namespace       indie {
  class         MenuLoaderException : public CustomException {
  public:
    MenuLoaderException(std::string const& what);
  };
}
