#include "EventHandler.hh"
#include "InputSystem.hh"
#include "KeyCollectionException.hh"
#include "EventHandlerException.hh"

#include <iostream>

namespace ecs {
  InputSystem::InputSystem() {
    _actions["moveRight"] = &InputSystem::_moveRight;
    _actions["moveUp"] = &InputSystem::_moveUp;
    _actions["moveDown"] = &InputSystem::_moveDown;
    _actions["moveLeft"] = &InputSystem::_moveLeft;
    // _actions["escape"] = &InputSystem::_escape;
    _actions["attack"] = &InputSystem::_attack;
  }

  InputSystem::~InputSystem() {

  }

  event::key InputSystem::_getActionFromKey(int key) const {
    return event::KeyCollection::getKey(key);
  }

  bool InputSystem::update(ecs::entityCollection const &,
			   ecs::componentCollection<ecs::directionComponent> &ccd,
			   ecs::componentCollection<ecs::velocityComponent> &ccv,
			   ecs::componentCollection<ecs::attackComponent> &ca) const {
    bool	run = true;

    while (run) {
      try {
	auto event = event::EventHandler::pop();
	auto keyInfo = _getActionFromKey(event.keyCode);
	auto it = _actions.find(keyInfo.action);
	auto  &direction = ccd.getComponent(event.id);
	auto  &velocity = ccv.getComponent(event.id);
	auto  &attack = ca.getComponent(event.id);
	if (it != _actions.end())
	  (this->*(it->second))(keyInfo.type, event.id, direction, velocity, attack, event.isPressed);
      }
      catch (indie::EventHandlerException const &) {
	run = false;
      }
      catch(indie::KeyCollectionException const &e) {
      }
      catch(indie::CollectionException const &e) {
      }
    }
    return true;
  }

  void InputSystem::_something(std::string const &, ecs::entity,
			       ecs::directionComponent &,
			       ecs::velocityComponent &,
			       ecs::attackComponent &, bool) const {
  }

  void InputSystem::_moveLeft(std::string const &,
			      ecs::entity id, ecs::directionComponent &dir,
			      ecs::velocityComponent &velocity,
			      ecs::attackComponent &, bool exec) const {
    _changeDirection(dir, -1.0f, 0.0f, exec);
    _changeVelocity(velocity, exec);
  }

  void InputSystem::_moveUp(std::string const &,
			    ecs::entity id, ecs::directionComponent &dir,
			    ecs::velocityComponent &velocity,
			    ecs::attackComponent &, bool exec) const {
    _changeDirection(dir, 0.0f, 1.0f, exec);
    _changeVelocity(velocity, exec);
  }

  void InputSystem::_moveDown(std::string const &, ecs::entity id,
			      ecs::directionComponent &dir,
			      ecs::velocityComponent &velocity,
			      ecs::attackComponent &, bool exec) const {
    _changeDirection(dir, 0.0f, -1.0f, exec);
    _changeVelocity(velocity, exec);
  }

  void InputSystem::_moveRight(std::string const &, ecs::entity id,
			       ecs::directionComponent &dir,
			       ecs::velocityComponent &velocity,
			       ecs::attackComponent &, bool exec) const {
    _changeDirection(dir, 1.0f, 0.0f, exec);
    _changeVelocity(velocity, exec);
  }

  // void InputSystem::_escape(std::string const &, ecs::entity, ecs::directionComponent &,
  // 			    ecs::velocityComponent &,
  // 			    ecs::attackComponent &, bool) const {
  //   //std::cout << "escape" << std::endl;
  // }

  void InputSystem::_attack(std::string const &, ecs::entity id,
			    ecs::directionComponent &,
			    ecs::velocityComponent &,
			    ecs::attackComponent &a, bool exec) const {
    a.isAttack = exec;
  }

  void InputSystem::_changeDirection(ecs::directionComponent &dir,
				     float x, float y, bool exec) const {
    dir.x = x;
    dir.z = y;
    return ;
    if (x)
      dir.x = (exec) ? x : 0.0f;
    if (y)
      dir.z = (exec) ? y : 0.0f;
  }

  void InputSystem::_changeVelocity(ecs::velocityComponent &velocity, bool exec) const {
    if (!exec) {
      velocity.velocity = 0.0f;
      return ;
    }
    velocity.velocity = MAX_VELOCITY;
    //velocity.velocity = (velocity.velocity > MAX_VELOCITY) ? MAX_VELOCITY : velocity.velocity;
  }
}
