#pragma once

#include <memory>
#include "entityCollection.hh"
#include "componentType.hh"
#include "IModel.hpp"

namespace	indie {
  class		AModel : public IModel {
  public:
    AModel();
    virtual ~AModel() {};
    bool		update() override;
  private:
    virtual bool	_update() = 0;
  protected:
    std::shared_ptr<IModel>	_currentModel;
    ecs::collectionDir		_direction;
    ecs::collectionVelocity	_velocity;
    ecs::collectionStrength	_strength;
    ecs::collectionGraphic	_graphic;
    ecs::collectionPos		_position;
    ecs::collectionScript	_script;
    ecs::collectionHealth	_health;
    ecs::collectionFaction	_faction;
    ecs::collectionRange	_range;
    ecs::collectionDamage	_damage;
    ecs::collectionPlayer	_player;
    ecs::collectionStuff	_stuff;
    ecs::entityCollection	_entities;
    ecs::collectionPotion	_potion;
    ecs::collectionSpeed	_speed;
    ecs::collectionRenforce	_renforce;
    ecs::collectionDefense	_defense;
    ecs::collectionAttack	_attack;
    ecs::scoreComponent		_score;
    ecs::collectionComponent	_components;
    bool			_ret;
  };
}
