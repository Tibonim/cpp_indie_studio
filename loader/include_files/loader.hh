#pragma once

#include <map>
#include <string>
#include <vector>
#include "SingletonPattern.hh"

namespace	indie {
  class		ConfigurationLoader : private event::SingletonPattern {
  public:
    static void	loadCfgConfiguration(std::string const& fileName);
    static std::string	getFile(std::string const& name);
    static bool		isFile(std::string const& name);
  private:
    static void		feedPath(std::string const& file);
    static std::string	getPath(std::string const& line, std::size_t lineNbr);
    static std::string	isAgoodPath(std::string const& path, std::string const& file);
  private:
    static std::string				_fileCfg;
    static std::vector<std::string>		_folders;
  };
}
