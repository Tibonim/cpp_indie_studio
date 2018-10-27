#include "CollectionException.hh"

namespace	indie {
  CollectionException::CollectionException(std::string const& what)
    : CustomException{ what } {}
}
