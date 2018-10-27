#include "IaSystemException.hh"

namespace	indie {
  IaSystemException::IaSystemException(std::string const& message)
    : CustomException{ message } {}
}
