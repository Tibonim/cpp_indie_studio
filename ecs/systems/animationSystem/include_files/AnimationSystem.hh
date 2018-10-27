#pragma once

#include "NonCopyable.hh"
#include "componentType.hh"

namespace	ecs {
  class		AnimationSystem : private NonCopyable {
  public:
    bool	update(entityCollection const& entities,
		       collectionGraphic& graphic,
		       collectionVelocity& velocity,
		       collectionAttack& attack) const;
  private:
    bool	getAnimatedEntity(entity const id,
				  collectionGraphic& graphic,
				  collectionVelocity& velocity) const;
    bool	getAttackEntity(entity const id,
				collectionGraphic& graphic,
				collectionAttack& attack) const;
    void	updateGraphicEntity(entity const id,
				    collectionGraphic& graphic,
				    collectionVelocity& velocity) const;
    void	updateAttackAnimation(entity const id,
				      collectionGraphic& graphic,
				      collectionAttack& attack) const;
  };
}
