//
//  valueItem.cpp
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#include "valueItem.h"
#include <Arduino.h>

// Constructor
ValueItem::ValueItem()
{
  empty = new char{'\0'};
}

// Deconstructor
ValueItem::~ValueItem()
{
}

void ValueItem::setMenu(Menu *menu)
{
    this->menu = menu;
}

Menu *ValueItem::getMenu()
{
    return this->menu;
}

void ValueItem::setNext(ValueItem* nextOne)
{
  next = nextOne;
}

ValueItem* ValueItem::getNext()
{
  return next;
}

void ValueItem::setLast(ValueItem* lastOne)
{
  last = lastOne;
}

ValueItem* ValueItem::getLast()
{
  return last;
}

void ValueItem::setValue(float value)
{
    this->value = value;
}

float ValueItem::getValue()
{
    return value;
}

void ValueItem::setUnit(char* unit)
{
    this->unit = unit;
}

char *ValueItem::getUnit()
{
  if (this->unit) {
    return unit;
  }
  return empty;
}
