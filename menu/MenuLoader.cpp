#include	"MenuLoader.hh"

namespace	indie {
  void		MenuLoader::loadButtonFromFile(std::string const& filename,
					       std::string const& page) {
    _collection.clear();
    Json::Value         root;
    Json::Reader        reader;
    std::filebuf	fd;

    if (!fd.open(filename, std::ios::in))
      throw MenuLoaderException{ "Can not open file: " + filename };
    std::istream        stream(&fd);
    if (!reader.parse(stream, root, false)) {
      fd.close();
      throw MenuLoaderException{ "Format Error " + reader.getFormattedErrorMessages() };
    }
    Json::Value list = root["Button"][page];
    for (unsigned int index = 0; index < list.size(); index++) {
      Button	button;

      button.ax = list[index].get("ax", 0).asFloat();
      button.ay = list[index].get("ax", 0).asFloat();
      button.bx = list[index].get("bx", 0).asFloat();
      button.by = list[index].get("by", 0).asFloat();
      button.sax = list[index].get("sax", 0).asFloat();
      button.say = list[index].get("sax", 0).asFloat();
      button.sbx = list[index].get("sbx", 0).asFloat();
      button.sby = list[index].get("sby", 0).asFloat();
      button.name = list[index].get("name", "").asString();
      button.text = list[index].get("text", "").asString();
      _collection[button.name] = button;
    }
  }

  const MenuLoader::buttonC	MenuLoader::getButtons() const {
    MenuLoader::buttonC	result{};

    for (auto it : _collection) {
      result.push_back(it.second);
    }
    return result;
  }

  const MenuLoader::Button&	MenuLoader::getButtonByName(std::string const& name) const {
    auto it = _collection.find(name);
    if (it == _collection.end())
      throw MenuLoaderException { "Button not found " + name };
    return (it->second);
  }

  const MenuLoader::Button&	MenuLoader::operator[](std::string const& name) const {
    return (this->getButtonByName(name));
  }
}
