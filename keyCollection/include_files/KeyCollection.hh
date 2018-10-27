#pragma	once

#include	<vector>
#include	<string>
#include	<map>
#include        <cstdio>
#include        <iostream>
#include        <fstream>
#include        "json/json.h"
#include	"SingletonPattern.hh"
#include	"KeyCollectionException.hh"

namespace	event
{
  struct	key
  {
    std::string	type;
    std::string	action;
    bool	mode;
    int		value;
  };

  class		KeyCollection : private SingletonPattern
  {
  public:
    static key&			getKey(int const&);
    static bool			load(std::string const&);
    static bool			save(std::string const&);
    static void			setKey(int const, int const);
    static std::vector<key>	getKeysOf(std::string const&);
    static bool			isLoaded(std::string const&);
  private:
    static std::map<int, key>        _table;
    static std::string		_file;
  };
};
