#pragma once

#include <memory>
#include "GraphicMenu.hh"
#include "AModel.hh"
#include "MenuLoader.hh"

namespace	indie {
  class		MenuModel : public AModel {
  public:
    MenuModel();
    bool	quit(CEGUI::EventArgs const& event);
    bool	settingsMenu(CEGUI::EventArgs const& event);
    bool	play(CEGUI::EventArgs const& event);
    bool	continueGame(CEGUI::EventArgs const& event);
    bool	handleSound(CEGUI::EventArgs const& event);
    bool	playWithOnePlayer(CEGUI::EventArgs const& event);
    bool	playWithTwoPlayer(CEGUI::EventArgs const& event);
  private:
    void	eraseMenu();
    void	pushInCollection(MenuLoader const& loader);
    void	removePlayButton();
  private:
    bool	_update() override;
    typedef std::shared_ptr<GraphicMenu>	graphicMenu_t;
    typedef std::vector<std::string>		buttonContainer_t;
    typedef std::unique_ptr<IModel>		modelPtr_t;
    typedef std::vector<modelPtr_t>		modelContainer_t;
    graphicMenu_t		_graphic;
    buttonContainer_t		_buttons;
    modelContainer_t		_modelContainer;
    bool			_isPlayClicked;
  };
}
