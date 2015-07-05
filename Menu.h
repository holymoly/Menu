//
//  menuNode.h
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#ifndef __Menu__menuNode__
#define __Menu__menuNode__

#include <stdio.h>
#include "parameterItem.h"
#include "coordinateItem.h"
#include "valueItem.h"
#include "item.h"

// Forward declaration
class ParameterItem;
class CoordinateItem;
class ValueItem;

class Menu: public Item
{
  Menu *parent;                       // Pointer to the parent menu.
  Menu *child;                        // Pointer to the child menu.

  Menu *next;                         // Pointer to next item
  Menu *last;                         // Pointer to last item

  Menu *curentMenu;                   // Pointer to curent selected Menu
  ParameterItem *curentParameter;         // Pointer to curent selected Parameter
  CoordinateItem *curentCoordinate;       // Pointer to curent selected Coordinate
  ValueItem *curentValue;                 // Pointer to curent selected Value

  const char *empty;                      // emtpy char
  void printLine(char *text);
  void printSubMenu();
  void printParameter();
  void printCoordinate();
  void printValue();

public:
  Menu(char* definition,int length); // Constructor
  ~Menu();                            // Deconstructor

  void setRelation(Menu *parent, Menu *child, Menu *next, Menu *last);

  void setParent(Menu *parent);
  Menu* getParent();

  void setChild(Menu *child);
  Menu* getChild();

  void setNext(Menu *next);
  Menu* getNext();

  void setLast(Menu *last);
  Menu* getLast();

  void setCurentParameter(ParameterItem *child);
  ParameterItem *getCurentParameter();
  void curentParameterLast();
  void curentParameterNext();

  void setCurentCoordinate(CoordinateItem *child);
  CoordinateItem *getCurentCoordinate();
  void curentCoordinateLast();
  void curentCoordinateNext();

  void setCurentValue(ValueItem *child);
  ValueItem *getCurentValue();
  void curentValueLast();
  void curentValueNext();

  void (*print)(char *text);                // Function pointer to printing function
  void printMenu();
};

#endif /* defined(__Menu__menuNode__) */
