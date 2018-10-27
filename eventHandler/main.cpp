#include <iostream>
#include "eventHandler.hh"

int		main() {
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 3, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 4, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 5, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 6, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 7, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 8, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 9, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 10, true });
  event::eventHandler::push(event::eventProtocol{ event::action::ASCII, 11, true });
  auto e =  event::eventHandler::pop();
  std::cout << e.id << std::endl;
  auto e1 = event::eventHandler::pop();
  std::cout << e1.id << std::endl;
  auto e2 = event::eventHandler::pop();
  std::cout << e2.id << std::endl;
  auto e3 = event::eventHandler::pop();
  std::cout << e3.id << std::endl;
  auto e4 = event::eventHandler::pop();
  std::cout << e4.id << std::endl;
  auto e5 = event::eventHandler::pop();
  std::cout << e5.id << std::endl;
  auto e6 = event::eventHandler::pop();
  std::cout << e6.id << std::endl;
  auto e7 = event::eventHandler::pop();
  std::cout << e7.id << std::endl;
  auto e8 = event::eventHandler::pop();
  std::cout << e8.id << std::endl;
}
