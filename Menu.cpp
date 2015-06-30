#include "Menu.h"
#include <stdlib.h>
#include <string.h>


using namespace std;

char* getSubCharArray(char *charArray,int start,int end)
{
    char *tempChar = new char[end - start];
    int count = end - start;
    for (int i = 0; i < count; ++i)
    {
        tempChar[i] = charArray[start+i];
    }
    return tempChar;
}

// Encoder right
void MenuStructure::incrementSelection()
{
    if (iSelectedItem <= iAvailableItems)
    {
        iSelectedItem++;
    }else{
        iSelectedItem=0;
    }
}

// Encode left
void MenuStructure::decrementSelection()
{
    if (iSelectedItem > 0)
    {
        iSelectedItem--;
    }else{
        iSelectedItem=iAvailableItems;
    }
}

MenuStructure* MenuStructure::getSelectedMenu(MenuStructure* Menu, int iSelected, int iCheck)
{
    if(iSelected==iCheck){
        return Menu;
    }else{
        return getSelectedMenu(Menu->Item.neighborDown, iSelected, iCheck+1);
    }
}

//Encoder press
MenuStructure* MenuStructure::select()
{
    if (iSelectedItem < iChildNodes)    // If Menu was selected
    {
        return getSelectedMenu(this->Item.child, iSelectedItem, 0);
    }else{                              // If Parameter or Coordinate was selected
        return this;
    }
}

void MenuStructure::printStructure(int (*funcPrintSerial)(char*text))
{
    //Reset available items if new menu is printed
    iAvailableItems = 0;
    //Reset selected item if new menu is printed
    iSelectedItem = 0;
    // Print Header
    funcPrintSerial(this->getNodeName());
    funcPrintSerial("--------");
    if (this->Item.child) {
        this->Item.child->printNeighbors(funcPrintSerial);
    }
    iChildNodes = iAvailableItems;
    this->printParamters(funcPrintSerial, 0);
    this->printCoordinates(funcPrintSerial, 0);
    this->printValues(funcPrintSerial, 0);
}

void MenuStructure::printNeighbors(int (*funcPrintSerial)(char*text))
{
    // Increment available items on each draw
    this->Item.parent->iAvailableItems++;
    char temp[16] = " ";
    strcat(temp,this->getNodeName());
    funcPrintSerial(temp);
    if (this->Item.neighborDown) {
        this->Item.neighborDown->printNeighbors(funcPrintSerial);
    }
}

void MenuStructure::printParamters(int (*funcPrintSerial)(char*text), int index)
{
    // Increment available items on each draw
    if (iParameteItems > index) {
        iAvailableItems++;
        char temp[16] = " ";
        strcat(temp,this->Parameters[index].name);
        funcPrintSerial(temp);
        this->printParamters(funcPrintSerial, index+1);
    }
}

void MenuStructure::printCoordinates(int (*funcPrintSerial)(char*text), int index)
{
    // Increment available items on each draw
    if (iCoordinateItems > index) {
        iAvailableItems++;
        char temp[16] = " ";
        strcat(temp,this->Coordinates[index].name);
        funcPrintSerial(temp);
        this->printCoordinates(funcPrintSerial, index+1);
    }
}

void MenuStructure::printValues(int (*funcPrintSerial)(char*text), int index)
{
    if (iValueItemes > index) {
        char temp[16] = " ";
        strcat(temp,this->Values[index].name);
        funcPrintSerial(temp);
        this->printValues(funcPrintSerial, index+1);
    }
}

//***************************************************************
MenuStructure::MenuStructure(char *definition, int length)
{
    int yParameteItems = 0;
    int yCoordinateItems = 0;
    int yValueItemes = 0;
    strncpy(emptyChar,"empty",6);

    // determine array sizes
    for (int i=0; i < length; ++i) {
        if (definition[i]=='<') {
            if (definition[i+1]=='P') {
                iParameteItems++;
            }
            if (definition[i+1]=='C') {
                iCoordinateItems++;
            }
        }
        if (definition[i]=='>') {
            iValueItemes++;
        }
    }

    //Item.name = name;

    if(iParameteItems>0)
    {
        Parameters = new MenuStructure::Parameter[iParameteItems];
    }
    if(iCoordinateItems>0)
    {
        Coordinates = new MenuStructure::Coordinate[iCoordinateItems];
    }
    if(iValueItemes>0)
    {
        Values = new MenuStructure::Value[iValueItemes];
    }
    Item.name = new char[15];


    // Parse Menu string
    for (int i=0; i < length; ++i) {
        //Menu Section
        if (definition[i] == ':') {
            i = i + 3;

            if (definition[i] == '$') {
                int start = i+1;
                i++;
                while (definition[i] != '|' and
                       definition[i] != '/' and
                       definition[i] != '-' and
                       definition[i] != '<' and
                       definition[i] != '>' and
                       definition[i] != '$' and
                       i <= length)
                {
                    i++;
                };
                Item.name = getSubCharArray(definition, start, i);
            }
        }

        if (definition[i] == '<') {
            // Parameter Section
            if (definition[i+1] == 'P') {
                i++;
                while (definition[i] != '<' and
                       definition[i] != '>' and
                       i <= length)
                {
                    i++;
                    //Name Section
                    if (definition[i] == '$') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               i <= length)
                        {
                            i++;
                        };
                        Parameters[yParameteItems].name = getSubCharArray(definition, start, i);
                    }
                    // Value Section
                    if (definition[i] == '|') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               definition[i] != 'x' and
                               definition[i] != 'y' and
                               i <= length)
                        {
                            i++;
                        };
                        Parameters[yParameteItems].value = atof(getSubCharArray(definition, start, i));
                    }
                    // Unit Section
                    if (definition[i] == '/') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               definition[i] != 'x' and
                               definition[i] != 'y' and
                               i <= length)
                        {
                            i++;
                        };
                        Parameters[yParameteItems].unit = getSubCharArray(definition, start, i);
                        i--;
                    }
                    // Step Section
                    if (definition[i] == '-') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               definition[i] != 'x' and
                               definition[i] != 'y' and
                               i <= length)
                        {
                            i++;
                        };
                        Parameters[yParameteItems].step = atof(getSubCharArray(definition, start, i));
                        i--;
                    }
                };
                ++yParameteItems;
                i--;            }
            // Coordinate Section
            if (definition[i+1] == 'C') {
                i++;
                while (definition[i] != '<' and
                       definition[i] != '>' and
                       i <= length)
                {
                    i++;
                    //Name Section
                    if (definition[i] == '$') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               i <= length)
                        {
                            i++;
                        };
                        Coordinates[yCoordinateItems].name = getSubCharArray(definition, start, i);
                    }
                    // X Section
                    if (definition[i] == 'x') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               definition[i] != 'x' and
                               definition[i] != 'y' and
                               i <= length)
                        {
                            i++;
                        };
                        Coordinates[yCoordinateItems].x = atof(getSubCharArray(definition, start, i));
                    }
                    // y Section
                    if (definition[i] == 'y') {
                        int start = i+1;
                        i++;
                        while (definition[i] != '|' and
                               definition[i] != '/' and
                               definition[i] != '-' and
                               definition[i] != '<' and
                               definition[i] != '>' and
                               definition[i] != '$' and
                               definition[i] != 'x' and
                               definition[i] != 'y' and
                               i <= length)
                        {
                            i++;
                        };
                        Coordinates[yCoordinateItems].y = atof(getSubCharArray(definition, start, i));
                        i--;
                    }

                };
                ++yCoordinateItems;
                i--;
            }
        }
        // Values Section
        if (definition[i] == '>') {
            i++;
            while (definition[i] != '<' and
                   definition[i] != '>' and
                   i <= length)
            {
                i++;
                //Name Section
                if (definition[i] == '$') {
                    int start = i+1;
                    i++;
                    while (definition[i] != '|' and
                           definition[i] != '/' and
                           definition[i] != '-' and
                           definition[i] != '<' and
                           definition[i] != '>' and
                           definition[i] != '$' and
                           i <= length)
                    {
                        i++;
                    };
                    Values[yValueItemes].name = getSubCharArray(definition, start, i);
                }
                //Unit Section
                if (definition[i] == '/') {
                    int start = i+1;
                    i++;
                    while (definition[i] != '|' and
                           definition[i] != '/' and
                           definition[i] != '-' and
                           definition[i] != '<' and
                           definition[i] != '>' and
                           definition[i] != '$' and
                           i <= length)
                    {
                        i++;
                    };
                    Values[yValueItemes].unit = getSubCharArray(definition, start, i);
                }
            };
            ++yValueItemes;
            i--;
        }
    }
}

MenuStructure::~MenuStructure()
{
}

char *MenuStructure::getNodeName()
{
    return Item.name;
}

void MenuStructure::setRelations(MenuStructure *parentNode, MenuStructure *childNode, MenuStructure *neighborNodeUp, MenuStructure *neighborNodeDown)
{
    this->setParent(parentNode);
    this->setChild(childNode);
    this->setNeighborUp(neighborNodeUp);
    this->setNeighborDown(neighborNodeDown);
}

void MenuStructure::setParent(MenuStructure *parentNode)
{
    Item.parent = parentNode;
}

void MenuStructure::setChild(MenuStructure *childNode)
{
    Item.child = childNode;
}

void MenuStructure::setNeighborUp(MenuStructure *neighborNodeUp)
{
    Item.neighborUp = neighborNodeUp;
}

void MenuStructure::setNeighborDown(MenuStructure *neighborNodeDown)
{
    Item.neighborDown = neighborNodeDown;
}

//************************************************************
void MenuStructure::setParameterName(char *name, int index)
{
    // Check if Pointer not NULL
    if(Parameters) {
        strncpy(Parameters[index].name, name, StringLength);
    }
}

void MenuStructure::setParameterValue(float value, int index)
{
    // Check if Pointer not NULL
    if(Parameters) {
        Parameters[index].value = value;
    }
}

void MenuStructure::setParameterUnit(char *unit, int index)
{
    // Check if Pointer not NULL
    if(Parameters) {
        Parameters[index].unit = unit;
    }
}

void MenuStructure::setParameterStep(float step, int index)
{
    // Check if Pointer not NULL
    if(Parameters) {
        Parameters[index].step = step;
    }
}

void MenuStructure::setParameterIndex(int index)
{
    // Check if Pointer not NULL
    if(Parameters) {
        Parameters[index].index = index;
    }
}

char* MenuStructure::getParameterName(int index)
{
    if(!Parameters) {
        return emptyChar;
    }
    return Parameters[index].name;
}

float MenuStructure::getParameterValue(int index)
{
    if(!Parameters) {
        return 0;
    }
    return Parameters[index].value;}

char* MenuStructure::getParameterUnit(int index)
{
    if(!Parameters) {
        return emptyChar;
    }
    return Parameters[index].unit;}

float MenuStructure::getParameterStep(int index)
{
    if(!Parameters) {
        return 1;
    }
    return Parameters[index].step;
}

//************************************************************
void MenuStructure::setValueName(char *name, int index)
{
    // Check if Pointer not NULL
    if (Values) {
        strncpy(Values[index].name, name, StringLength);
    }
}

void MenuStructure::setValueValue(float value, int index)
{
    // Check if Pointer not NULL
    if (Values) {
        Values[index].value = value;
    }
}

void MenuStructure::setValueUnit(char *unit, int index)
{
    // Check if Pointer not NULL
    if (Values) {
        Values[index].unit = unit;
    }
}

void MenuStructure::setValueIndex(int index)
{
    // Check if Pointer not NULL
    if (Values) {
        Values[index].index = index;
    }
}

char* MenuStructure::getValueName(int index)
{
    if(!Values) {
        return emptyChar;
    }
    return Values[index].name;
}

float MenuStructure::getValueValue(int index)
{
    if(!Values) {
        return 0;
    }
    return Values[index].value;
}

char* MenuStructure::getValueUnit(int index)
{
    if(!Values[index].unit) {
        return emptyChar;
    }
    return Values[index].unit;
}

//************************************************************
void MenuStructure::setCoordinateName(char *name, int index)
{
    // Check if Pointer not NULL
    if (Coordinates) {
        strncpy(Coordinates[index].name, name, StringLength);

    }
}

void MenuStructure::setCoordinateX(int x, int index)
{
    // Check if Pointer not NULL
    if (Coordinates) {
        Coordinates[index].x = x;
    }
}

void MenuStructure::setCoordinateY(int y, int index)
{
    // Check if Pointer not NULL
    if (Coordinates) {
        Coordinates[index].y = y;
    }
}

char* MenuStructure::getCoordinateName(int index)
{
    if (!Coordinates) {
        return emptyChar;
    }
    return Coordinates[index].name;
}

float MenuStructure::getCoordinateX(int index)
{
    if (!Coordinates) {
        return 0;
    }
    return Coordinates[index].x;
}

float MenuStructure::getCoordinateY(int index)
{
    if (!Coordinates) {
        return 0;
    }
    return Coordinates[index].y;
}
//************************************************************
