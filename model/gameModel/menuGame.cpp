#include <functional>
#include <algorithm>
#include "GameException.hh"
#include "Audio.hh"
#include "loader.hh"
#include "menuGame.hh"

namespace	indie {
  GameMenu::GameMenu(GameMenu::graphicMenu_t& graphic, std::size_t nbrPlayer)
    : AMenuModel{ graphic }, _isPaused{ false }, _healthPlayer1{ 0 },
      _healthPlayer2{ 0 }, _stuffPlayer1{ 0 }, _stuffPlayer2{ 0 } {
	_potions = 0;
	_renforce = 0;
	_speed = 0;
	_player1OpenInventory = false;
	_player2OpenInventory = false;
	try {
	  _isSaved = false;
	  _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
				     "MainPage");
	  pushInCollection();
	  _graphic->bindEventToWidget("Quit", &GameMenu::quit, this);
	  _graphic->bindEventToWidget("Sound", &GameMenu::sound, this);
	  _graphic->bindEventToWidget("Pause", &GameMenu::pause, this);
	  _graphic->bindEventToWidget("Save", &GameMenu::save, this);
	  _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
				     "InventoryPage");
	  pushInCollection();
	  _graphic->bindEventToWidget("Inventaire 1", &GameMenu::openInventory1, this);
	  _graphic->bindEventToWidget("Inventaire 2", &GameMenu::openInventory2, this);
	  if (nbrPlayer == 1)
	    _graphic->setInvisibleButton("Inventaire 2");
	}
	catch (CEGUI::Exception const&) {
	  throw indie::GameException{ "Error, error on configuration file game_menu.json, unable to launch menu from the game" };
	}
  }

  GameMenu::~GameMenu() {
    removeAll();
  }

  void	GameMenu::erase() {
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& butName) {
		    this->_graphic->setInvisibleButton(butName);
		  });
  }

  bool	GameMenu::needToSave() const {
    return _isSaved;
  }

  void	GameMenu::notifySave() {
    _isSaved = false;
  }

  bool	GameMenu::isPaused() const {
    return _isPaused;
  }

  bool	GameMenu::save(CEGUI::EventArgs const& ce) {
    _isSaved = true;
    return true;
  }

  /*
  ** Inventory handler
  */

  template<typename T>
  bool	GameMenu::isConcerned(ecs::entity const id, T *collection) const {
    if (!collection)
      return false;
    try {
      auto &component = collection->getComponent(id);
      return !component.isUsed;
    }
    catch (CollectionException const&) {
      return false;
    }
  }

  /*
  ** Get the number of each boost available
  */

  void	GameMenu::modifyPotion(ecs::entity const id, std::size_t& nbrPotion) {
    if (!isConcerned(id, _potions))
      return ;
    ++nbrPotion;
  }

  void	GameMenu::modifyRenforce(ecs::entity const id, std::size_t& nbrRenforce) {
    if (!isConcerned(id, _renforce))
      return ;
    ++nbrRenforce;
  }

  void	GameMenu::modifySpeed(ecs::entity const id, std::size_t& nbrSpeed) {
    if (!isConcerned(id, _speed))
      return ;
    ++nbrSpeed;
  }

  /*
  ** Display the inventory
  */

  void	GameMenu::displayContent(ecs::stuffComponent *stuff,
				 GameMenu::modificationFunc_t const& modifyStuffObj,
				 std::string const& section,
				 std::size_t& nbrComponent) {
    if (stuff) {
      std::for_each(stuff->owned.begin(), stuff->owned.end(),
		    [&](ecs::entity const id) {
		      modifyStuffObj(id, nbrComponent);
		    });
    }
    auto bPotion = _loader[section];
    std::string	name{ bPotion.text + std::to_string(nbrComponent) };
    _graphic->loadButton(bPotion.name, "TaharezLook/Button", name,
			 GraphicMenu::Pos{ bPotion.ax, bPotion.ay, bPotion.bx,
			     bPotion.by },
			 GraphicMenu::Size{ bPotion.sax, bPotion.say, bPotion.sbx,
			     bPotion.sby });
    _buttons.push_back(bPotion.name);
  }

  /*
  ** Update the number of items in the inventory
  */

  void	GameMenu::updateInventory(ecs::stuffComponent *stuff, std::string const& name,
				  GameMenu::modificationFunc_t const& funcMod,
				  std::size_t& nbr) {
    std::for_each(stuff->owned.begin(), stuff->owned.end(),
		  [&](ecs::entity const id) {
		    funcMod(id, nbr);
		  });
    if (std::find(_buttons.begin(), _buttons.end(), name) != _buttons.end()) {
      CEGUI::Window *win = _graphic->getWindow(name);
      std::string	nameWin{ name + std::string{"x"} + std::to_string(nbr) };
      win->setText(nameWin);
    }
  }

  void	GameMenu::updateInventoryPlayer(ecs::stuffComponent *stuff,
					std::size_t& potion,
					std::size_t& renforce,
					std::size_t& speed,
					bool isOpen) {
    if (!_stuffPlayer1 || !isOpen)
      return ;
    updateInventory(_stuffPlayer1, "Potion",
		    [this](ecs::entity const id, std::size_t& nbr) {
		      this->modifyPotion(id, nbr);
		    },
		    potion);
    updateInventory(_stuffPlayer1, "Attk",
		    [this](ecs::entity const id, std::size_t& nbr) {
		      this->modifyRenforce(id, nbr);
		    },
		    renforce);
    updateInventory(_stuffPlayer1, "Vit",
		    [this](ecs::entity const id, std::size_t& nbr) {
		      this->modifySpeed(id, nbr);
		    },
		    speed);
  }

  void	GameMenu::updateInventoryPlayer1() {
    _nbrPotionP1 = 0;
    _nbrRenforceP1 = 0;
    _nbrSpeedP1 = 0;
    updateInventoryPlayer(_stuffPlayer1, _nbrPotionP1, _nbrRenforceP1,
			  _nbrSpeedP1, _player1OpenInventory);
  }

  void	GameMenu::updateInventoryPlayer2() {
    _nbrPotionP2 = 0;
    _nbrRenforceP2 = 0;
    _nbrSpeedP2 = 0;
    updateInventoryPlayer(_stuffPlayer2, _nbrPotionP2, _nbrRenforceP2,
			  _nbrSpeedP2, _player2OpenInventory);
  }

  void	GameMenu::displayInventoryContent(std::string const& section,
					  ecs::stuffComponent *stuff,
					  std::string const& potionName,
					  std::string const& renforceName,
					  std::string const& speedName,
					  std::size_t& potionNbr,
					  std::size_t& renforceNbr,
					  std::size_t& speedNbr) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
			       section);
    displayContent(stuff, [this](ecs::entity const id, std::size_t& nbr) {
	this->modifyPotion(id, nbr); },
		   potionName, potionNbr);
    displayContent(stuff, [this](ecs::entity const id, std::size_t& nbr) {
	this->modifyRenforce(id, nbr); },
		   renforceName, renforceNbr);
    displayContent(stuff, [this](ecs::entity const id, std::size_t& nbr) {
	this->modifySpeed(id, nbr); },
		   speedName, speedNbr);
  }

  void	GameMenu::removeButtons(std::string const& potionName,
				std::string const& renforceName,
				std::string const& speedName) {
    std::for_each(_buttons.begin(), _buttons.end(),
		  [&, this](std::string const& button) {
		    if (this->isInventoryBox(button, potionName, renforceName,
					     speedName)) {
		      this->_graphic->removeChildWindow(button);
		    }
		  });
    _buttons.erase(std::remove_if(_buttons.begin(), _buttons.end(), [&, this] (std::string const& button) {
	  return this->isInventoryBox(button, potionName, renforceName, speedName);
	}),
      _buttons.end());
  }

  bool	GameMenu::openInventory(std::string const& section,
				ecs::stuffComponent *stuff,
				std::string const& potionName,
				std::string const& renforceName,
				std::string const& speedName,
				std::size_t& nbrPotion,
				std::size_t& nbrRenforce,
				std::size_t& nbrSpeed) {
    auto buttonExist = std::find_if(_buttons.begin(), _buttons.end(),
    				    [&](std::string const& name) {
    				      return this->isInventoryBox(name, potionName,
    								  renforceName,
    								  speedName);
    				    });
    if (buttonExist == _buttons.end())
      displayInventoryContent(section, stuff, potionName, renforceName, speedName,
			      nbrPotion, nbrRenforce, nbrSpeed);
    else {
      removeButtons(potionName, renforceName, speedName);
      return false;
    }
    return true;
  }

  bool	GameMenu::isInventoryBox(std::string const& button,
				 std::string const& potionName,
				 std::string const& renforceName,
				 std::string const& speedName) const {
    return button == potionName || button == renforceName || button == speedName;
  }

  /*
  ** Event catched by CEGUI (yes it's a huge hack, but, don't have any choices)
  ** we are able to use lambdas and std::function but, NO ! The CEGUI
  ** makes me use member function directly instead of capture the this pointer !!!
  ** I'm verry pissed of !!!
  */

  bool	GameMenu::openInventory1(CEGUI::EventArgs const& arg) {
    _nbrPotionP1 = 0;
    _nbrRenforceP1 = 0;
    _nbrSpeedP1 = 0;
    if (openInventory("InventoryBoxP1", _stuffPlayer1,
		      "Potion", "Attk", "Vit", _nbrPotionP1, _nbrRenforceP1,
		      _nbrSpeedP1)) {
      _player1OpenInventory = true;
      _graphic->bindEventToWidget("Potion", &GameMenu::usePotionP1, this);
      _graphic->bindEventToWidget("Attk", &GameMenu::useRenforceP1, this);
      _graphic->bindEventToWidget("Vit", &GameMenu::useSpeedP1, this);
    }
  }

  bool	GameMenu::openInventory2(CEGUI::EventArgs const& arg) {
    _nbrPotionP2 = 0;
    _nbrRenforceP2 = 0;
    _nbrSpeedP2 = 0;
    if (openInventory("InventoryBoxP2", _stuffPlayer2,
		      "Potion2", "Attk2", "Vit2", _nbrPotionP2, _nbrRenforceP2,
		      _nbrSpeedP2)) {
      _player2OpenInventory = true;
      _graphic->bindEventToWidget("Potion2", &GameMenu::usePotionP2, this);
      _graphic->bindEventToWidget("Attk2", &GameMenu::useRenforceP2, this);
      _graphic->bindEventToWidget("Vit2", &GameMenu::useSpeedP2, this);
    }
  }


  /*
  ** Event catched by CEGUI to use boost (yes, it's a huge hack
  ** but we don't have any choices)
  */

  template<typename T>
  void	GameMenu::useComponentInStuff(ecs::stuffComponent *stuff, T *collection,
				      std::size_t& nbr) {
    if (!stuff || stuff->owned.empty() || !nbr)
      return ;
    auto it = std::find_if(stuff->owned.begin(), stuff->owned.end(),
			   [&, this](ecs::entity const id) {
			     return this->isConcerned(id, collection);
			   });
    if (it == stuff->owned.end())
      return ;
    auto &component = collection->getComponent(*it);
    component.isUsed = true;
    --nbr;
  }

  bool	GameMenu::usePotionP1(CEGUI::EventArgs const& arg) {
    useComponentInStuff(_stuffPlayer1, _potions, _nbrPotionP1);
    return true;
  }

  bool	GameMenu::usePotionP2(CEGUI::EventArgs const& arg) {
    useComponentInStuff(_stuffPlayer2, _potions, _nbrPotionP2);
    return true;
  }

  bool	GameMenu::useRenforceP1(CEGUI::EventArgs const& arg) {
    useComponentInStuff(_stuffPlayer1, _renforce, _nbrRenforceP1);
    return true;
  }

  bool	GameMenu::useRenforceP2(CEGUI::EventArgs const& arg) {
    useComponentInStuff(_stuffPlayer2, _renforce, _nbrRenforceP2);
    return true;
  }

  bool	GameMenu::useSpeedP1(CEGUI::EventArgs const& arg) {
    useComponentInStuff(_stuffPlayer1, _speed, _nbrSpeedP1);
    return true;
  }

  bool	GameMenu::useSpeedP2(CEGUI::EventArgs const& arg) {
    useComponentInStuff(_stuffPlayer2, _speed, _nbrSpeedP2);
    return true;
  }

  /*
  ** Pause handler
  */

  bool	GameMenu::restart(CEGUI::EventArgs const& arg) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
			       "PausePage");
    auto bPause = _loader["pause"];
    _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), bPause.text),
		   _buttons.end());
    _graphic->removeChildWindow(bPause.text);
    _isPaused = false;
    return true;
  }

  bool	GameMenu::pause(CEGUI::EventArgs const& arg) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
			       "PausePage");
    auto bPause = _loader["pause"];
    if (_isPaused) {
      _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), bPause.text),
		     _buttons.end());
      _graphic->removeChildWindow(bPause.text);
      _isPaused = false;
      return true;
    }
    _graphic->loadButton(bPause.text, "TaharezLook/Button", bPause.text,
			 GraphicMenu::Pos{ bPause.ax, bPause.ay, bPause.bx, bPause.by },
			 GraphicMenu::Size{ bPause.sax, bPause.say, bPause.sbx,
			     bPause.sby });
    _buttons.push_back(bPause.text);
    _graphic->bindEventToWidget(bPause.text, &GameMenu::restart, this);
    _isPaused = true;
    return true;
  }

  /*
  ** Quit button
  */

  bool	GameMenu::quit(CEGUI::EventArgs const& arg) {
    AModel::_ret = false;
    removeAll();
    return true;
  }

  /*
  ** Setter for the stuff component / Collections.
  */

  GameMenu	&GameMenu::setHealthPlayer1(ecs::healthComponent& health) {
    _healthPlayer1 = &health;
    return *this;
  }

  GameMenu	&GameMenu::setHealthPlayer2(ecs::healthComponent& health) {
    _healthPlayer2 = &health;
    return *this;
  }

  GameMenu	&GameMenu::setStuffPlayer1(ecs::stuffComponent& stuff) {
    _stuffPlayer1 = &stuff;
    return *this;
  }

  GameMenu	&GameMenu::setStuffPlayer2(ecs::stuffComponent& stuff) {
    _stuffPlayer2 = &stuff;
    return *this;
  }

  GameMenu	&GameMenu::setPotion(ecs::collectionPotion& potion) {
    _potions = &potion;
    return *this;
  }

  GameMenu	&GameMenu::setRenforce(ecs::collectionRenforce& renforce) {
    _renforce = &renforce;
    return *this;
  }

  GameMenu	&GameMenu::setSpeed(ecs::collectionSpeed& speed) {
    _speed = &speed;
    return *this;
  }

  /*
  ** Ingame sound handler
  */

  void	GameMenu::displaySound(MenuLoader::Button const& bSound) {
    _graphic->loadButton(bSound.text, "TaharezLook/Slider", bSound.text,
			 GraphicMenu::Pos{ bSound.ax, bSound.ay, bSound.bx,
			     bSound.by },
			 GraphicMenu::Size{ bSound.sax, bSound.say, bSound.sbx,
			     bSound.sby });
    CEGUI::Slider *slider = static_cast<CEGUI::Slider *>(_graphic->getWindow(bSound.text));
    slider->setMaxValue(1.f);
    slider->setClickStep(0.1f);
    slider->setCurrentValue(Audio::getVolume() / 100);
    _graphic->bindEventToWidget(bSound.text, &GameMenu::manageSound, this,
				CEGUI::Slider::EventValueChanged);
    _buttons.push_back(bSound.text);
  }

  bool	GameMenu::sound(CEGUI::EventArgs const& arg) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
			       "SoundPage");
    auto bSound = _loader["SoundProgressBar"];
    if (std::find(_buttons.begin(), _buttons.end(), bSound.text) == _buttons.end())
      displaySound(bSound);
    else {
      _graphic->removeChildWindow(bSound.text);
      _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), bSound.text),
		     _buttons.end());
    }
    return true;
  }

  void	GameMenu::notifyDead(ecs::entity const id) {
    if (_healthPlayer1 && _healthPlayer1->id == id)
      _healthPlayer1 = 0;
    else if (_healthPlayer2 && _healthPlayer2->id == id)
      _healthPlayer2 = 0;
  }

  bool	GameMenu::manageSound(CEGUI::EventArgs const& arg) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
			       "SoundPage");
    auto bS = _loader["SoundProgressBar"];
    CEGUI::Slider *slider = static_cast<CEGUI::Slider *>(_graphic->getWindow(bS.text));
    float	value{ slider->getCurrentValue() };
    Audio::setVolume(value * 100);
    return true;
  }

  void	GameMenu::updateHealth(ecs::healthComponent *health,
			       MenuLoader::Button const& progress) {
    _graphic->removeChildWindow(progress.text);
    _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), progress.text),
		   _buttons.end());
    _graphic->loadButton(progress.text, "TaharezLook/ProgressBar", "",
			 GraphicMenu::Pos{ progress.ax, progress.ay, progress.bx,
			     progress.by },
			 GraphicMenu::Size{ progress.sax, progress.say, progress.sbx,
			     progress.sby });
    CEGUI::ProgressBar *win = static_cast<CEGUI::ProgressBar* >(_graphic->getWindow(progress.text));
    win->setProgress(health->live / 100);
    _buttons.push_back(progress.text);
  }

  void	GameMenu::displayHealth(ecs::healthComponent *health,
				MenuLoader::Button const& progress) {
    _graphic->loadButton(progress.text, "TaharezLook/ProgressBar", "",
			 GraphicMenu::Pos{ progress.ax, progress.ay, progress.bx,
			     progress.by },
			 GraphicMenu::Size{ progress.sax, progress.say,
			     progress.sbx,
			     progress.sby });
    CEGUI::ProgressBar *win = static_cast<CEGUI::ProgressBar* >(_graphic->getWindow(progress.text));
    _buttons.push_back(progress.text);
    win->setProgress(health->live / 100);
  }

  void	GameMenu::pushHealth(ecs::healthComponent *health,
			     std::string const& button) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("game_menu.json"),
			       "LivePage");
    auto progress = _loader[button];
    if (std::find(_buttons.begin(), _buttons.end(), progress.text) != _buttons.end())
      updateHealth(health, progress);
    else
      displayHealth(health, progress);
  }

  bool	GameMenu::_update() {
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& name) {
		    this->_graphic->setVisibleButton(name);
		  });
    if (!_healthPlayer1 && std::find(_buttons.begin(),
				     _buttons.end(), "livePlayer1") != _buttons.end())
      _graphic->setInvisibleButton("livePlayer1");
    if (!_healthPlayer2 && std::find(_buttons.begin(),
				     _buttons.end(), "livePlayer2") != _buttons.end())
      _graphic->setInvisibleButton("livePlayer2");
    if (_healthPlayer1)
      pushHealth(_healthPlayer1, "livePlayer1");
    if (_healthPlayer2)
      pushHealth(_healthPlayer2, "livePlayer2");
    updateInventoryPlayer1();
    updateInventoryPlayer2();
    _graphic->render();
    return AModel::_ret;
  }
}
