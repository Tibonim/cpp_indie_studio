#pragma once

#include "NonCopyable.hh"
#include "componentType.hh"

namespace	ecs {
  class		AttackSystem : private NonCopyable {
  public:
    bool	update(entityCollection const& collection,
		       collectionAttack& attack,
		       collectionDamage& damage,
		       collectionPosition& position,
		       collectionRange& range,
		       collectionStrength& strength,
		       collectionDirection& direction,
		       collectionFaction& faction) const;
  private:
    void	changeDamageOfEntity(entity id,
				     entityCollection const& collection,
				     collectionAttack const& attack,
				     collectionDamage &damage,
				     collectionPosition & position,
				     collectionRange & range,
				     collectionStrength & strength,
				     collectionDirection& direction,
				     collectionFaction& faction) const;
  };
}
