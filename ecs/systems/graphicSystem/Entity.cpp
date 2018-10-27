#include "Entity.hpp"

ov::VEntity::VEntity(ecs::entity id, Ogre::Entity *ogre,
		     Ogre::SceneNode *node, int player) :
  Anim(0),
  Dest(Ogre::Vector3::ZERO)
{
  this->id = id;
  this->Entity = ogre;
  this->Node = node;
  this->Time = 0;
  if (player != 0)
    {
      this->playerNb = player;
      this->player = "player" + std::to_string(player);
    }
}

ov::VEntity::~VEntity()
{
}

int		ov::VEntity::animate(std::string const &animation)
{
  if (this->Time == 0)
    {
      this->lastAnim = animation;
      this->Anim = this->Entity->getAnimationState(animation);
      this->Anim->setEnabled(true);
      this->Anim->setTimePosition(0);
      this->Time++;
    }
  else if (this->lastAnim != "Attack" && animation != "" &&
	   this->lastAnim != animation)
    {
      this->Time = 0;
      this->Anim->setEnabled(false);
      this->lastAnim = animation;
      this->Anim = this->Entity->getAnimationState(animation);
      this->Anim->setEnabled(true);
      this->Anim->setTimePosition(0);
      this->Time++;
    }
  else if (this->Time >= FRAME)
    {
      this->Time = 0;
      this->Anim->setEnabled(false);
      this->lastAnim = "";
      return (1);
    }
  else
    {
      this->Anim->addTime(this->Anim->getLength() / FRAME);
      this->Time++;
    }
  return (0);
}

void		ov::VEntity::move(std::string const &anim)
{
  if (this->Time < FRAME)
    {
      this->Node->setPosition(this->Dest);
      if (anim != "")
      	this->animate(anim);
      else
      	this->Time++;
    }
  else
    this->Time = 0;
}

void		ov::VEntity::setDest(Ogre::Vector3 const &dest)
{
  this->Dest = dest;
}

ecs::entity	ov::VEntity::getId() const
{
  return (this->id);
}

Ogre::Entity	*ov::VEntity::getOgre() const
{
  return (this->Entity);
}

Ogre::SceneNode	*ov::VEntity::getNode() const
{
  return (this->Node);
}

std::string	ov::VEntity::getPlayer() const
{
  return (this->player);
}

Ogre::AnimationState	*ov::VEntity::getAnim() const
{
  return (this->Anim);
}

void			ov::VEntity::setTime(int time)
{
  this->Time = time;
}

std::string		ov::VEntity::getLastAnim() const
{
  return (this->lastAnim);
}

int			ov::VEntity::getPlayerNb() const
{
  return (this->playerNb);
}
