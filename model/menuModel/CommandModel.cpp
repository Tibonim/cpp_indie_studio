#include <stdexcept>
#include <algorithm>
#include <unistd.h>
#include "loader.hh"
#include "CommandModel.hh"

namespace	indie {
  CommandModel::CommandModel(CommandModel::graphicMenu_t& graphic)
    : AMenuModel{ graphic }, _isChangedTheKey{ false } {
      loadKeysPlayer();
      _buttonKey["attack1"] = "attack";
      _buttonKey["left1"] = "moveLeft";
      _buttonKey["right1"] = "moveRight";
      _buttonKey["down1"] = "moveDown";
      _buttonKey["up1"] = "moveUp";
      _buttonKey["attack2"] = "attack";
      _buttonKey["left2"] = "moveLeft";
      _buttonKey["right2"] = "moveRight";
      _buttonKey["down2"] = "moveDown";
      _buttonKey["up2"] = "moveUp";
      _setKey["attack1"] = &CommandModel::setKeyAttackPlayer1;
      _setKey["left1"] = &CommandModel::setKeyMoveLeftPlayer1;
      _setKey["right1"] = &CommandModel::setKeyMoveRightPlayer1;
      _setKey["down1"] = &CommandModel::setKeyMoveDownPlayer1;
      _setKey["up1"] = &CommandModel::setKeyMoveUpPlayer1;
      _setKey["attack2"] = &CommandModel::setKeyAttackPlayer2;
      _setKey["left2"] = &CommandModel::setKeyMoveLeftPlayer2;
      _setKey["right2"] = &CommandModel::setKeyMoveRightPlayer2;
      _setKey["down2"] = &CommandModel::setKeyMoveDownPlayer2;
      _changeButtonAction["attack1"] = &CommandModel::changeAttackPlayer1;
      _changeButtonAction["left1"] = &CommandModel::changeMoveLeftPlayer1;
      _changeButtonAction["right1"] = &CommandModel::changeMoveRightPlayer1;
      _changeButtonAction["down1"] = &CommandModel::changeMoveDownPlayer1;
      _changeButtonAction["up1"] = &CommandModel::changeMoveUpPlayer1;
      _changeButtonAction["attack2"] = &CommandModel::changeAttackPlayer2;
      _changeButtonAction["left2"] = &CommandModel::changeMoveLeftPlayer2;
      _changeButtonAction["right2"] = &CommandModel::changeMoveRightPlayer2;
      _changeButtonAction["down2"] = &CommandModel::changeMoveDownPlayer2;
      _changeButtonAction["up2"] = &CommandModel::changeMoveUpPlayer2;
      _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
				 "CommandPage");
      pushInCollection();
      _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
				 "KeyPadButtonPage1");
      loadButtonKey(_keyPlayer1);
      _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
				 "Player2");
      loadButtonKey(_keyPlayer2);
      _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
				 "SettingPage");
      auto collection = _loader.getButtons();
      auto it = std::find_if(collection.begin(), collection.end(),
			     [this](MenuLoader::Button const& b) {
			       return b.text == "PREV.";
			     });
      if (it != collection.end()) {
	_graphic->loadButton(std::string("GUI") + it->text,
			     "TaharezLook/Button", it->text,
			     GraphicMenu::Pos{ it->ax, it->ay, it->bx, it->by },
			     GraphicMenu::Size{ it->sax, it->say, it->sbx, it->sby });
	_graphic->bindEventToWidget(std::string("GUI") + it->text,
				    &CommandModel::prev, this);
	_buttons.push_back(std::string("GUI") + it->text);
      }
      _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
				 "ResetHard");
      auto butLoad = _loader["reset"];
      _graphic->loadButton(butLoad.text, "TaharezLook/Button", butLoad.text,
			   GraphicMenu::Pos{ butLoad.ax, butLoad.ay, butLoad.bx,
			       butLoad.by },
			   GraphicMenu::Size{ butLoad.sax, butLoad.say, butLoad.sbx,
			       butLoad.sby });
      _graphic->bindEventToWidget(butLoad.text, &CommandModel::resetConfiguration,
				  this);
      _buttons.push_back(butLoad.text);
    }

  void		CommandModel::loadKeysPlayer() {
    if (!event::KeyCollection::isLoaded(ConfigurationLoader::getFile("keys.json")))
      event::KeyCollection::load(ConfigurationLoader::getFile("keys.json"));
    _keyPlayer1 = event::KeyCollection::getKeysOf("player1");
    _keyPlayer2 = event::KeyCollection::getKeysOf("player2");
  }

  void		CommandModel::removeControlButtons(std::string const& filename,
						   std::string const& categorie) {
    _loader.loadButtonFromFile(filename, categorie);
    auto collection = _loader.getButtons();
    std::for_each(collection.begin(), collection.end(),
		  [this](MenuLoader::Button const& but) {
		    auto it = this->_actionButton.find(but.text);
		    if (it != _actionButton.end()) {
		      std::cout << "BUTTON: " << it->second << std::endl;
		      this->_graphic->removeChildWindow(it->second);
		      this->_actionButton.erase(it);
		      this->_buttons.erase(std::remove(this->_buttons.begin(),
						       this->_buttons.end(),
						       it->second),
		      			   _buttons.end());
		    }
		  });
  }

  bool		CommandModel::resetConfiguration(CEGUI::EventArgs const& arg) {
    removeControlButtons(ConfigurationLoader::getFile("menu.json"),
			 "KeyPadButtonPage1");
    removeControlButtons(ConfigurationLoader::getFile("menu.json"), "Player2");
    _actionButton.clear();
    event::KeyCollection::load(ConfigurationLoader::getFile("keys.json"));
    _keyPlayer1 = event::KeyCollection::getKeysOf("player1");
    _keyPlayer2 = event::KeyCollection::getKeysOf("player2");
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
			       "KeyPadButtonPage1");
    loadButtonKey(_keyPlayer1);
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"), "Player2");
    loadButtonKey(_keyPlayer2);
    return true;
  }

  bool		CommandModel::prev(CEGUI::EventArgs const& arg) {
    AModel::_ret = false;
    removeAll();
    return true;
  }


  /*
  ** Both of the function are there to change keys !
  */

  void		CommandModel::changeKey(CEGUI::String const& text, int oldkey,
					std::string const& nameButton) {
    std::string	str{ text.begin(), text.end() };
    if (nameButton.size() >= str.size())
      return ;
    std::string sub { str.substr(nameButton.size(), str.size()) };
    auto const c = (*sub.begin());
    try {
      event::KeyCollection::setKey(oldkey, static_cast<int>(c));
      std::string	name(1, static_cast<char>(oldkey));
      CEGUI::Window *win = _graphic->getWindow(name);
      std::string newKey{ 1, static_cast<char>(c) };
      win->setText(newKey);
    }
    catch (indie::KeyCollectionException const& ce) {
    }
    _isChangedTheKey = true;
  }

  void		CommandModel::getTextBox(std::string const& keyName) {
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
			       "ButtonConfigurationPage");
    auto butName = _loader["press"];
    CEGUI::Editbox *editBox = static_cast<CEGUI::Editbox* >(_graphic->getWindow(butName.text));
    CEGUI::String text = editBox->getText();
    auto it = _actionButton.find(keyName);
    auto c = it->second.begin();
    changeKey(text, static_cast<int>(*c), butName.text);
    std::string	name{ text.begin(), text.end() };
    _graphic->removeChildWindow(butName.text);
    _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), butName.text),
		   _buttons.end());
  }

  /*
  ** When an event is triggered, those functions change the key.
  */

  bool		CommandModel::setKeyMoveUpPlayer1(CEGUI::EventArgs const& arg) {
    getTextBox("up1");
    return true;
  }

  bool		CommandModel::setKeyMoveDownPlayer1(CEGUI::EventArgs const& arg) {
    getTextBox("down1");
    return true;
  }

  bool		CommandModel::setKeyMoveRightPlayer1(CEGUI::EventArgs const& arg) {
    getTextBox("right1");
    return true;
  }

  bool		CommandModel::setKeyMoveLeftPlayer1(CEGUI::EventArgs const& arg) {
    getTextBox("left1");
    return true;
  }

  bool		CommandModel::setKeyAttackPlayer1(CEGUI::EventArgs const& arg) {
    getTextBox("attack1");
    return true;
  }

  bool		CommandModel::setKeyMoveUpPlayer2(CEGUI::EventArgs const& arg) {
    getTextBox("up2");
    return true;
  }

  bool		CommandModel::setKeyMoveDownPlayer2(CEGUI::EventArgs const& arg) {
    getTextBox("down2");
    return true;
  }

  bool		CommandModel::setKeyMoveLeftPlayer2(CEGUI::EventArgs const& arg) {
    getTextBox("left2");
    return true;
  }

  bool		CommandModel::setKeyMoveRightPlayer2(CEGUI::EventArgs const& arg) {
    getTextBox("right2");
    return true;
  }

  bool		CommandModel::setKeyAttackPlayer2(CEGUI::EventArgs const& arg) {
    getTextBox("attack2");
    return true;
  }

  /*
  ** When an event is triggered, this function display the editbox
  */

  void		CommandModel::setEventToEditBox(CommandModel::FsetKey_t function) {
    _isChangedTheKey = false;
    _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
			       "ButtonConfigurationPage");
    auto butName = _loader["press"];
    try {
      _graphic->loadButton(butName.text, "TaharezLook/Editbox", butName.text,
			   GraphicMenu::Pos{ butName.ax, butName.ay,
			       butName.bx, butName.by },
			   GraphicMenu::Size{ butName.sax, butName.say,
			       butName.sbx, butName.sby });
      _graphic->bindEventToWidget(butName.text, function, this,
				  CEGUI::Editbox::EventTextAccepted);
      _buttons.push_back(butName.text);
    }
    catch (CEGUI::Exception const& ce) {
    }
  }

  /*
  ** The followings functions display the edit box which allow the user to
  ** enter a new key, those functions are a hack, because of CEGUI I have no
  ** choice, except a if forest !
  */

  bool		CommandModel::changeMoveUpPlayer1(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveUpPlayer1);
    return true;
  }

  bool		CommandModel::changeMoveDownPlayer1(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveDownPlayer1);
    return true;
  }

  bool		CommandModel::changeMoveLeftPlayer1(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveLeftPlayer1);
    return true;
  }

  bool		CommandModel::changeMoveRightPlayer1(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveRightPlayer1);
    return true;
  }

  bool		CommandModel::changeAttackPlayer1(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyAttackPlayer1);
    return true;
  }

  bool		CommandModel::changeMoveUpPlayer2(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveUpPlayer2);
    return true;
  }

  bool		CommandModel::changeMoveDownPlayer2(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveDownPlayer2);
    return true;
  }

  bool		CommandModel::changeMoveLeftPlayer2(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveLeftPlayer2);
    return true;
  }

  bool		CommandModel::changeMoveRightPlayer2(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyMoveRightPlayer2);
    return true;
  }

  bool		CommandModel::changeAttackPlayer2(CEGUI::EventArgs const& arg) {
    setEventToEditBox(&CommandModel::setKeyAttackPlayer2);
    return true;
  }

  /*
  ** This function load all the events and display the command button
  */

  void		CommandModel::loadButtonKey(CommandModel::collection_t const &button) {
    auto collection = _loader.getButtons();
    for (auto it : collection) {
      auto buttonType = _buttonKey.find(it.text);
      if (buttonType != _buttonKey.end()) {
	std::string	name{ buttonType->second };
	auto nameBut = std::find_if(button.begin(), button.end(),
				    [this, &name](event::key const& key) {
				      return key.action == name;
				    });
	if (nameBut == button.end())
	  return ;
	std::string	butName(1, static_cast<char>(nameBut->value));
	_graphic->loadButton(butName, "TaharezLook/Button", butName,
			     GraphicMenu::Pos{ it.ax, it.ay, it.bx, it.by },
			     GraphicMenu::Size{ it.sax, it.say, it.sbx, it.sby });
	auto itAction = _changeButtonAction.find(it.text);
	if (itAction != _changeButtonAction.end())
	  _graphic->bindEventToWidget(butName, itAction->second, this);
	_buttons.push_back(butName);
	_actionButton[it.text] = butName;
      }
    }
  }

  bool		CommandModel::_update() {
    AModel::_ret = true;
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& name) {
		    this->_graphic->setVisibleButton(name);
		  });
    _graphic->render();
    return AModel::_ret;
  }
}
