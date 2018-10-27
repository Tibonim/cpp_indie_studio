#include <iostream>
#include	"saveCollection.hh"

namespace		saver {
  void			SaveCollection::read(std::string const& filename,
					     Json::Value& root) const {
    Json::Reader        reader;
    std::filebuf        fd;

    if (!fd.open(filename, std::ios::in))
      throw indie::SaveCollectionException{ "Can not open file: " + filename };
    std::istream        stream(&fd);
    if (!reader.parse(stream, root, false)) {
      fd.close();
      throw indie::SaveCollectionException{ "Format Error in " + filename + reader.getFormattedErrorMessages() };
    }
    fd.close();
  }

  void			SaveCollection::write(std::string const& filename,
					      Json::Value const& root) const {
    std::ofstream       file;
    file.open(filename);
    if (!file)
      throw indie::SaveCollectionException{ "Can not open file: " + filename };
    Json::StyledWriter styledWriter;
    file << styledWriter.write(root);
    file.close();
  }

  void			SaveCollection::saveEntity(std::string const& filename,
						   ecs::entityCollection::entityList const& collection) const {
    Json::Value		root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value		list = root["entitylist"];
    list.clear();
    for (unsigned int it = 0; it < collection.size(); it++) {
      unsigned int val = collection.at(it);
      list.append(val);
    }
    root["entitylist"] = list;
    this->write(filename, root);
  }
  
  void			SaveCollection::loadEntity(std::string const& filename,
						   ecs::entityCollection& collection) const {
      Json::Value		root;
      this->read(filename, root);
      Json::Value		list = root["entitylist"];
      for (auto it = 0; it < list.size(); it++)
	collection.addEntity(list[it].asUInt());
  }

  void			SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionDir& collection) const {
      Json::Value	root;
      this->read(filename, root);
      Json::Value	list = root["Component"]["directionComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt();
	float x = list[it].get("x", 0).asFloat();
	float y = list[it].get("y", 0).asFloat();
	float z = list[it].get("z", 0).asFloat();
	collection.addComponent(id, x, y, z);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionVelocity& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["velocityComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt();
	float vel = list[it].get("velocity", 0).asFloat();
	collection.addComponent(id, vel);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionPos& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["positionComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	float x = list[it].get("x", 0).asFloat();
	float y = list[it].get("y", 0).asFloat();
	float z = list[it].get("z", 0).asFloat();
	collection.addComponent(id, x, y, z);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionStuff& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["collectionStuff"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	Json::Value owned = list[it]["owned"];
	std::vector<ecs::entity> tab;
	for (auto itab = 0; itab != owned.size(); itab++)
	  tab.push_back(owned[itab].asUInt());
	collection.addComponent(id, tab);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionHealth& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["healthComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	float live = list[it].get("live", 0).asFloat();
	collection.addComponent(id, live);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionGraphic& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["graphicComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	std::string meshName = list[it].get("meshName", "").asString();
	std::string textureName = list[it].get("textureName", "").asString();
	std::string animationName = list[it].get("animationName", "").asString();
	collection.addComponent(id, meshName, textureName, animationName);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionStrength& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["strengthComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	float strength = list[it].get("strength", "").asFloat();
	collection.addComponent(id, strength);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionFaction& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["factionComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	ecs::faction type = static_cast<ecs::faction>(list[it].get("type", "").asInt());
	collection.addComponent(id, type);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionScript& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["iaScriptComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	std::string script = list[it].get("script", "").asString();
	collection.addComponent(id, script);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionRange& collection) const {
      Json::Value       root;
      this->read(filename, root);
      Json::Value       list = root["Component"]["rangeComponent"];

      for (auto it = 0; it < list.size(); it++) {
	ecs::entity id = list[it].get("id", 0).asUInt64();
	float x = list[it].get("x", 0).asFloat();
	float y = list[it].get("y", 0).asFloat();
	collection.addComponent(id, x, y);
      }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionDamage& collection) const {
    Json::Value       root;
    this->read(filename, root);
    Json::Value       list = root["Component"]["damageComponent"];

    for (auto it = 0; it < list.size(); it++) {
      ecs::entity id = list[it].get("id", 0).asUInt64();
      float damageValue = list[it].get("damageValue", 0).asFloat();
      collection.addComponent(id, damageValue);
    }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionAttack& collection) const {
    Json::Value       root;
    this->read(filename, root);
    Json::Value       list = root["Component"]["attackComponent"];
    for (auto it = 0; it < list.size(); it++) {
      ecs::entity id = list[it].get("id", 0).asUInt64();
      bool isAttack = list[it].get("isAttack", 0).asFloat();
      collection.addComponent(id, isAttack);
    }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionDefense& collection) const {
    Json::Value       root;
    this->read(filename, root);
    Json::Value       list = root["Component"]["defenseComponent"];

    for (auto it = 0; it < list.size(); it++) {
      ecs::entity id = list[it].get("id", 0).asUInt64();
      float defenseValue = list[it].get("defenseValue", 0).asFloat();
      collection.addComponent(id, defenseValue);
    }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::collectionPlayer& collection) const {
    Json::Value       root;
    this->read(filename, root);
    Json::Value       list = root["Component"]["playerComponent"];

    for (auto it = 0; it < list.size(); it++) {
      ecs::entity id = list[it].get("id", 0).asUInt64();
      int idPlayer = list[it].get("idPlayer", 0).asFloat();
      collection.addComponent(id, idPlayer);
    }
  }

  void                  SaveCollection::loadComponent(std::string const& filename,
						      ecs::scoreComponent& component) const {
    Json::Value       root;
    this->read(filename, root);
    Json::Value       list = root["Component"]["scoreComponent"];

    component.id = list.get("id", 0).asUInt64();
    component.value = list.get("value", 0).asUInt64();
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionDir& collection,
					      ecs::entityCollection::entityList const& list) const {
      Json::Value               root;
      try {
	this->read(filename, root);
      } catch (indie::SaveCollectionException const&) {}
      Json::Value               dir = root["Component"]["directionComponent"];
      dir.clear();
      for (unsigned int it = 0; it < list.size(); it++) {
	try {
	auto component = collection.getComponent(list.at(it));
	Json::Value	data;
	data["id"] = component.id;
	data["x"] = component.x;
	data["y"] = component.y;
	data["z"] = component.z;
	dir.append(data);
	} catch (indie::CollectionException const&) {}
      }
      root["Component"]["directionComponent"] = dir;
      this->write(filename, root);
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionVelocity& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["velocityComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list.at(it));
	Json::Value     data;
	data["id"] = component.id;
	data["velocity"] = component.velocity;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    } 
    root["Component"]["velocityComponent"] = dir;
    this->write(filename, root);
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionPos& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["positionComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list.at(it));
	Json::Value     data;
	data["id"] = component.id;
	data["x"] = component.x;
	data["y"] = component.y;
	data["z"] = component.z;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["positionComponent"] = dir;
    this->write(filename, root);
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionStuff& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["stuffComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list.at(it));
	Json::Value	data;
	Json::Value	vec;
	data["id"] = component.id;
	for (unsigned int tab = 0; tab < component.owned.size(); tab++)
	  vec.append(tab);
	data["owned"] = vec;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["stuffComponent"] = dir;
    this->write(filename, root);
  }
  
  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionHealth& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["healthComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list.at(it));
	Json::Value     data;
	data["id"] = component.id;
	data["live"] = component.live;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["healthComponent"] = dir;
    this->write(filename, root);
  }

  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionAttack& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["attackComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list.at(it));
	Json::Value     data;
	data["id"] = component.id;
	data["isAttack"] = component.isAttack;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["attackComponent"] = dir;
    this->write(filename, root);
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionGraphic& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["graphicComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list.at(it));
	Json::Value     data;
	data["id"] = component.id;
	data["meshName"] = component.meshName;
	data["textureName"] = component.textureName;
	data["animationName"] = component.animationName;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["graphicComponent"] = dir;
    this->write(filename, root);
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionStrength& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["strengthComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["strength"] = component.strength;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["strengthComponent"] = dir;
    this->write(filename, root);
  }

  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionFaction& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["factionComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["type"] = component.type;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["factionComponent"] = dir;
    this->write(filename, root);
  }
  
  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionScript& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["iaScriptComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["script"] = component.script;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["iaScriptComponent"] = dir;
    this->write(filename, root);
  }

  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionRange& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["rangeComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["x"] = component.x;
	data["y"] = component.y;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["rangeComponent"] = dir;
    this->write(filename, root);
  }

  void		SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionDamage& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["damageComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["damageValue"] = component.damageValue;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["damageComponent"] = dir;
    this->write(filename, root);
  }

  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionPlayer& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["playerComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["idPlayer"] = component.idPlayer;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["playerComponent"] = dir;
    this->write(filename, root);
  }

  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::collectionDefense& collection,
					      ecs::entityCollection::entityList const& list) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value               dir = root["Component"]["defenseComponent"];
    dir.clear();
    for (unsigned int it = 0; it < list.size(); it++) {
      try {
	auto component = collection.getComponent(list[it]);
	Json::Value     data;
	data["id"] = component.id;
	data["defenseValue"] = component.defenseValue;
	dir.append(data);
      } catch (indie::CollectionException const&) {}
    }
    root["Component"]["defenseComponent"] = dir;
    this->write(filename, root);
  }

  void          SaveCollection::saveComponent(std::string const& filename,
					      ecs::scoreComponent& component) const {
    Json::Value               root;
    try {
      this->read(filename, root);
    } catch (indie::SaveCollectionException const&) {}
    Json::Value     dir = root["Component"]["scoreComponent"];
    dir["id"] = component.id;
    dir["value"] = static_cast<Json::Value::Int64>(component.value);
    root["Component"]["scoreComponent"] = dir;
    this->write(filename, root);
  }
}
