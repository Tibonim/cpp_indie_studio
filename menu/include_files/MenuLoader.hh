#pragma once

#include	<string>
#include	<map>
#include        <cstdio>
#include        <iostream>
#include        <fstream>
#include        "json/json.h"
#include	"MenuLoaderException.hh"


namespace	indie {
  class		MenuLoader {
  public:
    struct	Button
    {
      float	ax;
      float	ay;
      float	bx;
      float	by;
      float       sax;
      float       say;
      float       sbx;
      float       sby;
      std::string name;
      std::string text;
    };
    typedef std::vector<Button>	buttonC;

    MenuLoader() {};
    ~MenuLoader() {};
    void	loadButtonFromFile(std::string const&, std::string const&);
    const Button&	getButtonByName(std::string const&) const;
    const Button&	operator[](std::string const&) const;
    const buttonC	getButtons() const;
  private:
    std::map<std::string, Button>	_collection;
  };
};
