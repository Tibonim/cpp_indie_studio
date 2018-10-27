#include <algorithm>
#include "Spawner.hh"
#include "CollectionException.hh"
#include "SpawnSystem.hh"
#include "factionComponent.hh"

namespace	ecs {
  bool		SpawnSystem::isConcerned(entity const id,
					 collectionFaction& faction) const {
    try {
      auto &factionComponent = faction.getComponent(id);
      return factionComponent.type == ecs::faction::EVIL;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		SpawnSystem::update(entityCollection& collection,
				    collectionComponent& components) const {
    auto entitiesList = collection.getEntitiesOf([&components, this](entity id) {
	return this->isConcerned(id, (*components.faction));
      });
    if (!entitiesList.empty())
      return false;
    indie::Spawner::loadSpawnComponent(components, collection);
    return true;
  }
}
