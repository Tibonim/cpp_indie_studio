#pragma once

#include "componentCollection.hpp"
#include "componentType.hh"

namespace	ecs {
  class		BinderComponent {
  public:
    BinderComponent(entity id);
    int				getNbrOfEntities();
    entity			getCurrentIa();
    /*
    ** Set of new components
    */
    BinderComponent		&setNewCollection(std::vector<entity> const& collection);
    BinderComponent		&setNewComponent(collectionDir& collection);
    BinderComponent		&setNewComponent(collectionPos& collection);
    BinderComponent		&setNewComponent(collectionAttack& collection);
    BinderComponent		&setNewComponent(collectionVelocity& collection);
    BinderComponent		&setNewComponent(collectionHealth& collection);
    BinderComponent		&setNewComponent(collectionStrength& collection);
    BinderComponent		&setNewComponent(collectionFaction& collection);
    BinderComponent		&setNewComponent(collectionRange& collection);
    BinderComponent		&setNewComponent(collectionDamage& collection);
    /*
    ** By giving an index, it return the entity.
    */
    entity			getEntityFromCollection(int const idx);
    double			getDirX(entity const id);
    double			getDirY(entity const id);
    double			getDirZ(entity const id);
    void			setDirection(entity const id, double x, double y, double z);
    double			getVelocity(entity const id);
    void			setVelocity(entity const id, double vel);
    void			setAttack(entity const id, bool attack);
    double			getPosX(entity const id);
    double			getPosY(entity const id);
    double			getPosZ(entity const id);
    void			setPosition(entity const id, double x, double y, double z);
    double			getLive(entity const id);
    void			setLive(entity const id, double live);
    double			getStrength(entity const id);
    void			setStrength(entity const id, double strength);
    int				getFaction(entity const id);
    double			getRangeX(entity const id);
    double			getRangeY(entity const id);
    double			getDamage(entity const id);
    void			setDamage(entity const id, double damage);
  private:
    collectionDir		*_direction;
    collectionVelocity		*_velocity;
    collectionAttack		*_attack;
    collectionPos		*_position;
    collectionHealth		*_health;
    collectionStrength		*_strength;
    collectionFaction		*_faction;
    collectionRange		*_range;
    collectionDamage		*_damages;
    std::vector<entity> const	*_entities;
    entity			_id;
  };
}
