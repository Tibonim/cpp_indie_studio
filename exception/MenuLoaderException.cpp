#include "MenuLoaderException.hh"

namespace       indie {
  MenuLoaderException::MenuLoaderException(std::string const& what)
    : CustomException{ what } {}
}
