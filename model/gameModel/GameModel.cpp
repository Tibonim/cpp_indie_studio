#include <algorithm>
#include <iostream>
#include "CEGUI.h"
#include <thread>
#include <unistd.h>
#include <OgreWindowEventUtilities.h>
#include <RendererModules/Ogre/Renderer.h>
#include "CollectionException.hh"
#include "Spawner.hh"
#include "loader.hh"
#include "saveCollection.hh"
#include "InputSystem.hh"
#include "GameModel.hh"
#include "Audio.hh"

namespace	indie {
  GameModel::GameModel(GameModel::graphicMenu_t& graphic, std::size_t nbrPlayer,
		       std::string const& map, bool isSaved)
    : AModel{}, _graphicDisplayer{ graphic }, _view{ 0 }, _gameMenu{ graphic },
      _healthPlayer1{ 0 }, _healthPlayer2{ 0 }, _stuffPlayer1{ 0 },
      _stuffPlayer2{ 0 }, _scoreSystem{ graphic } {
	Spawner::loadSpawnFile(ConfigurationLoader::getFile("spawn_lv1"));
	Audio::stop();
	Audio::playMusic("media/mario.wav");
	loadComponents(map, isSaved, nbrPlayer);
	keepGoodEntity();
	setHealthBar();
	_view = _graphicDisplayer->getView();
	_view->NewMap();
	_start = std::chrono::system_clock::now();
      }

  void		GameModel::setHealthBar() {
    auto entitiesP = _entityCol.getEntitiesOf([this](ecs::entity const id) {
	return this->isPlayer(id);
      });
    std::for_each(entitiesP.begin(), entitiesP.end(),
		  [this](ecs::entity const id) {
		    this->setHealth(id);
		  });
    _gameMenu.setHealthPlayer1((*_healthPlayer1)).setHealthPlayer2((*_healthPlayer2));
  }

  void		GameModel::loadFromSave(std::string const& map) {
    auto entities = _entities.getEntities();
    std::for_each(entities.begin(), entities.end(), [this](ecs::entity const id) {
	this->removeEntity(id);
	_entities.removeEntity(id);
      });
    saver::SaveCollection	saver{};
    const std::string	str = ConfigurationLoader::getFile(map);
    saver.loadComponent(str, AModel::_velocity);
    saver.loadComponent(str, AModel::_strength);
    saver.loadComponent(str, AModel::_graphic);
    saver.loadComponent(str, AModel::_position);
    saver.loadComponent(str, AModel::_direction);
    saver.loadComponent(str, AModel::_script);
    saver.loadComponent(str, AModel::_health);
    saver.loadComponent(str, AModel::_faction);
    saver.loadComponent(str, AModel::_range);
    saver.loadComponent(str, AModel::_player);
    saver.loadComponent(str, AModel::_damage);
    saver.loadComponent(str, AModel::_defense);
    saver.loadComponent(str, AModel::_attack);
    saver.loadComponent(str, AModel::_stuff);
    saver.loadComponent(str, AModel::_score);
    saver.loadComponent(str, AModel::_potion, "potionComponent");
    saver.loadComponent(str, AModel::_speed, "speedUpComponent");
    saver.loadComponent(str, AModel::_renforce, "renforceComponent");
    saver.loadEntity(str, AModel::_entities);
  }

  void		GameModel::loadWalls(std::string const& map) {
    saver::SaveCollection	saver{};
    const std::string	str = ConfigurationLoader::getFile(map);
    saver.loadComponent(str, AModel::_velocity);
    saver.loadComponent(str, AModel::_strength);
    saver.loadComponent(str, AModel::_graphic);
    saver.loadComponent(str, AModel::_position);
    saver.loadComponent(str, AModel::_direction);
    saver.loadComponent(str, AModel::_script);
    saver.loadComponent(str, AModel::_health);
    saver.loadComponent(str, AModel::_faction);
    saver.loadComponent(str, AModel::_range);
    saver.loadEntity(str, AModel::_entities);
  }

  void		GameModel::loadComponents(std::string const& map, bool isSaved,
					  std::size_t const nbrPlayer) {
    if (!isSaved) {
      loadWalls(map);
      genPlayer(nbrPlayer);
      Spawner::loadSpawnComponent(_components, _entities);
    }
    else {
      loadFromSave(map);
      _scoreSystem.update(_score);
    }
  }

  bool		GameModel::isVelocitySet(ecs::entity const id) {
    try {
      AModel::_velocity.getComponent(id);
      return true;
    }
    catch (CollectionException const&) {
      return false;
    }
  }

  void		GameModel::genPlayer(std::size_t const nbr) {
    for (std::size_t i = 0; i < nbr; ++i) {
      auto player = _entities.createEntity();
      _player.addComponent(player, static_cast<int>(i + 1));
      _direction.addComponent(player, 0.f, 0.f, 0.f);
      _velocity.addComponent(player, 0.f);
      _strength.addComponent(player, 600.f);
      _graphic.addComponent(player, "MyMate" + std::to_string(i) + ".mesh", "", "");
      _health.addComponent(player, 100.f);
      _damage.addComponent(player, 0.f);
      _faction.addComponent(player, ecs::faction::NICE);
      _range.addComponent(player, 30.f, 30.f);
      _position.addComponent(player, 0.f, 0.f,
			     static_cast<float>(-(10.f - (i + 1.f)) * 100.f));
      _defense.addComponent(player, 10.f);
      _attack.addComponent(player, false);
      if (i == 0) {
	std::vector<ecs::entity>	pt{ 9, 10, 11 };
	_stuff.addComponent(player, pt);
	_stuffPlayer1 = &_stuff.getComponent(player);
      }
    }
    _score.value = 0;
    if (_stuffPlayer1)
      _gameMenu.setStuffPlayer1(*_stuffPlayer1).setPotion(_potion).setRenforce(_renforce).setSpeed(_speed);
  }

  void		GameModel::keepGoodEntity() {
    auto entities = AModel::_entities.getEntitiesOf([this](ecs::entity const id) {
	return this->isVelocitySet(id);
      });
    std::for_each(entities.begin(), entities.end(), [this] (ecs::entity const id) {
	this->_entityCol.addEntity(id);
      });
  }

  GameModel::~GameModel() {
    Audio::stop();
    Audio::playMusic("media/ambiance.wav");
    Audio::setPitch(1.5);
    auto entities = _entities.getEntities();
    std::for_each(entities.begin(), entities.end(), [this](ecs::entity const id) {
	this->removeEntity(id);
	_entities.removeEntity(id);
      });
    Spawner::clear();
  }

  void		GameModel::setHealth(ecs::entity const id) {
    auto &health = AModel::_health.getComponent(id);
    auto &player = AModel::_player.getComponent(id);
    if (player.idPlayer == 1)
      _healthPlayer1 = &health;
    else if (player.idPlayer == 2)
      _healthPlayer2 = &health;
  }

  bool		GameModel::isPlayer(ecs::entity const id) {
    try {
      auto &playerC = AModel::_player.getComponent(id);
      auto &healthC = AModel::_health.getComponent(id);
      return true;
    }
    catch (CollectionException const&) {
      return false;
    }
  }

  void		GameModel::saveGame() {
    saver::SaveCollection	saver{};
    saver.saveComponent("save.json", AModel::_attack,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_direction,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_velocity,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_strength,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_graphic,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_position,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_script,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_health,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_faction,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_range,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_player,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_defense,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_damage,
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_speed, "speedUpComponent",
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_renforce, "renforceComponent",
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_potion, "potionComponent",
			AModel::_entities.getEntities());
    saver.saveComponent("save.json", AModel::_score);
    saver.saveEntity("save.json", AModel::_entities.getEntities());
  }

  void		GameModel::removeEntity(ecs::entity const id) {
    _health.eraseComponent(id);
    _direction.eraseComponent(id);
    _velocity.eraseComponent(id);
    _position.eraseComponent(id);
    _stuff.eraseComponent(id);
    _graphic.eraseComponent(id);
    _strength.eraseComponent(id);
    _faction.eraseComponent(id);
    _script.eraseComponent(id);
    _range.eraseComponent(id);
    _player.eraseComponent(id);
    _damage.eraseComponent(id);
    _defense.eraseComponent(id);
    _entities.removeEntity(id);
  }

  void		GameModel::deleteDyingEntities() {
    auto toRemove = _handler.update(_entities,
				    _health, _direction, _velocity, _position,
				    _stuff, _graphic, _strength, _faction,
				    _script, _range, _player, _damage, _defense);
    std::for_each(toRemove.begin(), toRemove.end(),
		  [this](ecs::entity const id) {
		    _view->deleteByEntity(id);
		    if (isPlayer(id)) {
		      removePtrPlayer(id);
		      _player.eraseComponent(id);
		      _gameMenu.notifyDead(id);
		    }
		    removeEntity(id);
		  });
  }

  void		GameModel::removePtrPlayer(ecs::entity const id) {
    auto idPlayer = _player.getComponent(id).idPlayer;
    if (idPlayer == 1) {
      _healthPlayer1 = 0;
    }
    else if (idPlayer == 2) {
      _healthPlayer2 = 0;
    }
  }

  void		GameModel::updateDamage() {
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - _start;
    if (elapsed.count() >= 0.5f) {
      if (_gameMenu.needToSave()) {
	saveGame();
	_gameMenu.notifySave();
      }
      AModel::_ret = _gameMenu.update();
      _attacksystem.update(_entities, _attack, _damage, _position, _range, _strength, _direction, _faction);
      _damageSystem.update(_entities, _damage, _defense, _health);
      _dropSystem.update(_entities, _potion, _renforce, _speed, _stuff, _player);
      _start = end;
    }
  }

  void		GameModel::updateGamePlaySystem() {
    _iasystem.update(_entities, _script, _direction, _position, _velocity,
		     _health, _strength, _faction, _range, _damage, _attack);
    _inputsystem.update(_entities, _direction, _velocity, _attack);
    _physicsystem.update(_view, _entities, _direction, _velocity, _position, _graphic,
			 _faction);
    _inventorySystem.update(_entities, _health, _strength, _velocity, _stuff, _potion,
			    _renforce, _speed);
  }

  void		GameModel::updateSystems() {
    _view->DisplayEntities(_entities, _graphic, _position, _direction, _player);
    _animationHandler.update(_entities, _graphic, _velocity, _attack);
    if (_spawnSystem.update(_entities, _components))
      _scoreSystem.update(_score);
  }

  bool		GameModel::isPlayerAlive() const {
    return !_player.empty();
  }

  void		GameModel::updateGame() {
    if (_gameMenu.isPaused()) {
      AModel::_ret = _gameMenu.update();
      return ;
    }
    updateDamage();
    updateGamePlaySystem();
    updateSystems();
    if (!AModel::_ret) {
      _scoreSystem.deleteScore();
      _view->DestroyMap();
    }
  }

  void		GameModel::displayGameOver() {
    _view->DestroyMap();
    _gameMenu.erase();
    _scoreSystem.deleteScore();
    _graphicDisplayer->createBackground("game_over_bg.jpg", "bgOver");
    _graphicDisplayer->render();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    _graphicDisplayer->saveBackground("game_over_bg.jpg", "bgOver");
    AModel::_ret = false;
    Audio::stop();
    Audio::playMusic("media/ambiance.wav");
    Audio::setPitch(1.5);
    auto entities = _entities.getEntities();
    std::for_each(entities.begin(), entities.end(), [this](ecs::entity const id) {
	this->removeEntity(id);
	_entities.removeEntity(id);
      });
    Spawner::clear();
  }

  bool		GameModel::_update() {
    setHealthBar();
    updateGame();
    deleteDyingEntities();
    if (!isPlayerAlive()) {
      displayGameOver();
    }
    else if (!AModel::_ret && _gameMenu.isPaused()) {
      Spawner::clear();
      _scoreSystem.deleteScore();
      _view->DestroyMap();
    }
    return AModel::_ret;
  }
}
