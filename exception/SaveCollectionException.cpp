#include	"SaveCollectionException.hh"

namespace	indie {
  SaveCollectionException::SaveCollectionException(std::string const& what)
    : CustomException{ what } {}
}
