#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include "Spawner.hh"

namespace	indie {
  std::vector<Spawner::spawnInfo>	Spawner::_spawnInfo{};

  void		Spawner::removeBackspace(std::string& file) {
    std::istringstream	iss{ file };
    std::string		tmp{};
    std::string		final{};

    if (iss >> tmp)
      final += tmp;
    while (iss >> tmp)
      final += ' ' + tmp;
    file = final;
  }

  std::string::iterator	Spawner::setPointX(Spawner::spawnInfo& info,
					   std::string& infos,
					   std::string::iterator it) {
    auto itPrev = it;
    while (it != infos.end()) {
      if ((*it) == '#')
	return infos.end();
      if ((*it) == ' ') {
	std::string	point{ itPrev, it };
	info.pointX = std::stof(point);
	return it + 1;
      }
      ++it;
    }
    std::string	point{ itPrev, it };
    info.pointX = std::stof(point);
    return it;
  }

  std::string::iterator	Spawner::setPointY(Spawner::spawnInfo& info,
					   std::string& infos,
					   std::string::iterator it) {
    auto itPrev = it;
    while (it != infos.end()) {
      if ((*it) == '#')
	return infos.end();
      if ((*it) == ' ') {
	std::string	point{ itPrev, it };
	info.pointZ = std::stof(point);
	return it + 1;
      }
      ++it;
    }
    std::string	point{ itPrev, it };
    info.pointZ = std::stof(point);
    return it;
  }

  std::string::iterator	Spawner::setMeshName(Spawner::spawnInfo& info,
					     std::string& infos,
					     std::string::iterator it) {
    auto itPrev = it;
    while (it != infos.end()) {
      if ((*it) == '#')
	return infos.end();
      if ((*it) == ' ') {
	std::string	meshName{ itPrev, it };
	info.meshName = meshName + std::string(".mesh");
	return it + 1;
      }
      ++it;
    }
    std::string	meshName{ itPrev, it };
    info.meshName = meshName + std::string(".mesh");
    return it;
  }

  std::string::iterator	Spawner::setIaName(Spawner::spawnInfo& info,
					   std::string& infos,
					   std::string::iterator it) {
    auto itPrev = it;
    while (it != infos.end()) {
      if ((*it) == '#')
	return infos.end();
      if ((*it) == ' ') {
	std::string	iaName{ itPrev, it };
	info.iaName = iaName + std::string(".lua");
	return it + 1;
      }
      ++it;
    }
    std::string	iaName{ itPrev, it };
    info.iaName = iaName + std::string(".lua");
    return it;
  }

  void		Spawner::getInformations(std::string& infos) {
    try {
      removeBackspace(infos);
      Spawner::spawnInfo	info{};
      auto it = infos.begin();
      it = setPointX(info, infos, it);
      if (it != infos.end())
	it = setPointY(info, infos, it);
      if (it != infos.end())
	it = setMeshName(info, infos, it);
      if (it != infos.end())
	it = setIaName(info, infos, it);
      if (info.meshName != "" && info.iaName != "")
	_spawnInfo.push_back(info);
    }
    catch (std::invalid_argument const& arg) {
      throw indie::CollectionException{ "Error: cannot load spawn, because this line:" +
	  infos + std::string{ " is incorrect" }};
    }
  }

  void		Spawner::feedSpawn(std::string const& file) {
    auto it = file.begin();
    auto itPrev = file.begin();

    while (it != file.end()) {
      if ((*it) == '\n') {
	std::string	stringToParse{ itPrev, it };
	getInformations(stringToParse);
	itPrev = it + 1;
      }
      ++it;
    }
  }

  void		Spawner::loadComponents(ecs::entity const id,
					ecs::collectionComponent& component,
					Spawner::spawnInfo const& sp) {
    component.position->addComponent(id, sp.pointX, 0.f, sp.pointZ);
    component.direction->addComponent(id, 0.f, 0.f, 0.f);
    component.graphic->addComponent(id, sp.meshName, "", "");
    component.script->addComponent(id, sp.iaName);
    component.velocity->addComponent(id, 0.f, 0.f);
    component.attack->addComponent(id, false);
    component.range->addComponent(id, 30.f, 30.f);
    component.strength->addComponent(id, 40.f, 1.f);
    component.defense->addComponent(id, 5.f);
    component.faction->addComponent(id, ecs::faction::EVIL);
    component.damage->addComponent(id, 0.f);
    component.health->addComponent(id, 100.f);
  }

  void		Spawner::feedSpawn(ecs::collectionComponent& component,
				   ecs::entityCollection& entities,
				   Spawner::spawnInfo const& sp) {
    for (std::size_t nbrLoaded = 0; nbrLoaded < 1; ++nbrLoaded) {
      auto entity = entities.createEntity();
      loadComponents(entity, component, sp);
    }
  }

  void		Spawner::loadSpawnComponent(ecs::collectionComponent& component,
					    ecs::entityCollection& entity) {
    for (auto it : _spawnInfo) {
      feedSpawn(component, entity, it);
    }
  }

  void		Spawner::loadSpawnFile(std::string const& fileName) {
    std::ifstream	ifs{ fileName };

    if (!ifs)
      throw indie::CollectionException{ "Error, file named: " + fileName +
	  std::string{ " not found, maybe declare the path on configuration.cfg" } };
    ifs >> std::noskipws;
    std::string		file{ std::istream_iterator<char>(ifs),
	std::istream_iterator<char>() };
    feedSpawn(file);
  }

  void		Spawner::clear() {
    _spawnInfo.clear();
  }
}
