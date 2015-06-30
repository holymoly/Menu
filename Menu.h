#ifndef Menu_h
#define Menu_h
#include "Arduino.h"


// Length definitions
#define StringLength 15
#define UnitLength 4

//***************************************************************

//Holds the arrays of Items needed for the menu
class MenuStructure
{

public:
    struct MenuNode {
        char *name;  // The name for this this node.
        MenuStructure *parent;   // Pointer to the parent menu.
        MenuStructure *neighborUp;  // Pointer to the neighbor menu.
        MenuStructure *neighborDown;  // Pointer to the neighbor menu.
        MenuStructure *child;  // Pointer to the child menu.
    };

    struct Parameter {
        char *name;  // The name for this this node.
        MenuStructure *parent;   // Pointer to the parent menu.

        float value;
        char *unit;
        float step;
        int index;
    };

    struct Value {
        char *name;  // The name for this this node.
        MenuStructure *parent;   // Pointer to the parent menu.

        float value;
        char *unit;
        int index;
    };

    struct Coordinate {
        char *name;  // The name for this this node.
        MenuStructure *parent;   // Pointer to the parent menu.

        float x;
        float y;
        int index;
    };

    // Max count of available items
    int iAvailableItems=0;

    // Initialize Menu and have Interrupt handled by Menu class
    MenuStructure(char *definiiton, int length);
    ~MenuStructure();

    char* getNodeName();

    void setRelations(MenuStructure *parentNode, MenuStructure *childNode, MenuStructure *neighborNodeUp, MenuStructure *neighborNodeDown);
    void setParent(MenuStructure *parentNode);
    void setChild(MenuStructure *childNode);
    void setNeighborUp(MenuStructure *neighborNodeUp);
    void setNeighborDown(MenuStructure *neighborNodeDown);

    //Print Structures
    void printStructure(int (*funcPrintSerial)(char*text));
    void printNeighbors(int (*funcPrintSerial)(char*text));
    void printParamters(int (*funcPrintSerial)(char*text), int index);
    void printCoordinates(int (*funcPrintSerial)(char*text), int index);
    void printValues(int (*funcPrintSerial)(char*text), int index);

    // Setter for Parameter
    void setParameterName(char *name, int index);
    void setParameterValue(float value, int index);
    void setParameterUnit(char *unit, int index);
    void setParameterStep(float step, int index);
    void setParameterIndex(int index);
    // Getter Paremeter
    char* getParameterName(int index);
    float getParameterValue(int index);
    char* getParameterUnit(int index);
    float getParameterStep(int index);

    // Setter for Value
    void setValueName(char *name, int index);
    void setValueValue(float value, int index);
    void setValueUnit(char *unit, int index);
    void setValueIndex(int index);
    // Getter for Value
    char* getValueName(int index);
    float getValueValue(int index);
    char* getValueUnit(int index);

    // Setter for Coordinate
    void setCoordinateName(char *name, int index);
    void setCoordinateX(int x, int index);
    void setCoordinateY(int y, int index);
    // Getter for Coordinate
    char* getCoordinateName(int index);
    float getCoordinateX(int index);
    float getCoordinateY(int index);

    // Handle Selections
    void incrementSelection();
    void decrementSelection();
    MenuStructure* select();
    MenuStructure* getSelectedMenu(MenuStructure* Menu, int iSelected, int iCheck);

private:
    MenuNode    Item;
    // Pointer to arrays of items
    Parameter   *Parameters;
    Value       *Values;
    Coordinate  *Coordinates;

    char emptyChar[6];
    // Max count of items
    int iChildNodes = 0;
    int iParameteItems = 0;
    int iCoordinateItems = 0;
    int iValueItemes = 0;


    int iSelectedItem=0;
};

#endif
