#include <iostream>
#include <algorithm>
#include "loader.hh"
#include "CollectionException.hh"
#include "IaBinding.hh"
#include "IaSystem.hh"

namespace	ecs {
  bool		IaSystem::getIaEntities(entity const id,
					collectionScript& script) const {
    try {
      script.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		IaSystem::getIaEnnemies(entity const id,
					collectionDir& directions,
					collectionPos& position,
					collectionVelocity& vel,
					collectionHealth& health,
					collectionStrength& strength,
					collectionFaction& faction,
					collectionRange& range,
					collectionDamage& damage,
					entity const iaId) const {
    try {
      directions.getComponent(id);
      position.getComponent(id);
      vel.getComponent(id);
      health.getComponent(id);
      strength.getComponent(id);
      damage.getComponent(id);
      auto &Faction = faction.getComponent(id);
      auto &FactionIa = faction.getComponent(iaId);
      if (Faction.type == FactionIa.type)
	return false;
      range.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		IaSystem::update(entityCollection const& entities,
				 collectionScript& script,
				 collectionDir& directions,
				 collectionPos& position,
				 collectionVelocity& vel,
				 collectionHealth& health,
				 collectionStrength& strength,
				 collectionFaction& faction,
				 collectionRange& range,
				 collectionDamage& damageValue,
				 collectionAttack& attack) const {
    IaBinding	binding{};
    auto	iaEntities = entities.getEntitiesOf([&, this](entity const id) {
	return this->getIaEntities(id, script);
      });
    for (auto currentIa : iaEntities) {
      auto ennemyEntity = entities.getEntitiesOf([&, this](entity const id) {
	  return this->getIaEnnemies(id, directions, position, vel, health,
				     strength, faction, range, damageValue, currentIa);
	});
      BinderComponent	binderIa{ currentIa };
      binderIa.setNewCollection(ennemyEntity).setNewComponent(directions).setNewComponent(position).setNewComponent(vel).setNewComponent(health).setNewComponent(strength).setNewComponent(range).setNewComponent(damageValue).setNewComponent(attack);
      binding.setBinder(binderIa);
      auto scriptIa = script.getComponent(currentIa);
      binding.bindFile(scriptIa.script);
    }
    return true;
  }
}
