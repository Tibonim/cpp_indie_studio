#pragma once

#include <array>
#include "componentType.hh"

namespace	ecs {
  class		DropSystem {
  public:
    bool	update(entityCollection& entities,
		       collectionPotion& potion,
		       collectionRenforce& renforce,
		       collectionSpeed& speed,
		       collectionStuff& stuff,
		       collectionPlayer& player) const;
  private:
    template<typename Component>
    bool	gotComponent(Component& component, entity const id) const;
    template<typename T>
    bool	isConcerned(T min, T max, T number) const;
    template<typename Component, typename T>
    entity	handleBoost(entityCollection& entities, Component& component,
			    std::array<T, 3> const &interval,
			    float valueToAttribute) const;
    bool	giveABoost(entity const id, entity const potion, entity const strength,
			   entity const speed, collectionStuff& stuff) const;
  };
}
