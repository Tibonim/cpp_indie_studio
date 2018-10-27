#include "CustomException.hh"

namespace	indie {
  CustomException::CustomException(std::string const& what) : _what{ what } {}

  const char	*CustomException::what() const throw() {
    return _what.c_str();
  }
}
