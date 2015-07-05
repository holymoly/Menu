#include <menu.h>
//
//  Menu.ino
//  Menu
//
//  Created by Maurice Streubel on 17.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//
void printSerial(char* text){
  Serial.print(text);       // prints a label
}
//*************************************************
//Create Menuelemtents
char MenuDefinitionMain[] = ":M$Main>n$Shots>S$Last Shot/s>S$Last Exp/s>S$Next Shot/se>S$Next Exp/s";
  char MenuDefinitionExposure[] =":M$Exposure";
    char MenuDefinitionExposureGraph[] =":M$Graph";
    char MenuDefinitionExposureDuration[] =":M$Duration<P$Start Time/s-1|0<PS$End Time/s-1|100";
    char MenuDefinitionExposureRamp[] =":M$Ramp<P$Start at/s-2|30<P$End at/s-3|60<C(0)0$C1<C(0.5)0$C2<C(0.5)0.5$C3<C(0.5)1$C4<C(1)1$C5";
  char MenuDefinitionTimelaps[] =":M$Timelaps";
    char MenuDefinitionTimelapsGraph[] =":M$Graph";
    char MenuDefinitionTimelapsDuration[] =":M$Duration<P$Start Period/s-1|0<P$End Period/s-1|3600";
    char MenuDefinitionTimelapsRamp[] =":M$Ramp<P$Start at/s-1|900<P$End at/s-1|1800<C(0)0$C1<C(0.5)0$C2<C(0.5)0.5$C3<C(0.5)1$C4<C(1)1$C5";
//Init Menus
Menu MainNode = *new Menu(MenuDefinitionMain,sizeof(MenuDefinitionMain));
  Menu ExposureNode = *new Menu(MenuDefinitionExposure,sizeof(MenuDefinitionExposure));
    Menu ExposureGraphNode = *new Menu(MenuDefinitionExposureGraph,sizeof(MenuDefinitionExposureGraph));
    Menu ExposureDurationNode = *new Menu(MenuDefinitionExposureDuration,sizeof(MenuDefinitionExposureDuration));
    Menu ExposureRampNode = *new Menu(MenuDefinitionExposureRamp,sizeof(MenuDefinitionExposureRamp));
  Menu TimelapsNode = *new Menu(MenuDefinitionTimelaps,sizeof(MenuDefinitionTimelaps));
    Menu TimelapsGraphNode = *new Menu(MenuDefinitionTimelapsGraph,sizeof(MenuDefinitionTimelapsGraph));
    Menu TimelapsDurationNode = *new Menu(MenuDefinitionTimelapsDuration,sizeof(MenuDefinitionTimelapsDuration));
    Menu TimelapsRampNode = *new Menu(MenuDefinitionTimelapsRamp,sizeof(MenuDefinitionTimelapsRamp));

//*************************************************
//*************************************************
// Create function used by a function pointer
//*************************************************

void setup(){
  Serial.begin(9600);

  MainNode.setRelation(NULL, &ExposureNode, NULL, NULL);
    ExposureNode.setRelation(&MainNode, &ExposureGraphNode, &TimelapsNode, NULL);
      ExposureGraphNode.setRelation(&ExposureNode, NULL, &ExposureDurationNode, NULL);
      ExposureDurationNode.setRelation(&ExposureNode, NULL, &ExposureRampNode, &ExposureGraphNode);
      ExposureRampNode.setRelation(&ExposureNode, NULL, NULL, &ExposureDurationNode);
    TimelapsNode.setRelation(&MainNode, &TimelapsGraphNode, NULL, &ExposureNode);
      TimelapsGraphNode.setRelation(&TimelapsNode, NULL, &TimelapsDurationNode, NULL);
      TimelapsDurationNode.setRelation(&TimelapsNode, NULL, &TimelapsRampNode, &TimelapsGraphNode);
      TimelapsRampNode.setRelation(&TimelapsNode, NULL, NULL, &TimelapsDurationNode);

  MainNode.print = printSerial;
  ExposureNode.print = printSerial;
  ExposureGraphNode.print = printSerial;
  ExposureDurationNode.print = printSerial;
  ExposureRampNode.print = printSerial;
  TimelapsNode.print = printSerial;
  TimelapsGraphNode.print = printSerial;
  TimelapsRampNode.print = printSerial;
  TimelapsDurationNode.print = printSerial;

  MainNode.printMenu();
  //ExposureNode.printMenu();
  //ExposureGraphNode.printMenu();
  //ExposureDurationNode.printMenu();
  //ExposureRampNode.printMenu();
  //TimelapsNode.printMenu();
  //TimelapsGraphNode.printMenu();
  //TimelapsRampNode.printMenu();
  //TimelapsDurationNode.printMenu();
}

void loop() {
  // put your main code here, to run repeatedly:

}
