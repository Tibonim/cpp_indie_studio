#pragma once

#include <map>
#include "KeyCollection.hh"
#include "GraphicMenu.hh"
#include "AMenuModel.hh"

namespace	indie {
  class		SettingModel : public AMenuModel {
    typedef std::shared_ptr<GraphicMenu>	graphicMenu_t;
    typedef std::vector<std::string>		button_t;
    typedef std::vector<event::key>		collection_t;
    typedef std::map<std::string, std::string>	buttonValue_t;
  public:
    SettingModel(graphicMenu_t& graphic);
    bool	prev(CEGUI::EventArgs const& arg);
    bool	command(CEGUI::EventArgs const& arg);
  private:
    bool		_update() override;
    void		loadButtonKey(collection_t const& button);
  private:
    collection_t	_keyPlayer1;
    collection_t	_keyPlayer2;
    buttonValue_t	_buttonKey;
  };
}
