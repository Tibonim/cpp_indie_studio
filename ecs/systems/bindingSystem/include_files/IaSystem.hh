#pragma once

#include "NonCopyable.hh"
#include "componentType.hh"
#include "entityType.hh"
#include "entityCollection.hh"

namespace	ecs {
  class		IaSystem : private NonCopyable {
  public:
  bool		update(entityCollection const& entities,
		       collectionScript& script,
		       collectionDir& directions,
		       collectionPos& position,
		       collectionVelocity& vel,
		       collectionHealth& health,
		       collectionStrength& strength,
		       collectionFaction& faction,
		       collectionRange& range, collectionDamage& damages,
		       collectionAttack& attack) const;
  private:
    bool	getIaEntities(entity const id, collectionScript& script) const;
    bool	getIaEnnemies(entity const id, collectionDir& direction,
			      collectionPos& position, collectionVelocity& vel,
			      collectionHealth& health, collectionStrength& strength,
			      collectionFaction& faction,
			      collectionRange& range, collectionDamage& damage,
			      entity const iaId) const;
  };
}
