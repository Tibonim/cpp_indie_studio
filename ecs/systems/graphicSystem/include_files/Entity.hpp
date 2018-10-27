#pragma once

#include "Includes.hh"

#define FRAME 100

namespace	ov
{
  class		VEntity
  {
  private:
    ecs::entity			id;
    Ogre::AnimationState	*Anim;
    Ogre::Entity		*Entity;
    Ogre::SceneNode		*Node;
    Ogre::Vector3		Dest;
    int				Time;
    int				playerNb;
    std::string			player;
    std::string			lastAnim;

  public:
    VEntity(ecs::entity, Ogre::Entity *, Ogre::SceneNode *, int = 0);
    ~VEntity();

    void		setDest(Ogre::Vector3 const &dest);

    ecs::entity		getId() const;
    Ogre::Entity	*getOgre() const;
    Ogre::SceneNode	*getNode() const;
    std::string		getPlayer() const;
    void		setTime(int);
    std::string		getLastAnim() const;
    int			getPlayerNb() const;
    Ogre::AnimationState	*getAnim() const;

    int		animate(std::string const&);
    void	move(std::string const&);
  };
};
