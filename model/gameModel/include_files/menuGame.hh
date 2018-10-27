#pragma once

#include	<functional>
#include	<memory>
#include	"componentType.hh"
#include	"AMenuModel.hh"
#include	"GraphicMenu.hh"

namespace	indie  {
  class		GameMenu : public AMenuModel {
    typedef std::shared_ptr<GraphicMenu>	graphicMenu_t;
    typedef std::function<void(ecs::entity const, std::size_t&)> modificationFunc_t;
  public:
    GameMenu(graphicMenu_t& graphic, std::size_t nbrPlayer = 1);
    ~GameMenu();
    void			erase();
    bool			quit(CEGUI::EventArgs const& arg);
    bool			restart(CEGUI::EventArgs const& arg);
    bool			sound(CEGUI::EventArgs const& arg);
    bool			manageSound(CEGUI::EventArgs const& arg);
    bool			pause(CEGUI::EventArgs const& arg);
    bool			openInventory1(CEGUI::EventArgs const& arg);
    bool			openInventory2(CEGUI::EventArgs const& arg);
    bool			isPaused() const;
    GameMenu			&setHealthPlayer1(ecs::healthComponent& health);
    GameMenu			&setHealthPlayer2(ecs::healthComponent& health);
    GameMenu			&setStuffPlayer1(ecs::stuffComponent& stuff);
    GameMenu			&setStuffPlayer2(ecs::stuffComponent& stuff);
    GameMenu			&setPotion(ecs::collectionPotion& potion);
    GameMenu			&setRenforce(ecs::collectionRenforce& renforce);
    GameMenu			&setSpeed(ecs::collectionSpeed& speed);
    void			pushHealth(ecs::healthComponent *health,
					   std::string const& button);
    bool			usePotionP1(CEGUI::EventArgs const& arg);
    bool			usePotionP2(CEGUI::EventArgs const& arg);
    bool			useRenforceP1(CEGUI::EventArgs const& arg);
    bool			useRenforceP2(CEGUI::EventArgs const& arg);
    bool			useSpeedP1(CEGUI::EventArgs const& arg);
    bool			useSpeedP2(CEGUI::EventArgs const& arg);
    bool			save(CEGUI::EventArgs const& ce);
    bool			needToSave() const;
    void			notifySave();
    void			notifyDead(ecs::entity const id);
  private:
    bool			_update() override;
    bool		openInventory(std::string const& section,
				      ecs::stuffComponent *stuff,
				      std::string const& potionName,
				      std::string const& renforceName,
				      std::string const& speedName,
				      std::size_t& nbrPotion, std::size_t& nbrRenforce,
				      std::size_t& nbrSpeed);
    bool		isInventoryBox(std::string const& button,
				       std::string const& potionName,
				       std::string const& renforceName,
				       std::string const& speedName) const;
    void		displayInventoryContent(std::string const& section,
						ecs::stuffComponent *stuff,
						std::string const&, std::string const&,
						std::string const&, std::size_t&,
						std::size_t&, std::size_t&);
    void		displayContent(ecs::stuffComponent *stuff,
				       modificationFunc_t const& function,
				       std::string const& section, std::size_t& nbr);
    void		modifyPotion(ecs::entity const id, std::size_t&);
    void		modifyRenforce(ecs::entity const id, std::size_t&);
    void		modifySpeed(ecs::entity const id, std::size_t&);
    template<typename T>
    bool		isConcerned(ecs::entity const id, T *collection) const;
    template<typename T>
    void		useComponentInStuff(ecs::stuffComponent *stuff, T *collection,
					    std::size_t& nbr);
    void		updateInventoryPlayer(ecs::stuffComponent *stuff,
					      std::size_t& potion,
					      std::size_t& renforce,
					      std::size_t& speed,
					      bool isOpen);
    void		updateInventory(ecs::stuffComponent *stuff,
					std::string const& name,
					modificationFunc_t const& modifFunction,
					std::size_t& nbr);
    void		updateInventoryPlayer1();
    void		updateInventoryPlayer2();
    void		removeButtons(std::string const& potionName,
				      std::string const& renforceName,
				      std::string const& speedName);
    void		displaySound(MenuLoader::Button const& bSound);
    void		updateHealth(ecs::healthComponent *health,
				     MenuLoader::Button const& progress);
    void		displayHealth(ecs::healthComponent *health,
				      MenuLoader::Button const& progress);
  private:
    bool			_isPaused;
    ecs::healthComponent	*_healthPlayer1;
    ecs::healthComponent	*_healthPlayer2;
    ecs::stuffComponent		*_stuffPlayer1;
    ecs::stuffComponent		*_stuffPlayer2;
    ecs::collectionPotion	*_potions;
    ecs::collectionRenforce	*_renforce;
    ecs::collectionSpeed	*_speed;
    std::size_t			_nbrPotionP1;
    std::size_t			_nbrRenforceP1;
    std::size_t			_nbrSpeedP1;
    std::size_t			_nbrPotionP2;
    std::size_t			_nbrRenforceP2;
    std::size_t			_nbrSpeedP2;
    bool			_isSaved;
    bool			_player1OpenInventory;
    bool			_player2OpenInventory;
  };
}
