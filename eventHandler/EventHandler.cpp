#include <algorithm>
#include <stdexcept>
#include "EventHandlerException.hh"
#include "EventHandler.hh"

namespace	event {
  EventHandler::eventQueue	EventHandler::_queue{};

  void	EventHandler::push(eventProtocol const& protocol) {
    _queue.push_back(protocol);
  }

  eventProtocol	EventHandler::pop() {
    if (_queue.empty())
      throw indie::EventHandlerException{ "Queue is empty" };
    auto event = _queue.front();
    _queue.pop_front();
    return event;
  }
}
