#include <Menu.h>
//
//  Menu.ino
//  Menu
//
//  Created by Maurice Streubel on 17.06.15.
//  Copyright (c) 2015 Maurice Streubel. All rights reserved.
//

//*************************************************
//Create Menuelemtents
char MenuDefinitionMain[] = ":1M$Main>n$Shots>S$Last Shot/s>S$Last Exp/s>S$Next Shot/s>S$Next Exp/s";
        char MenuDefinitionExposure[] =":2M$Exposure";
            char MenuDefinitionExposureGraph[] =":3G$Graph";
            char MenuDefinitionExposureDuration[] =":3M$Duration<P$Start Time/s-1|0<PS$End Time/s-1|100";
            char MenuDefinitionExposureRamp[] =":3M$Ramp<P$Start at/s-2|30<P$End at/s-3|60<Cx0y0$C1<Cx0.5y0$C2<Cx0.5y0.5$C3<Cx0.5y1$C4<Cx1y1$C5";
        char MenuDefinitionTimelaps[] =":2M$Timelaps";
            char MenuDefinitionTimelapsGraph[] =":3G$Graph";
            char MenuDefinitionTimelapsDuration[] =":3M$Duration<P$Start Period/s-1|0<P$End Period/s-1|3600";
            char MenuDefinitionTimelapsRamp[] =":3M$Ramp<P$Start at/s-1|900<P$End at/s-1|1800<Cx0y0$C1<Cx0.5y0$C2<Cx0.5y0.5$C3<Cx0.5y1$C4<Cx1y1$C5";

    //Init Menus
    MenuStructure menuRoot = *new MenuStructure(MenuDefinitionMain, sizeof(MenuDefinitionMain));

        MenuStructure exposureSub = *new MenuStructure(MenuDefinitionExposure, sizeof(MenuDefinitionExposure));

            MenuStructure exposureGraphSub = *new MenuStructure(MenuDefinitionExposureGraph, sizeof(MenuDefinitionExposureGraph));

            MenuStructure exposureDurationSub = *new MenuStructure(MenuDefinitionExposureDuration, sizeof(MenuDefinitionExposureDuration));

            MenuStructure exposureRampSub = *new MenuStructure(MenuDefinitionExposureRamp, sizeof(MenuDefinitionExposureRamp));

        MenuStructure timelapsSub = *new MenuStructure(MenuDefinitionTimelaps, sizeof(MenuDefinitionTimelaps));

            MenuStructure timelapsGraphSub = *new MenuStructure(MenuDefinitionTimelapsGraph, sizeof(MenuDefinitionTimelapsGraph));

            MenuStructure timelapsDurationSub = *new MenuStructure(MenuDefinitionTimelapsDuration, sizeof(MenuDefinitionTimelapsDuration));

            MenuStructure timelapsRampSub = *new MenuStructure(MenuDefinitionTimelapsRamp, sizeof(MenuDefinitionTimelapsRamp));


//Prepare Current Item ,its the item to work with
MenuStructure *curentItem = &menuRoot;
//*************************************************
//*************************************************
// Create function used by a function pointer
int printSerial(char* text){
     Serial.println(text);       // prints a label
}

int (*funcPrintSerial)(char*text);
//*************************************************

void setup(){
    //Assign function pointer to function
    funcPrintSerial = printSerial;
    Serial.begin(9600);

    //Set Relations
    menuRoot.setRelations(NULL, &exposureSub, NULL, NULL);
        exposureSub.setRelations(&menuRoot, &exposureGraphSub, NULL, &timelapsSub);
            exposureGraphSub.setRelations(&exposureSub, NULL, NULL, &exposureDurationSub);
            exposureDurationSub.setRelations(&exposureSub, NULL, &exposureGraphSub, &exposureRampSub);
            exposureRampSub.setRelations(&exposureSub, NULL, &exposureDurationSub, NULL);
        timelapsSub.setRelations(&menuRoot, &timelapsGraphSub, &exposureSub, NULL);
            timelapsGraphSub.setRelations(&timelapsSub, NULL, NULL, &timelapsDurationSub);
            timelapsDurationSub.setRelations(&timelapsSub, NULL, &timelapsGraphSub, &timelapsRampSub);
            timelapsRampSub.setRelations(&timelapsSub, NULL, &timelapsDurationSub, NULL);
    //***Testing function Pointer
    curentItem->printStructure(printSerial);
    Serial.println("\r\n");
    curentItem->incrementSelection();
    curentItem->incrementSelection();
    curentItem->incrementSelection();
    //curentItem->decrementSelection();

    curentItem = curentItem->select();
    curentItem->printStructure(printSerial);
    Serial.println("\r\n");
    curentItem->decrementSelection();
    curentItem->decrementSelection();


    curentItem = curentItem->select();
    curentItem->printStructure(printSerial);
}

void loop() {
  // put your main code here, to run repeatedly:

}

