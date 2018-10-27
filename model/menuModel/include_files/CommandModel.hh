#pragma once

#include "GraphicMenu.hh"
#include "MenuLoader.hh"
#include "AMenuModel.hh"

namespace	indie {
  class		CommandModel : public AMenuModel {
    typedef std::shared_ptr<GraphicMenu>	graphicMenu_t;
    typedef std::vector<std::string>		button_t;
    typedef std::vector<event::key>		collection_t;
    typedef std::map<std::string, std::string>	buttonValue_t;
    typedef bool (CommandModel::*FsetKey_t) (CEGUI::EventArgs const&);
    typedef std::map<std::string, FsetKey_t>	setKey_t;
  public:
    CommandModel(graphicMenu_t& graphic);
    bool	prev(CEGUI::EventArgs const& arg);
    bool	setKeyMoveUpPlayer1(CEGUI::EventArgs const& arg);
    bool	setKeyMoveDownPlayer1(CEGUI::EventArgs const& arg);
    bool	setKeyMoveLeftPlayer1(CEGUI::EventArgs const& arg);
    bool	setKeyMoveRightPlayer1(CEGUI::EventArgs const& arg);
    bool	setKeyAttackPlayer1(CEGUI::EventArgs const& arg);
    bool	setKeyMoveUpPlayer2(CEGUI::EventArgs const& arg);
    bool	setKeyMoveDownPlayer2(CEGUI::EventArgs const& arg);
    bool	setKeyMoveLeftPlayer2(CEGUI::EventArgs const& arg);
    bool	setKeyMoveRightPlayer2(CEGUI::EventArgs const& arg);
    bool	setKeyAttackPlayer2(CEGUI::EventArgs const& arg);
    bool	changeMoveLeftPlayer1(CEGUI::EventArgs const& arg);
    bool	changeMoveRightPlayer1(CEGUI::EventArgs const& arg);
    bool	changeMoveDownPlayer1(CEGUI::EventArgs const& arg);
    bool	changeMoveUpPlayer1(CEGUI::EventArgs const& arg);
    bool	changeAttackPlayer1(CEGUI::EventArgs const& arg);
    bool	changeMoveLeftPlayer2(CEGUI::EventArgs const& arg);
    bool	changeMoveRightPlayer2(CEGUI::EventArgs const& arg);
    bool	changeMoveDownPlayer2(CEGUI::EventArgs const& arg);
    bool	changeMoveUpPlayer2(CEGUI::EventArgs const& arg);
    bool	changeAttackPlayer2(CEGUI::EventArgs const& arg);
    bool	resetConfiguration(CEGUI::EventArgs const& arg);
  private:
    bool		_update() override;
    void		loadButtonKey(collection_t const& button);
    void		changeKey(CEGUI::String const& text, int oldkey,
				  std::string const& nameButton);
    void		getTextBox(std::string const& keyName);
    void		setEventToEditBox(FsetKey_t function);
    void		loadKeysPlayer();
    void		removeControlButtons(std::string const& filename,
					     std::string const& categorie);
  private:
    collection_t	_keyPlayer1;
    collection_t	_keyPlayer2;
    buttonValue_t	_buttonKey;
    bool		_isChangedTheKey;
    setKey_t		_setKey;
    buttonValue_t	_actionButton;
    setKey_t		_changeButtonAction;
  };
}
