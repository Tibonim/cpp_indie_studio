
#include "CollectionException.hh"
#include "CustomException.hh"
#include "View.hh"

void		ov::View::NewMap()
{
  this->displayed.clear();
  Ogre::MeshManager::getSingleton().createPlane("ground",
						Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
						this->Plane,
						2000, 2000, 20, 20,
						true,
						1, 5, 5,
						Ogre::Vector3::UNIT_Z);
  this->Map = this->SceneMgr->createEntity("ground");
  this->SceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(this->Map);
  this->Map->setMaterialName("Examples/Floor");
  this->SceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
  if (this->SceneMgr->hasLight("MainLight"))
    {
      this->Light = this->SceneMgr->createLight("MainLight");
      this->Light->setDiffuseColour(Ogre::ColourValue::White);
      this->Light->setSpecularColour(Ogre::ColourValue(0, 0, 1.0));
      this->Light->setType(Ogre::Light::LT_POINT);
      this->Light->setPosition(-1, -1, 0);
      this->Light->setPosition(Ogre::Vector3(200, 200, 0));
      this->Light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    }
  this->mapSet = true;
  this->SceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
}

void		ov::View::NewEntity(ecs::graphicComponent const &graph,
				    ecs::entity it,
				    Ogre::Vector3 const &vec_pos,
				    Ogre::Vector3 const &vec_dir,
				    ecs::collectionPlayer &playC)
{
  Ogre::Entity		*ogre = this->SceneMgr->createEntity(graph.meshName);
  Ogre::SceneNode	*node = this->SceneMgr->getRootSceneNode()->createChildSceneNode(vec_pos);
  node->attachObject(ogre);
  node->lookAt(vec_dir, Ogre::Node::TS_PARENT);
  VEntity		*entity;
  try {
    auto&		play = playC.getComponent(it);
    entity = new VEntity(it, ogre, node, play.idPlayer);
    if (play.idPlayer > 1)
      this->twoPlayer = true;
    this->vec_cam[play.idPlayer] = vec_pos;
    ogre->setQueryFlags(2);
  }
  catch (indie::CollectionException const&) {
    entity = new VEntity(it, ogre, node);
    ogre->setQueryFlags(3);
  };
  if (!this->Collision)
    this->Collision = new Collision::CollisionTools();
  this->Collision->register_entity(ogre, Collision::COLLISION_ACCURATE);
  Change::const_iterator	cit = this->needChange.find(graph.meshName);
  if (cit != this->needChange.end())
    (*cit->second)(entity);
  if (graph.textureName != "")
    {
      Ogre::MaterialPtr materialPtr =Ogre::MaterialManager::getSingleton().getByName(graph.textureName);
      ogre->setMaterial(materialPtr);
    }
  _idEntities[it] = ogre;
  this->displayed.push_back(entity);
}

Ogre::Entity *ov::View::getOgreEntityById(ecs::entity id) {
  auto it = _idEntities.find(id);
  if (it == _idEntities.end())
    return NULL;
  return it->second;
}

ecs::entity ov::View::willCollide(ecs::entity id, float x, float y, float z) {
  VEntity *entity = getEntityById(id);
  Ogre::Vector3 to{x, y, z};
  to.x = -z;
  to.z = -x;
  if (!entity)
    return -1;
  Collision::SCheckCollisionAnswer ret = Collision->check_ray_collision(entity->getNode()->getPosition(), to, 10, 0, 3, entity->getOgre(), true);
  if (ret.collided)
    {
      for (auto it = _idEntities.begin(); it != _idEntities.end(); ++it) {
	if (it->second == ret.entity)
	  return it->first;
      }
    }
  return -1;
}

void		ov::View::UpdateEntity(ecs::graphicComponent &graph,
				       ecs::entity it,
				       const Ogre::Vector3 &vec_pos,
				       const Ogre::Vector3 &vec_dir)
{
  VEntity		*entity = this->getEntityById(it);
  entity->getNode()->lookAt(vec_pos + vec_dir, Ogre::Node::TS_PARENT);
  if (vec_pos != entity->getNode()->getPosition())
    {
      if (strncmp(entity->getPlayer().c_str(), "player", 6) == 0)
	{
	  this->vec_cam[entity->getPlayerNb()] = entity->getNode()->getPosition();
	}
      entity->setDest(vec_pos);
      entity->move(graph.animationName);
      entity->getNode()->lookAt((vec_pos + vec_dir), Ogre::Node::TS_PARENT);
    }
  else if (graph.animationName != "" || entity->getLastAnim() == "Attack"
	   || entity->getLastAnim() == "Die")
    {
      if (entity->animate(graph.animationName) == 1)
	graph.animationName = "";
    }
  else if (entity->getAnim() != 0)
    {
      entity->getAnim()->setTimePosition(0);
      entity->setTime(0);
      entity->getAnim()->setEnabled(false);
    }
}

void		ov::View::DisplayEntities(const ecs::entityCollection& id,
					  ecs::collectionGraphic& graphC,
					  ecs::collectionPos& posC,
					  ecs::collectionDir& dirC,
					  ecs::collectionPlayer& playC)
{
  static int	i = 0;
  auto entities = id.getEntities();
  try {
    updateEventCollection();
    for(auto const &it : entities)
      {
	try {
	  auto&	graph = graphC.getComponent(it);
	  auto&	pos = posC.getComponent(it);
	  auto&	dir = dirC.getComponent(it);
	  const Ogre::Vector3	vec_pos(-pos.z, pos.y, -pos.x);
	  const Ogre::Vector3	vec_dir(dir.z, dir.y, dir.x);
	  if (i == 0)
	    {
	      i++;
	      this->vec_cam = new Ogre::Vector3[3];
	      this->vec_cam[0] = Ogre::Vector3(0, 550, 0);
	      this->vec_cam[1] = Ogre::Vector3(0, 0, 0);
	      this->vec_cam[2] = Ogre::Vector3(0, 0, 0);
	    }
	  if ((!this->is_in_entity(it)) || it == 0)
	    NewEntity(graph, it, vec_pos, vec_pos + vec_dir, playC);
	  else
	    {
	      UpdateEntity(graph, it, vec_pos, vec_dir);
	      if (this->twoPlayer == false)
		vec_cam[2] = vec_cam[1];
	      this->Camera->setPosition(vec_cam[0].x + ((vec_cam[1].x + vec_cam[2].x) / 2),
					vec_cam[0].y + 0,
					vec_cam[0].z + ((vec_cam[1].z + vec_cam[2].z) / 2));
	      this->Camera->lookAt((vec_cam[1].x + vec_cam[2].x) / 2,
				   0,
				   (vec_cam[1].z + vec_cam[2].z) / 2);
	    }
	}
	catch (indie::CollectionException const&) {
	}
      }
    this->startRendering();
  }
  catch (indie::CustomException const& c) {
    std::cout << c.what() << std::endl;
    throw;
  };
}

void			ov::View::deleteByEntity(ecs::entity id)
{
  auto it = std::find_if(this->displayed.begin(), this->displayed.end(),
			 [&, this](VEntity const *e) { return e->getId() == id; });
  if (it == this->displayed.end())
    return ;
  this->Collision->remove_entity((*it)->getOgre());
  this->SceneMgr->destroyEntity((*it)->getOgre());
  this->SceneMgr->destroySceneNode((*it)->getNode());
  this->displayed.erase(std::remove_if(this->displayed.begin(), this->displayed.end(),
				       [&, this](VEntity const *e) {
					 return e->getId() == id;
				       }),
			this->displayed.end());
}

void			ov::View::startRendering() {
  Ogre::WindowEventUtilities::messagePump();
  this->Root->renderOneFrame();
}

void		ov::View::DestroyMap()
{
  delete this->Collision;
  this->Collision = NULL;
  for (auto const &it : this->displayed)
    {
      it->getNode()->detachAllObjects();
      this->SceneMgr->destroyEntity(it->getOgre());
      this->SceneMgr->destroySceneNode(it->getNode());
    }
  this->displayed.clear();
  this->SceneMgr->destroyEntity(this->Map);
  Ogre::Vector3	vec_cam(0, 550, 0);
  this->Camera->setPosition(vec_cam);
  this->Camera->lookAt(Ogre::Vector3(0, 0, 0));
  this->mapSet = false;
}

ov::VEntity		*ov::View::getEntityById(ecs::entity id) const
{
  for (auto const &it : this->displayed)
    if (it->getId() == id)
      return (it);
  return (NULL);
}

void		ov::View::updateEventCollection() const
{
  std::vector<VEntity *> payload;

  for (auto const &it : this->displayed)
    {
      payload.push_back(it);
    }
  if (EventManager)
    EventManager->setEntityCollection(payload);
}

bool		ov::View::isMapSet() const
{
  return (this->mapSet);
}

bool		ov::View::is_in_entity(ecs::entity id) const
{
  for (auto const &it : this->displayed)
    if (it->getId() == id)
      return (true);
  return (false);
}
