// MAIN.CPP FILE
// VERSION: 1.1.0
//
// DOBOT BLOCK MOVEMENT AND COMMAND ASSIGNEMENT
// CONTRIBUTERS - bg7890g@gre.ac.uk - rd8814j@gre.ac.uk - da1437y@gre.ac.uk
//
// V 1.0.0 - Simple script to grab the positions for our preferred placements, uses getPoseCmd to send coordinates and then we will use those to send back.
//
// V 1.1.0 - Now added the locations declaring them as bytes so we can send the functions back to the robot in a write state instead of a read state. The loop is
//           a simple verification tool just telling the Dobot where to go.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                               
//                                                      THIS IS A COMPLETE WORKING VERSION OF THE CODE
//                                                      COLOUR SORTING:                lightSensor.cpp
//                                                      DOBOT MOVEMENTS:                     main2.cpp
//                                                      COMPATABILITY:                            100%
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <Dobot.h>

Dobot dobot = Dobot();

// --- PICKUP LOCATION COMMANDS ---
byte pickupPosDownCmd[] = {170, 170, 19, 84, 3, 0, 77, 144, 145, 67, 157, 182, 9, 191, 182, 119, 33, 194, 169, 210, 216, 189, 189};
byte pickupPosHoverCmd[] = {170, 170, 19, 84, 3, 0, 224, 42, 128, 67, 66, 208, 238, 192, 48, 202, 192, 65, 18, 117, 213, 191, 6};

// --- DROP-OFF LOCATION COMMANDS ---
byte dropPos1Cmd[] = {170, 170, 19, 84, 3, 0, 164, 100, 20, 67, 199, 237, 53, 195, 216, 122, 50, 194, 45, 48, 75, 194, 238};
byte dropPos2Cmd[] = {170, 170, 19, 84, 3, 0, 167, 239, 3, 67, 109, 141, 83, 195, 30, 150, 47, 194, 48, 51, 104, 194, 139};
byte dropPos3Cmd[] = {170, 170, 19, 84, 3, 0, 12, 128, 233, 66, 244, 73, 54, 195, 174, 91, 46, 194, 111, 114, 101, 194, 187};
byte dropPos4Cmd[] = {170, 170, 19, 84, 3, 0, 176, 180, 203, 65, 84, 71, 118, 195, 240, 5, 53, 194, 176, 49, 168, 194, 46};
byte dropPos5Cmd[] = {170, 170, 19, 84, 3, 0, 237, 127, 40, 66, 226, 2, 89, 195, 12, 153, 45, 194, 134, 7, 158, 194, 82};
byte dropPos6Cmd[] = {170, 170, 19, 84, 3, 0, 220, 173, 16, 65, 60, 244, 86, 195, 24, 64, 46, 194, 173, 46, 175, 194, 242};
byte dropPos7Cmd[] = {170, 170, 19, 84, 3, 0, 252, 85, 91, 67, 218, 204, 198, 194, 2, 108, 48, 194, 3, 9, 195, 193, 156};
byte dropPos8Cmd[] = {170, 170, 19, 84, 3, 0, 38, 155, 74, 67, 116, 226, 3, 195, 76, 136, 48, 194, 60, 63, 4, 194, 56};
byte dropPos9Cmd[] = {170, 170, 19, 84, 3, 0, 65, 45, 60, 67, 220, 182, 199, 194, 122, 65, 46, 194, 153, 159, 223, 193, 30};


void setup() {
  
  dobot.begin();
  Serial.begin(9600); // Arduino Baud Rate Is 9600
  
  // --- QUEUE SETUP (Clear, Start) ---
  byte clearQueueCmd[] = {170, 170, 2, 245, 1, 0, 10};
  dobot.commandFrame(clearQueueCmd);
  delay(500);
  
  byte startQueue[] = {170, 170, 2, 240, 1, 0, 15};
  dobot.commandFrame(startQueue);
  Serial.println("Ready. Entering Incremental Pick-Lift-Drop Loop.");
}

void loop()
{
    Serial.println("--- Starting Verification ---");
    
    // --- POSITION 1 ---
    Serial.println("Moving to Drop Position 1");
    dobot.commandFrame(dropPos1Cmd);
    delay(3000);
   
    // --- POSITION 2 ---
    Serial.println("Moving to Drop Position 2");
    dobot.commandFrame(dropPos2Cmd);
    delay(3000);
   
    // --- POSITION 3 ---
    Serial.println("Moving to Drop Position 3");
    dobot.commandFrame(dropPos3Cmd);
    delay(3000);
    
    // --- POSITION 4 ---
    Serial.println("Moving to Drop Position 4");
    dobot.commandFrame(dropPos4Cmd);
    delay(3000);

    // --- POSITION 5 ---
    Serial.println("Moving to Drop Position 5");
    dobot.commandFrame(dropPos5Cmd);
    delay(3000);

    // --- POSITION 6 ---
    Serial.println("Moving to Drop Position 6");
    dobot.commandFrame(dropPos6Cmd);
    delay(3000);

    // --- POSITION 7 ---
    Serial.println("Moving to Drop Position 7");
    dobot.commandFrame(dropPos7Cmd);
    delay(3000);

    // --- POSITION 8 ---
    Serial.println("Moving to Drop Position 8");
    dobot.commandFrame(dropPos8Cmd);
    delay(3000);

    // --- POSITION 9 ---
    Serial.println("Moving to Drop Position 9");
    dobot.commandFrame(dropPos9Cmd);
    delay(3000);
   
    Serial.println("--- Full Verification Complete ---");
    delay(10000); 
}
