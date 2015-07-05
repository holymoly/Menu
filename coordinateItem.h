//
//  coordinateItem.h
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#ifndef __Menu__coordinateItem__
#define __Menu__coordinateItem__

#include <stdio.h>
#include "menu.h"
#include "item.h"

// Forward declaration
class Menu;

class CoordinateItem: public Item
{
  Menu *menu;             // Pointer to the menu.

  CoordinateItem *next;   // Pointer to next item
  CoordinateItem *last;   // Pointer to last item

  float x;
  float y;

  char *empty;            // emtpy char
public:
  CoordinateItem();       // Constructor
  ~CoordinateItem();      // Deconstructor

  void setMenu(Menu* menu);
  Menu* getMenu();

  void setNext(CoordinateItem *next);
  CoordinateItem* getNext();

  void setLast(CoordinateItem *next);
  CoordinateItem* getLast();

  void setX(float x);
  float getX();

  void setY(float y);
  float getY();
};

#endif /* defined(__Menu__coordinateItem__) */
