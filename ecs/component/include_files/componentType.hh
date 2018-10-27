#pragma once

#include "scoreComponent.hh"
#include "defenseComponent.hh"
#include "damageComponent.hh"
#include "playerComponent.hh"
#include "componentCollection.hpp"
#include "directionComponent.hh"
#include "positionComponent.hh"
#include "velocityComponent.hh"
#include "healthComponent.hh"
#include "graphicComponent.hh"
#include "strengthComponent.hh"
#include "stuffComponent.hh"
#include "factionComponent.hh"
#include "iaScriptComponent.hh"
#include "rangeComponent.hh"
#include "potionComponent.hh"
#include "speedUpComponent.hh"
#include "renforceComponent.hh"
#include "attackComponent.hh"

namespace	ecs {
  typedef componentCollection<directionComponent>	collectionDirection;
  typedef componentCollection<positionComponent>	collectionPosition;
  typedef componentCollection<directionComponent>	collectionDir;
  typedef componentCollection<velocityComponent>	collectionVelocity;
  typedef componentCollection<positionComponent>	collectionPos;
  typedef componentCollection<stuffComponent>		collectionStuff;
  typedef componentCollection<healthComponent>		collectionHealth;
  typedef componentCollection<graphicComponent>		collectionGraphic;
  typedef componentCollection<strengthComponent>	collectionStrength;
  typedef componentCollection<factionComponent>		collectionFaction;
  typedef componentCollection<iaScriptComponent>	collectionScript;
  typedef componentCollection<rangeComponent>		collectionRange;
  typedef componentCollection<playerComponent>		collectionPlayer;
  typedef componentCollection<damageComponent>		collectionDamage;
  typedef componentCollection<defenseComponent>		collectionDefense;
  typedef componentCollection<potionComponent>		collectionPotion;
  typedef componentCollection<speedUpComponent>		collectionSpeed;
  typedef componentCollection<renforceComponent>	collectionRenforce;
  typedef componentCollection<attackComponent>		collectionAttack;
  typedef componentCollection<scoreComponent>		collectionScore;

  struct	collectionComponent {
    collectionPos	*position;
    collectionDir	*direction;
    collectionGraphic	*graphic;
    collectionScript	*script;
    collectionVelocity	*velocity;
    collectionAttack	*attack;
    collectionRange	*range;
    collectionStrength	*strength;
    collectionDefense	*defense;
    collectionPotion	*potion;
    collectionRenforce	*renforce;
    collectionSpeed	*speed;
    collectionFaction	*faction;
    collectionDamage	*damage;
    collectionPlayer	*player;
    collectionStuff	*stuff;
    collectionHealth	*health;
    collectionScore	*score;
  };

}
