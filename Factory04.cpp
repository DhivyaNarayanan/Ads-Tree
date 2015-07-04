#include "Factory04.h"
#include"AVLTree.h"
#include"BTree.h"
#include"Point.h"
#include"RTree.h"

//#include"AVLTreeNode.h"

Factory04::Factory04()
{
}

Factory04::~Factory04()
{
}
 
void * Factory04::create(std::string name)
{
  if(name == "IAVLTree"){
    return new AVLTree();
  } else if(name == "IPoint"){
    return new Point();
  } else if(name == "IRTree"){
    return new RTree();
  } else if(name == "IBTree"){
    return new BTree();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory04();  
}

}
