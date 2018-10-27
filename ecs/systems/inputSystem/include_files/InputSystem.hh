#pragma once

#include <map>
#include <string>
#include "protocol.hh"
#include "entityType.hh"
#include "KeyCollection.hh"
#include "directionComponent.hh"
#include "velocityComponent.hh"
#include "attackComponent.hh"
#include "componentCollection.hpp"

namespace ecs {
  class InputSystem {
  private:
    typedef void (InputSystem::*_action)(std::string const &, ecs::entity,
					 ecs::directionComponent &,
					 ecs::velocityComponent &,
					 ecs::attackComponent &,
					 bool) const;
  public:
    InputSystem();
    ~InputSystem();
    bool update(ecs::entityCollection const &,
		ecs::componentCollection<ecs::directionComponent> &,
		ecs::componentCollection<ecs::velocityComponent> &,
		ecs::componentCollection<ecs::attackComponent> &) const;
  private:
    std::map<std::string, _action>	_actions;

    void	_moveLeft(std::string const &, ecs::entity, ecs::directionComponent &,
			  ecs::velocityComponent &,
			  ecs::attackComponent &, bool) const;
    void	_moveUp(std::string const &, ecs::entity, ecs::directionComponent &,
			ecs::velocityComponent &,
			ecs::attackComponent &, bool) const;
    void	_moveDown(std::string const &, ecs::entity, ecs::directionComponent &,
			  ecs::velocityComponent &,
			  ecs::attackComponent &, bool) const;
    void	_moveRight(std::string const &, ecs::entity, ecs::directionComponent &,
			   ecs::velocityComponent &,
			   ecs::attackComponent &, bool) const;
    // void	_escape(std::string const &, ecs::entity, ecs::directionComponent &,
    // 			ecs::velocityComponent &,
    // 			ecs::attackComponent &, bool) const;
    void	_attack(std::string const &, ecs::entity, ecs::directionComponent &,
			ecs::velocityComponent &,
			ecs::attackComponent &, bool) const;
    void	_something(std::string const &, ecs::entity, ecs::directionComponent &,
			   ecs::velocityComponent &,
			   ecs::attackComponent &, bool) const;

    event::key _getActionFromKey(int) const;
    void	_changeDirection(ecs::directionComponent &, float, float, bool) const;
    void	_changeVelocity(ecs::velocityComponent &, bool) const;
  };
}
