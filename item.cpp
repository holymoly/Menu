//
//  Item.cpp
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#include "Item.h"
#include <Arduino.h>

// Constructor
Item::Item()
{
  empty = new char{'\0'};
}

// Deconstructor
Item::~Item()
{
}

void Item::setName(char *name)
{
    this->name = name;
}

char* Item::getName()
{
  if (this->name) {
    return this->name;
  }
  return empty;
}
