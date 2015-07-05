//
//  valueItem.h
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#ifndef __Menu__valueItem__
#define __Menu__valueItem__

#include <stdio.h>
#include "menu.h"
#include "item.h"

// Forward declaration
class Menu;

class ValueItem: public Item
{
  Menu *menu;         // Pointer to the menu.

  ValueItem *next;    // Pointer to next item
  ValueItem *last;    // Pointer to last item

  float value;
  char *unit;

  char *empty;        // emtpy char
public:
  ValueItem();        // Constructor
  ~ValueItem();       // Deconstructor

  void setMenu(Menu* menu);
  Menu* getMenu();

  void setNext(ValueItem *next);
  ValueItem* getNext();

  void setLast(ValueItem *last);
  ValueItem* getLast();


  void setValue(float value);
  float getValue();

  void setUnit(char* unit);
  char* getUnit();
};

#endif /* defined(__Menu__valueItem__) */
