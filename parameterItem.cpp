//
//  parameterItem.cpp
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#include "parameterItem.h"
#include <Arduino.h>

// Constructor
ParameterItem::ParameterItem()
{
  empty = new char{'\0'};
}

// Deconstructor
ParameterItem::~ParameterItem()
{
}


void ParameterItem::setMenu(Menu *menu)
{
    this->menu = menu;
}

Menu *ParameterItem::getMenu()
{
    return this->menu;
}

void ParameterItem::setNext(ParameterItem* nextOne)
{
  next = nextOne;
}

ParameterItem* ParameterItem::getNext()
{
  return next;
}

void ParameterItem::setLast(ParameterItem* lastOne)
{
  last = lastOne;
}

ParameterItem* ParameterItem::getLast()
{
  return last;
}

void ParameterItem::setValue(float value)
{
    this->value = value;
}

float ParameterItem::getValue()
{
    return value;
}

void ParameterItem::setUnit(char *unit)
{
    this->unit = unit;
}

char *ParameterItem::getUnit()
{
  if (this->unit) {
    return this->unit;
  }
  return empty;
}

void ParameterItem::setStep(float step)
{
    this->step = step;
}

float ParameterItem::getStep()
{
    return this->step;
}
