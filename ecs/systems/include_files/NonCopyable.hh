#pragma once

namespace	ecs {
  class		NonCopyable {
  public:
    NonCopyable() = default;
    NonCopyable(NonCopyable const& copy) = delete;
    NonCopyable	&operator=(NonCopyable const& copy) = delete;
  };
}
