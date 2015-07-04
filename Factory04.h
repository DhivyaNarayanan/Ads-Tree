#pragma once

#include "ObjectFactory.h"

class Factory04 : public ObjectFactory {
public:
  Factory04();
  virtual ~Factory04();
  virtual void * create(std::string interface_name);
};
