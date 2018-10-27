#pragma once

#include <stdexcept>

namespace	indie {
  class		CustomException : public std::exception {
  public:
    CustomException(std::string const& what);
    virtual ~CustomException() throw() = default;
    const char	*what() const throw();
  private:
    std::string	_what;
  };
}
