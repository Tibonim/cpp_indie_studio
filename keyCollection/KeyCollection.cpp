#include	<algorithm>
#include	"KeyCollection.hh"
#include	"KeyFileProtocole.hh"

namespace	event {
  std::map<int, key>		KeyCollection::_table;
  std::string			KeyCollection::_file;

  key&	KeyCollection::getKey(int const &key)
  {
    auto it = _table.find(key);
    if (it == _table.end())
      throw indie::KeyCollectionException{ "Unknow key " + std::to_string(key) };
    return (it->second);
  }

  bool			KeyCollection::load(std::string const& filename){
    Json::Value		root;
    Json::Reader	reader;
    std::filebuf	fd;

    if (!fd.open(filename, std::ios::in))
      throw indie::KeyCollectionException{ "Can not open file: " + filename };
    std::istream	stream(&fd);
    if (!reader.parse(stream, root, false)) {
      fd.close();
      throw indie::KeyCollectionException{ "Format Error " + reader.getFormattedErrorMessages() };
    }
    _table.clear();
    Json::Value	typearray = root[BASE];
    for (unsigned int index = 0; index < typearray.size(); ++index) {
      Json::Value	type = typearray[index];
      Json::Value	keyarray = type[ACTION];

      for (unsigned int keyindex = 0; keyindex < keyarray.size(); ++keyindex) {
	key	elem;

	elem.type = typearray[index].get(TYPE, "undifined").asString();
	elem.action = keyarray[keyindex].get(NAME, "undifined").asString();
	elem.mode = keyarray[keyindex].get(EDIT, true).asBool();
	elem.value = keyarray[keyindex].get(VALUE, 0).asInt();
	auto it = _table.find(elem.value);
	if (it != _table.end()) {
	  fd.close();
	  throw indie::KeyCollectionException {
	    "Key already exist in " + it ->second.type + " to " + elem.action };
	}
	_table[elem.value] = elem;
      }
    }
    _file = filename;
    fd.close();
    return (true);
  }

  bool			KeyCollection::isLoaded(std::string const& fileName) {
    return _file == fileName;
  }

  std::vector<key>	KeyCollection::getKeysOf(std::string const& groupe) {
    std::vector<key>	keys;

    for (auto it = _table.begin(); it != _table.end(); ++it) {
      if (it->second.type == groupe)
	keys.push_back(it->second);
    }
    return (keys);
  }

  bool	KeyCollection::save(std::string const& filename) {
    Json::Value		typearray;
    for (auto it = _table.begin(); it != _table.end(); ++it) {
      Json::Value	elem;
      Json::Value	type;

      if (!typearray.empty())
	for (unsigned int find = 0; find < typearray[BASE].size(); ++find)
	  if (typearray[BASE][find].get(TYPE, "").asString() == it->second.type) {
	    type = typearray[BASE][find];
	    typearray[BASE].removeIndex(find, &typearray[BASE][find]);
	  }
      elem[VALUE] = it->first;
      elem[NAME] = it->second.action;
      elem[EDIT] = it->second.mode;
      type[TYPE] = it->second.type;
      type[ACTION].append(elem);
      typearray[BASE].append(type);
    }
    std::ofstream	fd;
    fd.open(filename);
    if (!fd)
      throw indie::KeyCollectionException{ "Can not open file: " + filename };
    Json::StyledWriter styledWriter;
    fd << styledWriter.write(typearray);
    fd.close();
    return (true);
  }

  void	KeyCollection::setKey(int const oldkey, int const newkey) {
    auto	it = _table.find(oldkey);
    key		elem;
    if (it == _table.end())
      throw indie::KeyCollectionException{ "Unknown key" };
    elem = it->second;
    auto test = _table.find(newkey);
    if (test != _table.end())
      throw indie::KeyCollectionException{ "Key already exist" };
    elem.value = newkey;
    _table.erase(it);
    elem.value = newkey;
    _table[newkey] = elem;
  }
}
