#pragma once

#include <chrono>
#include <memory>
#include <mutex>
#include "ScoreSystem.hh"
#include "SpawnSystem.hh"
#include "InventorySystem.hh"
#include "DropSystem.hh"
#include "AttackSystem.hh"
#include "DamageSystem.hh"
#include "AnimationSystem.hh"
#include "GraphicMenu.hh"
#include "IaSystem.hh"
#include "InputSystem.hh"
#include "PhysicSystem.hh"
#include "HandlerEntitySystem.hh"
#include "menuGame.hh"
#include "AModel.hh"

namespace	indie {
  class		GameModel : public AModel {
    typedef std::shared_ptr<GraphicMenu>	graphicMenu_t;
  public:
    GameModel(graphicMenu_t& view, std::size_t nbrPlayer = 1,
	      std::string const& map = std::string("map.json"),
	      bool isSaved = false);
    ~GameModel();
  private:
    bool			isPlayer(ecs::entity const id);
    void			removeEntity(ecs::entity const id);
    void			setHealth(ecs::entity const id);
    bool			_update() override;
    void			keepGoodEntity();
    bool			isVelocitySet(ecs::entity const id);
    void			genPlayer(std::size_t const nbr);
    void			saveGame();
    void			deleteDyingEntities();
    void			updateDamage();
    void			loadComponents(std::string const& map, bool isSaved,
					       std::size_t const nbrPlayer);
    void			setHealthBar();
    bool			isPlayerAlive() const;
    void			removePtrPlayer(ecs::entity const id);
    void			displayScore();
    void			updateGame();
    void			updateGamePlaySystem();
    void			updateSystems();
    void			displayGameOver();
    void			loadFromSave(std::string const& save);
    void			loadWalls(std::string const& walls);
  private:
    graphicMenu_t		_graphicDisplayer;
    ov::View			*_view;
    GameMenu			_gameMenu;
    ecs::entityCollection	_entityCol;
    ecs::IaSystem		_iasystem;
    ecs::InputSystem		_inputsystem;
    ecs::PhysicSystem		_physicsystem;
    ecs::healthComponent	*_healthPlayer1;
    ecs::healthComponent	*_healthPlayer2;
    ecs::stuffComponent		*_stuffPlayer1;
    ecs::stuffComponent		*_stuffPlayer2;
    ecs::AnimationSystem	_animationHandler;
    ecs::DamageSystem		_damageSystem;
    ecs::AttackSystem		_attacksystem;
    ecs::HandlerEntitySystem	_handler;
    ecs::InventorySystem	_inventorySystem;
    ecs::DropSystem		_dropSystem;
    ecs::SpawnSystem		_spawnSystem;
    ecs::ScoreSystem		_scoreSystem;
    std::chrono::time_point<std::chrono::system_clock>	_start;
  };
}
