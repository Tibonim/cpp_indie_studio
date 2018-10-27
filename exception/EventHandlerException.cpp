#include "EventHandlerException.hh"

namespace	indie {
  EventHandlerException::EventHandlerException(std::string const& what)
    : CustomException{ what } {}
}
