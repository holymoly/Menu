//
//  Item.h
//  Menu
//
//  Created by Maurice Streubel on 30.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

#ifndef __Menu__Item__
#define __Menu__Item__

#include <stdio.h>

class Item {
  char *name;     // The name for this this node.
  Item *next;
  Item *last;
  
  char *empty;    // emtpy char
public:
  Item();
  ~Item();
  
  void setName(char *Name);
  char *getName();
};

#endif /* defined(__Menu__Item__) */
