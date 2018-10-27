#pragma once

#include "CustomException.hh"

namespace	indie {
  class		IaSystemException : public CustomException {
  public:
    IaSystemException(std::string const& message);
  };
}
