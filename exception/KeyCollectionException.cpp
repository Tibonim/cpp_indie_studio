#include "KeyCollectionException.hh"

namespace	indie {
  KeyCollectionException::KeyCollectionException(std::string const& what)
    : CustomException{ what } {}
}
