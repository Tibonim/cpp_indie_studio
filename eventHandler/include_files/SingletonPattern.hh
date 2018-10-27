#pragma once

namespace	event {
  class		SingletonPattern {
  public:
    SingletonPattern() = delete;
    ~SingletonPattern() = delete;
    SingletonPattern(SingletonPattern const& copy) = delete;
    SingletonPattern	&operator=(SingletonPattern const &copy) = delete;
  };
}
