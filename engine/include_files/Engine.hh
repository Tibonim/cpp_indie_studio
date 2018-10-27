#pragma once

#include <string>
#include "IModel.hpp"

namespace indie {
  class Engine {
  public:
    Engine(std::string const &);
    ~Engine() = default;

    bool	run(IModel *) const;
  private:
 };
}
