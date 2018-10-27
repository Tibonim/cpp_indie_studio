#pragma once

#include "View.hh"
#include "NonCopyable.hh"
#include "componentType.hh"
#include "entityType.hh"
#include "entityCollection.hh"

namespace	ecs {
  class		PhysicSystem : private NonCopyable {
  public:
    bool       update(ov::View *, entityCollection const &collection,
		      collectionDir &direction,
		      collectionVelocity &velocity,
		      collectionPos &pos,
		      collectionGraphic& graphic,
		      collectionFaction& faction) const;
  private:
    bool	getGoodEntities(entity id, collectionDir &direction,
				collectionVelocity &velocity,
				collectionPos &pos, collectionGraphic& graph,
				collectionFaction& faction) const;
    bool	updateComponents(ov::View *, entity id, collectionDir &direction,
				 collectionVelocity &velocity,
				 collectionPos &pos, collectionGraphic& graph,
				 collectionFaction& faction) const;
    bool	getFactionFromCollision(entity const lhs, entity const rhs,
					collectionFaction& faction) const;
  };
}
