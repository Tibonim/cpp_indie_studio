#include <utility>
#include <algorithm>
#include "GameModel.hh"
#include "MenuModel.hh"
#include "MenuLoader.hh"
#include "GameException.hh"
#include "SettingsModel.hh"
#include "loader.hh"
#include "Audio.hh"

namespace	indie {
  MenuModel::MenuModel()
    : AModel{  } {
    _graphic = std::make_shared<GraphicMenu>();
    _graphic->loadScheme("Generic.scheme").loadScheme("TaharezLook.scheme").loadMouse("TaharezLook/MouseArrow").createBackground("bg_start.jpg", "bgMenu");
    _isPlayClicked = false;
    try {
      MenuLoader	loader{};

      loader.loadButtonFromFile("conf/menu/menu.json", "MainPage");
      auto bP = loader["playButton"];
      _graphic->loadButton(bP.text, "TaharezLook/Button", bP.text,
      			   GraphicMenu::Pos{ bP.ax, bP.ay, bP.bx, bP.by },
      			   GraphicMenu::Size{ bP.sax, bP.say, bP.sbx, bP.sby });
      auto bC = loader["continueButton"];
      _graphic->loadButton(bC.text, "TaharezLook/Button", bC.text,
			   GraphicMenu::Pos{ bC.ax, bC.ay, bC.bx, bC.by },
			   GraphicMenu::Size{ bC.sax, bC.say, bC.sbx, bC.sby });
      _graphic->bindEventToWidget(bC.text, &MenuModel::continueGame, this);
      _buttons.push_back(bC.text);
      auto bDown = loader["soundDown"];
      _graphic->loadButton(bDown.text, "TaharezLook/Slider", bDown.text,
      			   GraphicMenu::Pos{ bDown.ax, bDown.ay, bDown.bx, bDown.by },
      			   GraphicMenu::Size{ bDown.sax, bDown.say, bDown.sbx,
			       bDown.sby });
      CEGUI::Slider	*slider = static_cast<CEGUI::Slider* >(_graphic->getWindow(bDown.text));
      slider->setMaxValue(1.0f);
      slider->setClickStep(0.1f);
      slider->setCurrentValue(Audio::getVolume() / 100.f);
      auto bS = loader["settingButton"];
      _graphic->loadButton(bS.text, "TaharezLook/Button", bS.text,
      			   GraphicMenu::Pos{ bS.ax, bS.ay, bS.bx, bS.by },
      			   GraphicMenu::Size{ bS.sax, bS.say, bS.sbx, bS.sby });
      auto bQ = loader["quitButton"];
      _graphic->loadButton(bQ.text, "TaharezLook/Button", bQ.text,
      			   GraphicMenu::Pos{ bQ.ax, bQ.ay, bQ.bx, bQ.by },
      			   GraphicMenu::Size{ bQ.sax, bQ.say, bQ.sbx, bQ.sby });
      _graphic->bindEventToWidget(bP.text,
				  &MenuModel::play, this);
      _graphic->bindEventToWidget(bS.text,
				  &MenuModel::settingsMenu, this);
      _graphic->bindEventToWidget(bQ.text,
				  &MenuModel::quit, this);
      _graphic->bindEventToWidget(bDown.text, &MenuModel::handleSound, this,
				  CEGUI::Slider::EventValueChanged);
      _buttons.push_back(bP.text);
      _buttons.push_back(bS.text);
      _buttons.push_back(bQ.text);
      _buttons.push_back(bDown.text);
    }
    catch (CEGUI::Exception const& bad) {
      throw indie::CustomException{ std::string{ bad.what() } };
    };

  }

  bool		MenuModel::handleSound(CEGUI::EventArgs const& event) {
    MenuLoader	loader{};
    loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"), "MainPage");
    auto bDown = loader["soundDown"];
    CEGUI::Slider	*slider = static_cast<CEGUI::Slider* >(_graphic->getWindow(bDown.text));

    float volume{ slider->getCurrentValue() };
    Audio::setVolume(volume * 100);
    return true;
  }

  bool		MenuModel::quit(CEGUI::EventArgs const& arg) {
    AModel::_currentModel.reset();
    _graphic.reset();
    AModel::_ret = false;
    return true;
  }

  void		MenuModel::eraseMenu() {
    _graphic->saveBackground("menu_background.jpg", "bgMenu");
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& button) {
		    this->_graphic->setInvisibleButton(button);
		  });
  }

  void		MenuModel::pushInCollection(MenuLoader const& loader) {
    auto collection = loader.getButtons();
    std::for_each(collection.begin(), collection.end(),
		  [this](MenuLoader::Button const& b) {
		    this->_graphic->loadButton(b.text, "TaharezLook/Button",
					       b.text,
					       GraphicMenu::Pos{ b.ax, b.ay, b.bx,
						   b.by },
					       GraphicMenu::Size{ b.sax, b.say,
						   b.sbx, b.sby});
		    this->_buttons.push_back(b.text);
		    return ;
		  });
  }

  void		MenuModel::removePlayButton() {
    try {
      _graphic->removeChildWindow("ONE PLAYER");
      _graphic->removeChildWindow("TWO PLAYERS");
      _buttons.erase(std::remove_if(_buttons.begin(), _buttons.end(),
				    [](std::string const& butt) {
				      return butt == "ONE PLAYER" ||
					butt == "TWO PLAYERS";
				    }),
		     _buttons.end());
    }
    catch (CEGUI::Exception const& ce) {
      throw indie::GameException{ std::string{ ce.what() } };
    }
  }

  bool		MenuModel::playWithOnePlayer(CEGUI::EventArgs const& arg) {
    eraseMenu();
    _isPlayClicked = false;
    AModel::_currentModel = std::make_shared<GameModel>(_graphic);
    AModel::_ret = true;
    removePlayButton();
    return true;
  }

  bool		MenuModel::playWithTwoPlayer(CEGUI::EventArgs const& arg) {
    eraseMenu();
    _isPlayClicked = false;
    AModel::_currentModel = std::make_shared<GameModel>(_graphic, 2);
    AModel::_ret = true;
    removePlayButton();
    return true;
  }

  bool		MenuModel::play(CEGUI::EventArgs const& arg) {
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& name) {
		    _graphic->setInvisibleButton(name);
		  });
    _isPlayClicked = true;
    MenuLoader	loader{};
    loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
			      "playerNbrChoice");
    auto onePlayer = loader["onePlayer"];
    auto twoPlayer = loader["twoPlayers"];
    _graphic->loadButton(onePlayer.text, "TaharezLook/Button", onePlayer.text,
			 GraphicMenu::Pos{ onePlayer.ax, onePlayer.ay, onePlayer.bx,
			     onePlayer.by },
			 GraphicMenu::Size{ onePlayer.sax, onePlayer.say,
			     onePlayer.sbx, onePlayer.sby });
    _graphic->loadButton(twoPlayer.text, "TaharezLook/Button", twoPlayer.text,
			 GraphicMenu::Pos{ twoPlayer.ax, twoPlayer.ay, twoPlayer.bx,
			     twoPlayer.by },
			 GraphicMenu::Size{ twoPlayer.sax, twoPlayer.say,
			     twoPlayer.sbx, twoPlayer.sby });
    _graphic->bindEventToWidget(onePlayer.text, &MenuModel::playWithOnePlayer, this);
    _graphic->bindEventToWidget(twoPlayer.text, &MenuModel::playWithTwoPlayer, this);
    return true;
  }

  bool		MenuModel::continueGame(CEGUI::EventArgs const& arg) {
    eraseMenu();
    AModel::_currentModel = std::make_shared<GameModel>(_graphic, 2, "save.json",
							true);
    AModel::_ret = true;
    return true;
  }

  bool		MenuModel::settingsMenu(CEGUI::EventArgs const& arg) {
    try {
      std::for_each(_buttons.begin(), _buttons.end(),
		    [this](std::string const& name) {
		      this->_graphic->setInvisibleButton(name);
		    });
      AModel::_currentModel = std::make_shared<SettingModel>(_graphic);
      AModel::_ret = true;
      return true;
    }
    catch (CEGUI::Exception const& bad) {
      return false;
    }
  }

  bool		MenuModel::_update() {
    AModel::_ret = true;
    if (!_graphic->isBackgroundSet()) {
      _graphic->createBackground("menu_background.jpg", "bgMenu");
    }
    if (!_isPlayClicked) {
      std::for_each(_buttons.begin(), _buttons.end(),
		    [this](std::string const& name) {
		      this->_graphic->setVisibleButton(name);
		    });
      if (!ConfigurationLoader::isFile("save.json"))
	_graphic->setInvisibleButton("CONTINUE");
    }
    if (_graphic.get())
      _graphic->render();
    return AModel::_ret;
  }
}
