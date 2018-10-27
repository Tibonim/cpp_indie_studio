#pragma once

#include <vector>
#include "SingletonPattern.hh"
#include "componentType.hh"

namespace	indie {
  class		Spawner : private event::SingletonPattern {
  public:
    struct		spawnInfo {
      float		pointX;
      float		pointZ;
      std::string	meshName;
      std::string	iaName;
    };
    static void	loadSpawnFile(std::string const& fileName);
    static void	clear();
    static void	loadSpawnComponent(ecs::collectionComponent& component,
				   ecs::entityCollection& entity);
  private:
    static std::vector<spawnInfo>	_spawnInfo;
  private:
    static void	feedSpawn(std::string const& file);
    static void	removeBackspace(std::string& file);
    static void	getInformations(std::string& infos);
    static std::string::iterator	setPointX(Spawner::spawnInfo& info,
						  std::string& infos,
						  std::string::iterator it);
    static std::string::iterator	setPointY(Spawner::spawnInfo& info,
						  std::string& infos,
						  std::string::iterator it);
    static std::string::iterator	setMeshName(Spawner::spawnInfo& info,
						    std::string& infos,
						    std::string::iterator it);
    static std::string::iterator	setIaName(Spawner::spawnInfo& info,
						  std::string& infos,
						  std::string::iterator it);
    static void	feedSpawn(ecs::collectionComponent& component,
			  ecs::entityCollection& entity,
			  spawnInfo const& sp);
    static void	loadComponents(ecs::entity const id,
			       ecs::collectionComponent& component,
			       Spawner::spawnInfo const& sp);
  };
}
