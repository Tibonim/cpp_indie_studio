#pragma once

#include "NonCopyable.hh"

namespace	indie {
  class		IModel {
  public:
    virtual ~IModel() = default;
    virtual bool	update() = 0;
  };
}
