#include <iostream>
#include <algorithm>
#include "CollectionException.hh"
#include "HandlerEntitySystem.hh"

namespace	ecs {
  bool		HandlerEntitySystem::isRemovable(entity const id,
						 collectionHealth& health) const {
    try {
      auto healthComponent = health.getComponent(id);
      return healthComponent.live <= 0.f;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  const entityCollection::entityList	HandlerEntitySystem::update(entityCollection& entities,
							    collectionHealth& health,
							    collectionDir& dir,
							    collectionVelocity& vel,
							    collectionPos& pos,
							    collectionStuff& stuff,
							    collectionGraphic& graphic,
							    collectionStrength& strength,
							    collectionFaction& faction,
							    collectionScript& script,
							    collectionRange& range,
							    collectionPlayer& player,
							    collectionDamage& damage,
							    collectionDefense& defense) const {
    auto entityToRemove = entities.getEntitiesOf([&, this](entity const id) {
	return this->isRemovable(id, health);
      });
    entityCollection::entityList	idToRemove{};
    std::for_each(entityToRemove.begin(), entityToRemove.end(),
		  [&](entity const id) {
		    idToRemove.push_back(id);
		  });
    return idToRemove;
  }
}
