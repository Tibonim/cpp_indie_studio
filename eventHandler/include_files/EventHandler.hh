#pragma once

#include <list>
#include "SingletonPattern.hh"
#include "protocol.hh"

namespace	event {
  class		EventHandler : private SingletonPattern {
  public:
    typedef	std::list<eventProtocol>	eventQueue;
    static void			push(eventProtocol const& protocol);
    static eventProtocol	pop();
  private:
    static eventQueue		_queue;
  };
}
