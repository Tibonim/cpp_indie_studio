#include "GameException.hh"

namespace	indie {
  GameException::GameException(std::string const& message)
    : CustomException{ message } {}
}
