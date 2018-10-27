#pragma once

#include "NonCopyable.hh"
#include "componentType.hh"

namespace	ecs {
  class		InventorySystem : private NonCopyable {
  public:
    bool	update(entityCollection const& entity,
		       collectionHealth& health,
		       collectionStrength& strength,
		       collectionVelocity& vel,
		       collectionStuff& stuff,
		       collectionPotion& potions,
		       collectionRenforce& renforce,
		       collectionSpeed& speed) const;
  private:
    template<typename collectionComponent>
    bool	isConcerned(entity const id, collectionComponent& component) const;
    void	handleInventory(entity const id, collectionStuff& stuff,
				collectionHealth& health,
				collectionStrength& strength,
				collectionVelocity& vel,
				collectionPotion& potion,
				collectionRenforce& renforce,
				collectionSpeed& speed) const;
    entity	checkBoostComponent(entity const boostId, entity const id,
				    collectionPotion& potion, collectionRenforce& r,
				    collectionSpeed& speed, collectionHealth& health,
				    collectionStrength& str,
				    collectionVelocity& vel) const;
    entity	handleBoost(entity const id,
			    entity const boostId,
			    collectionPotion& potion,
			    collectionHealth& health) const;
    entity	handleBoost(entity const id,
			    entity const boostId,
			    collectionRenforce& renforce,
			    collectionStrength& strength) const;
    entity	handleBoost(entity const id,
			    entity const boostId,
			    collectionSpeed& speed,
			    collectionVelocity& vel) const;
  };
}
