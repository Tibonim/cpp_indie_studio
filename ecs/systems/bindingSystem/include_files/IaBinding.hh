#pragma once

#include "selene.h"
#include "NonCopyable.hh"
#include "BinderComponent.hh"

namespace	ecs {
  class		IaBinding : private NonCopyable {
  public:
    IaBinding();
    void			bindFile(std::string const& fileName);
    void			setBinder(BinderComponent &component);
  private:
    sel::State			_bindFile;
    BinderComponent		*_binder;
  };
}
