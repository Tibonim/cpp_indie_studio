#include <iostream>
#include <algorithm>
#include "CollectionException.hh"
#include "InventorySystem.hh"

namespace	ecs {
  template<typename T>
  bool		InventorySystem::isConcerned(entity const id, T& component) const {
    try {
      component.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  entity	InventorySystem::handleBoost(entity const id,
					     entity const boostId,
					     collectionPotion& potion,
					     collectionHealth& health) const {
    auto &potionComponent = potion.getComponent(boostId);
    auto &healthComponent = health.getComponent(id);
    if (potionComponent.isUsed && healthComponent.live < 100) {
      healthComponent.live += potionComponent.value;
      if (healthComponent.live >= 100)
	healthComponent.live = 100;
      auto ret = potionComponent.id;
      potion.eraseComponent(boostId);
      return ret;
    }
    return -1;
  }

  entity	InventorySystem::handleBoost(entity const id,
					     entity const boostId,
					     collectionRenforce& renforce,
					     collectionStrength& strength) const {
    auto &renforceComponent = renforce.getComponent(boostId);
    auto &strengthComponent = strength.getComponent(id);
    if (renforceComponent.isUsed) {
      strengthComponent.boost += renforceComponent.value;
      if (strengthComponent.boost >= 1.5)
	strengthComponent.boost = 1.5f;
      renforce.eraseComponent(boostId);
      return renforceComponent.id;
    }
    return -1;
  }

  entity	InventorySystem::handleBoost(entity const id,
					     entity const boostId,
					     collectionSpeed& speed,
					     collectionVelocity& vel) const {
    auto &speedComponent = speed.getComponent(boostId);
    auto &velocityComponent = vel.getComponent(id);
    if (speedComponent.isUsed) {
      velocityComponent.boost += speedComponent.value;
      if (velocityComponent.boost >= 1.5)
	velocityComponent.boost = 1.5f;
      speed.eraseComponent(boostId);
      return speedComponent.id;
    }
    return -1;
  }

  entity	InventorySystem::checkBoostComponent(entity const boostId,
						     entity const id,
						     collectionPotion& potion,
						     collectionRenforce& renforce,
						     collectionSpeed& speed,
						     collectionHealth& health,
						     collectionStrength& str,
						     collectionVelocity& vel) const {
    if (isConcerned(boostId, potion)) {
      return handleBoost(id, boostId, potion, health);
    }
    if (isConcerned(boostId, renforce)) {
      return handleBoost(id, boostId, renforce, str);
    }
    if (isConcerned(boostId, speed)) {
      return handleBoost(id, boostId, speed, vel);
    }
    return -1;
  }

  void		InventorySystem::handleInventory(entity const id,
						 collectionStuff& stuff,
						 collectionHealth& health,
						 collectionStrength& strength,
						 collectionVelocity& vel,
						 collectionPotion& potion,
						 collectionRenforce& renforcement,
						 collectionSpeed& speed) const {
    auto& stuffComponent = stuff.getComponent(id);
    auto owned = stuffComponent.owned;
    std::vector<entity>	toErase;
    std::for_each(owned.begin(), owned.end(), [&, this](entity const id) {
	auto idE = this->checkBoostComponent(id, stuffComponent.id, potion,
					     renforcement, speed,
					     health, strength, vel);
	if (idE != -1)
	  toErase.push_back(idE);
      });
    std::for_each(toErase.begin(), toErase.end(), [&](entity const id) {
	std::cout << "ID STORED: " << id << std::endl;
	auto it = std::find(stuffComponent.owned.begin(), stuffComponent.owned.end(),
			    id);
	if (it != stuffComponent.owned.end())
	  stuffComponent.owned.erase(it);
      });
  }

  bool		InventorySystem::update(entityCollection const& entities,
					collectionHealth& health,
					collectionStrength& strength,
					collectionVelocity& vel,
					collectionStuff& stuff,
					collectionPotion& potions,
					collectionRenforce& renforce,
					collectionSpeed& speed) const {
    auto eStuffed = entities.getEntitiesOf([&, this](entity const id) {
	return this->isConcerned(id, stuff);
      });
    std::for_each(eStuffed.begin(), eStuffed.end(), [&, this](entity const id) {
	this->handleInventory(id, stuff, health, strength, vel,
			      potions, renforce, speed);
      });
  }
}
