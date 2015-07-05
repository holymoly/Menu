//
//  coordinateItem.cpp
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#include "coordinateItem.h"
#include <Arduino.h>

// Constructor
CoordinateItem::CoordinateItem()
{
  empty = new char{'\0'};
}

// Deconstructor
CoordinateItem::~CoordinateItem()
{
}

void CoordinateItem::setMenu(Menu *menu)
{
    this->menu = menu;
}

Menu* CoordinateItem::getMenu()
{
    return this->menu;
}

void CoordinateItem::setNext(CoordinateItem* nextOne)
{
  next = nextOne;
}

CoordinateItem* CoordinateItem::getNext()
{
  return next;
}

void CoordinateItem::setLast(CoordinateItem* lastOne)
{
  last = lastOne;
}

CoordinateItem* CoordinateItem::getLast()
{
  return last;
}

void CoordinateItem::setX(float x)
{
    this->x = x;
}

float CoordinateItem::getX()
{
    return this->x;
}

void CoordinateItem::setY(float y)
{
    this->y = y;
}

float CoordinateItem::getY()
{
    return this->y;
}
