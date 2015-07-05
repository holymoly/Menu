//
//  Menu.cpp
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#include "menu.h"
#include <Arduino.h>

// Return Sub string till end character
char* getSubCharArray(char *charArray,int start,int maxLength)
{
  int i = start;

  while (charArray[i] != '|' and
         charArray[i] != '/' and
         charArray[i] != '-' and
         charArray[i] != '<' and
         charArray[i] != '>' and
         charArray[i] != '$' and
         charArray[i] != '(' and
         charArray[i] != ')' and
         i <= maxLength)
  {
    i++;
  };
  int count = i - start;
  char *tempChar = new char[count];

  for (int i = 0; i < count; ++i)
  {
    tempChar[i] = charArray[start+i];
  }
  tempChar[i] = '\0';
  return tempChar;
}

void Menu::printSubMenu()
{
  char tab[] = " ";

  this->print(tab);
  this->printLine(curentMenu->getName());
  this->print('\0');
}

void Menu::printParameter()
{
  char tab[] = "  \0";
  char space[] = " \0";
  char temp[15];

  this->print(tab);
  this->print(curentParameter->getName());
  this->print(space);
  dtostrf(curentParameter->getValue(), 1 ,4 , temp);
  this->print(temp);
  this->printLine(curentParameter->getUnit());

}

void Menu::printCoordinate()
{
  char tab[] = "  \0";
  char space[] = " \0";
  char temp[15];

  this->print(tab);
  this->print(curentCoordinate->getName());
  this->print(space);
  sprintf(temp,"(");
  this->print(temp);
  dtostrf(curentCoordinate->getX(), 1 ,1 , temp);
  this->print(temp);
  sprintf(temp,";");
  this->print(temp);
  dtostrf(curentCoordinate->getY(), 1 ,1 , temp);
  this->print(temp);
  sprintf(temp,")");
  this->printLine(temp);
}

void Menu::printValue()
{
  char tab[] = "  \0";
  char space[] = " \0";
  char temp[15];

  this->print(tab);
  this->print(curentValue->getName());
  this->print(space);
  dtostrf(curentParameter->getValue(), 1 ,4 , temp);
  this->print(temp);
  this->printLine(curentValue->getUnit());
}

// Constructor
Menu::Menu(char* definition, int length)
{
  empty = new char{'\0'};
  curentParameter = NULL;
  curentCoordinate = NULL;
  curentValue = NULL;

  for (int i=0; i < length; ++i) {
    if (definition[i]==':') {
      i++;
      if (definition[i]=='M') {
        // Main
        while (definition[i] != '<' and
               definition[i] != '>' and
               i <= length)
        {
          ++i;
          switch (definition[i]) {
            case '$': // Start of name part
              this->setName(getSubCharArray(definition, i+1, length));break;
            default:
              break;
          }
        }
        --i;
      }
    }
    if (definition[i]=='<') {
      ++i;
      if (definition[i]=='P') {
        // Parameter
        if (!curentParameter) { // first new Parameter
          curentParameter = new ParameterItem;
          curentParameter->setLast(NULL);
          curentParameter->setNext(NULL);
          curentParameter->setUnit(NULL);
        }else{ //if more then one Parameter
          ParameterItem *temp = new ParameterItem;
          temp->setLast(NULL);
          temp->setNext(NULL);
          temp->setUnit(NULL);

          curentParameter->setNext(temp);
          temp->setLast(curentParameter);
          curentParameter = temp;
        }

        while (definition[i] != '<' and
               definition[i] != '>' and
               i <= length)
        {
          ++i;
          switch (definition[i]) {
            case '$': // Start of name part
              curentParameter->setName(getSubCharArray(definition, i+1, length));break;
            case '|': // Start of value part
              curentParameter->setValue(atof(getSubCharArray(definition, i+1, length)));break;
            case '/': // Start of unit part
              curentParameter->setUnit(getSubCharArray(definition, i+1, length));break;
            case '-': // Start of step part
              curentParameter->setStep(atof(getSubCharArray(definition, i+1, length)));break;
            default:
              break;
          }
        }
        --i;
      }
      if (definition[i]=='C') {
        //Coordinate
        if (!curentCoordinate) { // first new Coordinate
          curentCoordinate = new CoordinateItem;
          curentCoordinate->setLast(NULL);
          curentCoordinate->setNext(NULL);
        }else{ //if more then one Coordinate
          CoordinateItem *temp = new CoordinateItem;
          temp->setLast(NULL);
          temp->setNext(NULL);

          curentCoordinate->setNext(temp);
          temp->setLast(curentCoordinate);
          curentCoordinate = temp;
        }

        while (definition[i] != '<' and
               definition[i] != '>' and
               i <= length)
        {
          ++i;
          switch (definition[i]) {
            case '$': // Start of name part
              curentCoordinate->setName(getSubCharArray(definition, i+1, length));break;
            case '(': // Start of value part
              curentCoordinate->setX(atof(getSubCharArray(definition, i+1, length)));break;
            case ')': // Start of unit part
              curentCoordinate->setY(atof(getSubCharArray(definition, i+1, length)));break;
            default:
              break;
          }
        }
        --i;
      }
    }
    if (definition[i]=='>') {
      //Values
      if (!curentValue) { // first new Value
        curentValue = new ValueItem;
        curentValue->setLast(NULL);
        curentValue->setNext(NULL);
        curentValue->setUnit(NULL);
      }else{ //if more then one Value
        ValueItem *temp = new ValueItem;
        temp->setLast(NULL);
        temp->setNext(NULL);
        temp->setUnit(NULL);

        curentValue->setNext(temp);
        temp->setLast(curentValue);
        curentValue = temp;
      }
      ++i;
      while (definition[i] != '<' and
             definition[i] != '>' and
             i <= length)
      {
        ++i;
        switch (definition[i]) {
          case '$': // Start of name part
            curentValue->setName(getSubCharArray(definition, i+1, length));break;
          case '|': // Start of value part
            curentValue->setValue(atof(getSubCharArray(definition, i+1, length)));break;
          case '/': // Start of unit part
            curentValue->setUnit(getSubCharArray(definition, i+1, length));break;
          default:
            break;
        }
      }
      --i;
    }
  }
}

// Deconstructor
Menu::~Menu()
{
}

void Menu::setRelation(Menu *parent, Menu *child, Menu *next, Menu *last)
{
  this->parent = parent;
  this->child  = child;
  this->next   = next;
  this->last   = last;
}

void Menu::setParent(Menu *parent)
{
  this->parent = parent;
}

Menu *Menu::getParent()
{
  return this->parent;
}

void Menu::setChild(Menu *child)
{
  this->child = child;
}

Menu *Menu::getChild()
{
  return this->child;
}

void Menu::setNext(Menu *next)
{
  this->next = next;
}

Menu *Menu::getNext()
{
  return this->next;
}

void Menu::setLast(Menu *last)
{
  this->last = last;
}

Menu *Menu::getLast()
{
  return this->last;
}

void Menu::setCurentParameter(ParameterItem *child)
{
  this->curentParameter = child;
}

ParameterItem *Menu::getCurentParameter()
{
  return this->curentParameter;
}

void Menu::curentParameterLast()
{
    curentParameter = curentParameter->getLast();
}

void Menu::curentParameterNext()
{
    curentParameter = curentParameter->getNext();
}

void Menu::setCurentCoordinate(CoordinateItem *child)
{
  this->curentCoordinate = child;
}

CoordinateItem *Menu::getCurentCoordinate()
{
  return this->curentCoordinate;
}

void Menu::curentCoordinateLast()
{
  curentCoordinate = curentCoordinate->getLast();
}

void Menu::curentCoordinateNext()
{
  curentCoordinate = curentCoordinate->getNext();
}

void Menu::setCurentValue(ValueItem *child)
{
  this->curentValue = child;
}

ValueItem *Menu::getCurentValue()
{
  return this->curentValue;
}

void Menu::curentValueLast()
{
  curentValue = curentValue->getLast();
}

void Menu::curentValueNext()
{
  curentValue = curentValue->getNext();
}

void Menu::printLine(char* text)
{
  char crcn[] = "\r\n\0";

  this->print(text);
  this->print(crcn);
}

void Menu::printMenu()
{
  char line[] = "---------";
  this->printLine(this->getName());
  this->printLine(line);

  // Print Submenus
  if (this->child) {
    curentMenu = this->getChild();

    this->printSubMenu();
    while (curentMenu->getNext()) {
      curentMenu = curentMenu->getNext();
      this->printSubMenu();
    }
  }

  // Print Parameters
  if (this->curentParameter) {
    while (this->curentParameter->getLast()) {
      curentParameter = curentParameter->getLast();
    }
    this->printParameter();

    while (curentParameter->getNext()) {
      curentParameter = curentParameter->getNext();
      this->printParameter();
    }
  }

  if (this->curentCoordinate) {

    while (this->curentCoordinate->getLast()) {
      curentCoordinate = curentCoordinate->getLast();
    }
    this->printCoordinate();

    while (curentCoordinate->getNext()) {
      curentCoordinate = curentCoordinate->getNext();
      this->printCoordinate();
    }
  }

  if (this->curentValue) {

    while (this->curentValue->getLast()) {
      curentValue = curentValue->getLast();
    }

    this->printValue();

    while (curentValue->getNext()) {
      curentValue = curentValue->getNext();
      this->printValue();
    }
  }
}
