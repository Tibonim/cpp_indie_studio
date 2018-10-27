#include <iostream>
#include <random>
#include <type_traits>
#include "CollectionException.hh"
#include "DropSystem.hh"

namespace	ecs {
  template<typename T>
  bool		DropSystem::isConcerned(T min, T max, T number) const {
    static_assert(std::is_integral<T>::value, "Error: isConcerned need integral value");
    std::random_device		random;
    std::default_random_engine	engine{ random() };
    std::uniform_int_distribution<T>	distribution(min, max);
    T	value{ distribution(engine) };
    return value >= number;
  }

  template<typename Component, typename T>
  entity	DropSystem::handleBoost(entityCollection& entities,
					Component& component,
					std::array<T, 3> const &interval,
					float valueToAttribute) const {
    static_assert(std::is_integral<T>::value, "Error, random require integral");
    if (!isConcerned(interval[0], interval[1], interval[2]))
      return -1;
    auto newBoost = entities.createEntity();
    component.addComponent(newBoost, valueToAttribute, false);
    return newBoost;
  }

  template<typename Component>
  bool		DropSystem::gotComponent(Component& component, entity const id) const {
    try {
      component.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		DropSystem::giveABoost(entity const id,
				       entity const potion, entity const strength,
				       entity const speed,
				       collectionStuff& stuff) const {
      auto random = isConcerned(0, 2, 1);
      if (random && potion != -1) {
	stuff.getComponent(id).owned.push_back(potion);
	return true;
      }
      if (random && strength != -1) {
	stuff.getComponent(id).owned.push_back(strength);
	return true;
      }
      if (random && speed != -1) {
	stuff.getComponent(id).owned.push_back(strength);
	return true;
      }
      return false;
  }

  bool		DropSystem::update(entityCollection& entities,
				   collectionPotion& potion,
				   collectionRenforce& renforce,
				   collectionSpeed& speed,
				   collectionStuff& stuff,
				   collectionPlayer& player) const {
    auto boostPotion = handleBoost(entities, potion, std::array<int, 3>{ 1, 100, 95 },
				   30.f);
    auto boostStrength = handleBoost(entities, renforce,
				     std::array<int, 3>{ 1, 100, 99 }, 1.2);
    auto boostSpeed = handleBoost(entities, speed,  std::array<int, 3>{ 1, 100, 99 },
				  1.3);
    auto playerEntities = entities.getEntitiesOf([&stuff, &player, this]
						 (entity const id) {
	return this->gotComponent(player, id) && this->gotComponent(stuff, id);
      });
    for (auto it : playerEntities) {
      if (giveABoost(it, boostPotion, boostStrength, boostSpeed, stuff))
	return true;
    }
    return true;
  }

}
