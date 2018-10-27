#include "View.hh"

void		ChangeMyMesh(ov::VEntity *ent)
{
  ent->getNode()->setScale(5, 5, 5);
}

void		ChangeMyBoss(ov::VEntity *ent)
{
  ent->getNode()->setScale(15, 15, 15);
}

void		ChangeMyBoost(ov::VEntity *ent)
{
  ent->getNode()->setScale(0.2, 0.2, 0.2);
}

void		ChangeMyWall(ov::VEntity *ent)
{
  ent->getNode()->setScale(80, 80, 80);
}

ov::View::View() : Root(0), ResourcesCfg(Ogre::StringUtil::BLANK),
		   PluginsCfg(Ogre::StringUtil::BLANK), Plane(Ogre::Vector3::UNIT_Y, 0)
{
  this->createRoot();
  this->setUpRessources();
  if (this->Root->restoreConfig() || this->Root->showConfigDialog());
  this->Window = this->Root->initialise(true);
  this->SceneMgr = this->Root->createSceneManager(Ogre::ST_GENERIC);
  this->Overlay = new Ogre::OverlaySystem();
  this->SceneMgr->addRenderQueueListener(this->Overlay);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  this->configCam();
  this->configViewport();
  this->EventManager = new event::EventManager(Window, Root, Camera);
  this->EventManager->createFrameListener();
  this->mapSet = false;
  this->Collision = new Collision::CollisionTools();
  this->needChange.insert(std::make_pair("MyMate0.mesh", &ChangeMyMesh));
  this->needChange.insert(std::make_pair("MyMate1.mesh", &ChangeMyMesh));
  this->needChange.insert(std::make_pair("MyRobot.mesh", &ChangeMyBoss));
  this->needChange.insert(std::make_pair("MyOrc.mesh", &ChangeMyMesh));
  this->needChange.insert(std::make_pair("Wall.mesh", &ChangeMyWall));
  this->needChange.insert(std::make_pair("Maze.mesh", &ChangeMyWall));
  this->needChange.insert(std::make_pair("BoostA.mesh", &ChangeMyBoost));
  this->needChange.insert(std::make_pair("BoostV.mesh", &ChangeMyBoost));
  this->needChange.insert(std::make_pair("BoostH.mesh", &ChangeMyBoost));
  this->twoPlayer = false;
}

ov::View::~View()
{
  //Ogre::WindowEventUtilities::removeWindowEventListener(this->Window, this);
  // if (this->CameraMan)
  //   delete (this->CameraMan);
  // this->windowClosed(this->Window);
  // if (this->Root)
  //   delete (this->Root);
}

void		ov::View::windowClosed(Ogre::RenderWindow const *rw)
{
  if (this->EventManager->getInputManager())
    {
      this->EventManager->getInputManager()->destroyInputObject(this->EventManager->getMouse());
      this->EventManager->getInputManager()->destroyInputObject(this->EventManager->getKeyboard());
      OIS::InputManager::destroyInputSystem(this->EventManager->getInputManager());
      this->EventManager->setInputManager(0);
    }
}

void		ov::View::configViewport()
{
  this->Viewport = this->Window->addViewport(this->Camera);
  this->Viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
  this->Camera->setAspectRatio(Ogre::Real(this->Viewport->getActualWidth()) /
			       Ogre::Real(this->Viewport->getActualHeight()));
}

void		ov::View::configCam()
{
  this->Camera = this->SceneMgr->createCamera("MainCam");
  this->Camera->setPosition(600, 250, 0);
  this->Camera->lookAt(100, 0, 0);
  this->Camera->setNearClipDistance(5);
  this->CameraNode = this->SceneMgr->getRootSceneNode()->createChildSceneNode(this->Camera->getPosition());
  this->CameraNode->attachObject(this->Camera);
}

void		ov::View::setUpRessources()
{
  Ogre::ConfigFile	cf;
  Ogre::String		name;
  Ogre::String		locType;

  cf.load(this->ResourcesCfg);
  Ogre::ConfigFile::SectionIterator cf_it = cf.getSectionIterator();
  while (cf_it.hasMoreElements())
    {
      Ogre::ConfigFile::SettingsMultiMap* set = cf_it.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator it;
      for (it = set->begin(); it != set->end(); ++it)
	{
	  locType = it->first;
	  name = it->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
	}
    }
}

Ogre::SceneManager	*ov::View::getSceneManager() const {
  return SceneMgr;
}

Ogre::Root		*ov::View::getRoot() const {
  return Root;
}

void		ov::View::createRoot()
{
#ifdef _DEBUG
  this->ResourcesCfg = "./config/resources_d.cfg";
  this->PluginsCfg = "./config/plugins_d.cfg";
#else
  this->ResourcesCfg = "./config/resources.cfg";
  this->PluginsCfg = "./config/plugins.cfg";
#endif
  this->Root = new Ogre::Root(this->PluginsCfg);
}
