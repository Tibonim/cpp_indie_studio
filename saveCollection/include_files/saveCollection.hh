#pragma	once

#include	<vector>
#include	<string>
#include        <iostream>
#include        <fstream>
#include	"json/json.h"
#include	"SaveCollectionException.hh"
#include	"entityCollection.hh"
#include	"componentType.hh"

namespace	saver {
  class		SaveCollection {
  public:
    SaveCollection() {};
    ~SaveCollection() {};
    void                saveEntity(std::string const&, ecs::entityCollection::entityList const&) const;
    void		loadEntity(std::string const&, ecs::entityCollection&) const;
    void		loadComponent(std::string const&, ecs::scoreComponent&) const;
    void                loadComponent(std::string const&, ecs::collectionDir&) const;
    void                loadComponent(std::string const&, ecs::collectionVelocity&) const;
    void                loadComponent(std::string const&, ecs::collectionPos&) const;
    void                loadComponent(std::string const&, ecs::collectionStuff&) const;
    void                loadComponent(std::string const&, ecs::collectionHealth&) const;
    void                loadComponent(std::string const&, ecs::collectionGraphic&) const;
    void                loadComponent(std::string const&, ecs::collectionStrength&) const;
    void                loadComponent(std::string const&, ecs::collectionFaction&) const;
    void                loadComponent(std::string const&, ecs::collectionScript&) const;
    void                loadComponent(std::string const&, ecs::collectionRange&) const;
    void                loadComponent(std::string const&, ecs::collectionPlayer&) const;
    void                loadComponent(std::string const&, ecs::collectionDefense&) const;
    void                loadComponent(std::string const&, ecs::collectionDamage&) const;
    void		loadComponent(std::string const&, ecs::collectionAttack&) const;
    template<class Collection>
    void                loadComponent(std::string const&, Collection&,
				      std::string const&) const;
    void		read(std::string const&, Json::Value&) const;
    void		write(std::string const&, Json::Value const&) const;
    template<class Collection>
    void                saveComponent(std::string const&, Collection&, std::string const&,
				      ecs::entityCollection::entityList const&) const;
    void		saveComponent(std::string const&, ecs::collectionRange&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionScript&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionFaction&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionStrength&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionGraphic&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionHealth&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionStuff&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionPos&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionVelocity&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionDir&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionPlayer&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionDefense&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::collectionDamage&,
				      ecs::entityCollection::entityList const&) const;
    void		saveComponent(std::string const&, ecs::collectionAttack&,
				      ecs::entityCollection::entityList const&) const;
    void                saveComponent(std::string const&, ecs::scoreComponent&) const;
  };

    template<class Collection>
    void                SaveCollection::loadComponent(std::string const& filename,
						      Collection& collection,
						      std::string const& type) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"][type];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	float value = list[it].get("value", 0).asFloat();
	bool  isUsed = list[it].get("isUsed", 0).asBool();
	collection.addComponent(id, value, isUsed);
      }
    }

  template<class Collection>
  void          SaveCollection::saveComponent(std::string const& filename,
					      Collection& collection, std::string const& type,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"][type];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["value"] = component.value;
	data["isUsed"] = component.isUsed;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"][type] = dir;
    this->write(filename, root);
  }
};
