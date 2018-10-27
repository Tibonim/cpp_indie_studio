#pragma once

#include "componentType.hh"

namespace	ecs {
  class		SpawnSystem {
  public:
    bool	update(entityCollection& collection,
		       collectionComponent& components) const;
  private:
    bool	isConcerned(entity const id, collectionFaction& faction) const;
  };
}
