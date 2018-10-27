#include "EngineException.hh"

namespace	indie {
  EngineException::EngineException(std::string const& what)
    : CustomException{ what } {}
}
