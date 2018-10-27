#pragma once

#include "NonCopyable.hh"
#include "componentType.hh"

namespace	ecs {
  class		DamageSystem : private NonCopyable {
  public:
    bool	update(entityCollection const& entities,
		       collectionDamage& damage,
		       collectionDefense& defense,
		       collectionHealth& health) const;
  private:
    bool	isEntityHitable(entity const id, collectionDamage& damage,
				collectionDefense& defense,
				collectionHealth& health) const;
    void	changeHealthOfEntity(entity const id,
				     collectionDamage& damage,
				     collectionDefense& defense,
				     collectionHealth& health) const;
  };
}
