#pragma once

#include "NonCopyable.hh"
#include "componentType.hh"

namespace	ecs {
  class		HandlerEntitySystem : private NonCopyable {
  public:
    const entityCollection::entityList	update(entityCollection& entities,
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
					       collectionDefense& defense) const;
  private:
    bool	isRemovable(entity const id,
			    collectionHealth& health) const;
  };
}
