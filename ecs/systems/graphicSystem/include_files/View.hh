#pragma once

#include "Includes.hh"
#include "Entity.hpp"
#include "NewMOC.h"
#include "EventManager.hh"

typedef void	(*ChangeMesh)(ov::VEntity *);
typedef std::map<std::string, ChangeMesh>	Change;
namespace	ov
{
  class		View
  {
  private:
    std::vector<VEntity *>	displayed;
    std::map<ecs::entity, Ogre::Entity *>	_idEntities;
    Change		needChange;

    Ogre::Root		*Root;
    Ogre::String	ResourcesCfg;
    Ogre::String	PluginsCfg;
    Ogre::RenderWindow	*Window;
    Ogre::Camera	*Camera;
    Ogre::Viewport	*Viewport;
    Ogre::SceneManager	*SceneMgr;
    Ogre::Entity	*Map;
    Ogre::Light		*Light;
    Ogre::Plane		Plane;
    Ogre::SceneNode	*CameraNode;
    event::EventManager	*EventManager;
    Ogre::Vector3	*vec_cam;
    bool		twoPlayer;
    Ogre::Terrain::ImportData	Tdata;
    Ogre::TerrainGlobalOptions	*TGO;
    Ogre::OverlaySystem		*Overlay;
    Collision::CollisionTools *Collision;

    bool		mapSet;

    void		createRoot();
    void		setUpRessources();
    void		configCam();
    void		configViewport();
    void		updateEventCollection() const;
    void		windowClosed(Ogre::RenderWindow const *);
    void		createWalls();

  public:
    View();
    ~View();

    void			NewMap();
    void			NewEntity(ecs::graphicComponent const&, ecs::entity,
					  Ogre::Vector3 const&,
					  Ogre::Vector3 const&,
					  ecs::collectionPlayer&);
    void			UpdateEntity(ecs::graphicComponent&,
					     ecs::entity,
					     const Ogre::Vector3&,
					     const Ogre::Vector3&);
    void			DisplayEntities(const ecs::entityCollection&,
						ecs::collectionGraphic&,
						ecs::collectionPos&,
						ecs::collectionDir&,
						ecs::collectionPlayer&);
    void			deleteByEntity(ecs::entity);

    bool			is_in_entity(ecs::entity) const;
    VEntity			*getEntityById(ecs::entity) const;
    void			startRendering();
    Ogre::SceneManager		*getSceneManager() const;
    Ogre::Root			*getRoot() const;

    void			DestroyMap();
    bool			isMapSet() const;

    Ogre::Entity		*getOgreEntityById(ecs::entity);
    ecs::entity willCollide(ecs::entity, float, float, float);
  };
};
