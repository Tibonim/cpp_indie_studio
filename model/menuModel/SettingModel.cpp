#include <algorithm>
#include "loader.hh"
#include "CommandModel.hh"
#include "SettingsModel.hh"

namespace	indie {
  SettingModel::SettingModel(SettingModel::graphicMenu_t& graphic)
    : AMenuModel{ graphic } {
      _loader.loadButtonFromFile(ConfigurationLoader::getFile("menu.json"),
				 "SettingPage");
      pushInCollection();
      auto itPrevious = std::find_if(_buttons.begin(), _buttons.end(),
				     [](std::string const& name) {
				       return name == "PREV.";
				     });
      if (itPrevious != _buttons.end())
	_graphic->bindEventToWidget(*itPrevious, &SettingModel::prev, this);
      auto itCommand = std::find_if(_buttons.begin(), _buttons.end(),
				    [](std::string const& name) {
				      return name == "COMMANDS";
				    });
      if (itCommand != _buttons.end())
	_graphic->bindEventToWidget(*itCommand, &SettingModel::command, this);
    }

  bool		SettingModel::prev(CEGUI::EventArgs const& arg) {
    AModel::_ret = false;
    removeAll();
    return true;
  }

  void		SettingModel::loadButtonKey(SettingModel::collection_t const& button) {
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
	std::string	butName{ 1, static_cast<char>(nameBut->value) };
	std::cout << butName << std::endl;
	_graphic->loadButton(butName, "TaharezLook/Button", butName,
			     GraphicMenu::Pos{ it.ax, it.ay, it.bx, it.by },
			     GraphicMenu::Size{ it.sax, it.say, it.sbx, it.sby });
	_buttons.push_back(butName);
      }
    }
  }

  bool		SettingModel::command(CEGUI::EventArgs const& args) {
    AModel::_ret = true;
    AModel::_currentModel = std::make_shared<CommandModel>(_graphic);
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& name) {
		    this->_graphic->setInvisibleButton(name);
		  });
    return true;
  }

  bool		SettingModel::_update() {
    AModel::_ret = true;
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& name) {
		    this->_graphic->setVisibleButton(name);
		  });
    _graphic->render();
    return AModel::_ret;
  }
}
