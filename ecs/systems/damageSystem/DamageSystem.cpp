#include <iostream>
#include <algorithm>
#include "CollectionException.hh"
#include "DamageSystem.hh"

namespace	ecs {
  bool		DamageSystem::isEntityHitable(entity const id,
					      collectionDamage& damage,
					      collectionDefense& defense,
					      collectionHealth& health) const {
    try {
      damage.getComponent(id);
      defense.getComponent(id);
      health.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  void		DamageSystem::changeHealthOfEntity(entity const id,
						   collectionDamage& damage,
						   collectionDefense& defense,
						   collectionHealth& health) const {
    auto &damageComponent = damage.getComponent(id);
    auto &defenseComponent = defense.getComponent(id);
    auto &healthComponent = health.getComponent(id);
    healthComponent.live -= (damageComponent.damageValue /
			     defenseComponent.defenseValue);
    if (healthComponent.live < 0)
      healthComponent.live = 0;
    damageComponent.damageValue = 0.f;
  }

  bool		DamageSystem::update(entityCollection const& collection,
				     collectionDamage& damage,
				     collectionDefense& defense,
				     collectionHealth& health) const {
    auto entities = collection.getEntitiesOf([&, this](entity const id) {
	return this->isEntityHitable(id, damage, defense, health);
      });
    std::for_each(entities.begin(), entities.end(), [&, this](entity id) {
	this->changeHealthOfEntity(id, damage, defense, health);
      });
    return true;
  }
}
