#include <stdexcept>
#include <iostream>
#include <fstream>
#include <iterator>
#include "CollectionException.hh"
#include "loader.hh"

namespace	indie {
  std::string				ConfigurationLoader::_fileCfg{};
  std::vector<std::string>		ConfigurationLoader::_folders;

  void		ConfigurationLoader::loadCfgConfiguration(std::string const& fileName) {
    std::ifstream	ifs{ fileName };
    if (!ifs)
      throw CollectionException{ "Error: " + fileName + " not found" };
    ifs >> std::noskipws;
    _fileCfg = std::string{ fileName };
    std::string		file{ std::istream_iterator<char>(ifs),
	std::istream_iterator<char>() };
    feedPath(file);
  }

  std::string	ConfigurationLoader::getPath(std::string const& line,
					     std::size_t const lineNbr) {
    auto find = line.find('=');
    if (find == std::string::npos)
      throw CollectionException{ "Error, missing \'=\' on line: " +
	  std::to_string(lineNbr) };
    return std::string{ line.substr(find + 1, line.size()) };
  }

  void		ConfigurationLoader::feedPath(std::string const& file) {
    auto	it = file.begin();
    auto	itPrev = file.begin();
    std::size_t	lineNbr{ 1 };

    while (it != file.end()) {
      if ((*it) == '\n' || (*it) == '#') {
	std::string	stringToTreat{ itPrev, it };
	std::string	path = getPath(stringToTreat, lineNbr);
	_folders.push_back(path);
	++lineNbr;
	itPrev = it + 1;
      }
      ++it;
    }
  }

  std::string	ConfigurationLoader::isAgoodPath(std::string const& path,
						 std::string const& file) {
    std::string		name{ path };
    if (name[name.size()] != '/')
      name += "/";
    name += file;
    std::ifstream	ifs{ name };
    if (!ifs)
      return "";
    return name;
  }

  bool		ConfigurationLoader::isFile(std::string const& fileName) {
    try {
      getFile(fileName);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  std::string	ConfigurationLoader::getFile(std::string const& fileName) {
    std::string	result{};

    for (auto it : _folders) {
      std::string	file = isAgoodPath(it, fileName);
      if (file != "")
	result = file;
    }
    if (result == "")
      throw CollectionException{ "Error: Cannot find file named " +
	  std::string(fileName) };
    return result;
  }
}
