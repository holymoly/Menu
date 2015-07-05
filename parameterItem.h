//
//  parameterItem.h
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#ifndef __Menu__parameterItem__
#define __Menu__parameterItem__

#include <stdio.h>
#include "menu.h"
#include "item.h"

// Forward declaration
class Menu;

class ParameterItem:public Item
{
  Menu *menu;             // Pointer to the menu.

  ParameterItem *next;    // Pointer to next item
  ParameterItem *last;    // Pointer to last item

  float value;
  char *unit;
  float step;

  char *empty;            // emtpy char
public:
  ParameterItem();        // Constructor
  ~ParameterItem();       // Deconstructor

  void setMenu(Menu *menu);
  Menu* getMenu();

  void setNext(ParameterItem *next);
  ParameterItem* getNext();

  void setLast(ParameterItem *next);
  ParameterItem* getLast();


  void setValue(float value);
  float getValue();

  void setUnit(char *unit);
  char* getUnit();

  void setStep(float step);
  float getStep();
};

#endif /* defined(__Menu__parameterItem__) */
