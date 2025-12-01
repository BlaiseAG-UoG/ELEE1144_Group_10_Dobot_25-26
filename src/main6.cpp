// MAIN.CPP FILE
// VERSION: 1.5.0
//
// DOBOT BLOCK MOVEMENT AND COMMAND ASSIGNEMENT
// CONTRIBUTERS - bg7890g@gre.ac.uk - rd8814j@gre.ac.uk - da1437y@gre.ac.uk
//
// V 1.0.0 - Simple script to grab the positions for our preferred placements, uses getPoseCmd to send coordinates and then we will use those to send back.
//
// V 1.1.0 - Now added the locations declaring them as bytes so we can send the functions back to the robot in a write state instead of a read state. The loop is
//           a simple verification tool just telling the Dobot where to go.
//
// V 1.2.0 - Added the drop points as an array of commands and added a drop index so we can count the block/cycles without the code being too large. Also added
//           suction commands to trial using blocks.
//
// V 1.3.0 - Retrieval system was now added, this code should back iterate through the positions and pick all the blocks up and returned to home. Also added a waitCmd for future code changes.
//
// V 1.3.1 - Replaced long delays with new waitCmd so they will execute efficiently rather than us telling it when to do so.
//
// V 1.3.2 - Adding already supplied light sensor code as we know it works via file lightSensor.cpp. This is produced by the university.
//
// V 1.4.0 - Added our own colour sensing based on the results we got back from our colour test. Uses light levels to determine what colour band it is in. The applied sensor is 8mm away.
//
// V 1.5.0 - Added the python script used to simulate block placement based on colour. The python coordinates simulator will be added in a later version.

#include <Arduino.h>
#include <Dobot.h>

Dobot dobot = Dobot();

const int NUM_DROP_POINTS = 9;
int currentDropIndex = 0;

// --- COLOUR SORTING INDEX ---
uint8_t pinkIndex = 0;
uint8_t greenIndex = 3;
uint8_t blackIndex = 6;

// --- RAW COMMAND PACKETS ---
byte suckOnCmd[] = {170, 170, 4, 62, 3, 1, 1, 189};
byte suckOffCmd[] = {170, 170, 4, 62, 3, 1, 0, 190};
byte waitCmd[] = {170, 170, 6, 110, 3, 0, 100, 0, 0, 0, 43};

// --- PICKUP LOCATION COMMANDS ---
byte pickupPosDownCmd[] = {170, 170, 19, 84, 3, 0, 77, 144, 145, 67, 157, 182, 9, 191, 182, 119, 33, 194, 169, 210, 216, 189, 189};
byte pickupPosHoverCmd[] = {170, 170, 19, 84, 3, 0, 224, 42, 128, 67, 66, 208, 238, 192, 48, 202, 192, 65, 18, 117, 213, 191, 6};
byte poshome[] = {170, 170, 19, 84, 3, 0, 20, 3, 52, 67, 187, 118, 27, 56, 0, 160, 101, 188, 238, 237, 69, 55, 127};

// --- PINK AREA DROPS ---
byte dropPos1Cmd[] = {170, 170, 19, 84, 3, 0, 164, 100, 20, 67, 199, 237, 53, 195, 216, 122, 50, 194, 45, 48, 75, 194, 238};
byte dropPos2Cmd[] = {170, 170, 19, 84, 3, 0, 167, 239, 3, 67, 109, 141, 83, 195, 30, 150, 47, 194, 48, 51, 104, 194, 139};
byte dropPos3Cmd[] = {170, 170, 19, 84, 3, 0, 12, 128, 233, 66, 244, 73, 54, 195, 174, 91, 46, 194, 111, 114, 101, 194, 187};

// --- GREEN AREA DROPS ---
byte dropPos4Cmd[] = {170, 170, 19, 84, 3, 0, 176, 180, 203, 65, 84, 71, 118, 195, 240, 5, 53, 194, 176, 49, 168, 194, 46};
byte dropPos5Cmd[] = {170, 170, 19, 84, 3, 0, 237, 127, 40, 66, 226, 2, 89, 195, 12, 153, 45, 194, 134, 7, 158, 194, 82};
byte dropPos6Cmd[] = {170, 170, 19, 84, 3, 0, 220, 173, 16, 65, 60, 244, 86, 195, 24, 64, 46, 194, 173, 46, 175, 194, 242};

// --- BLACK AREA DROPS ---
byte dropPos7Cmd[] = {170, 170, 19, 84, 3, 0, 252, 85, 91, 67, 218, 204, 198, 194, 2, 108, 48, 194, 3, 9, 195, 193, 156};
byte dropPos8Cmd[] = {170, 170, 19, 84, 3, 0, 38, 155, 74, 67, 116, 226, 3, 195, 76, 136, 48, 194, 60, 63, 4, 194, 56};
byte dropPos9Cmd[] = {170, 170, 19, 84, 3, 0, 65, 45, 60, 67, 220, 182, 199, 194, 122, 65, 46, 194, 153, 159, 223, 193, 30};

// Array OF ALL 9 DROPS ---
byte* dropPositions[] = {
    dropPos1Cmd, dropPos2Cmd, dropPos3Cmd, dropPos4Cmd, dropPos5Cmd,
    dropPos6Cmd, dropPos7Cmd, dropPos8Cmd, dropPos9Cmd
};

int readLightSensor() {
    int sensorValue = analogRead(A0); 
    Serial.print("Sensor Read: ");
    Serial.println(sensorValue);
    delay(10); 
    return sensorValue;
}
 

void setup() {
  
  dobot.begin();
  Serial.begin(9600); // Arduino Baud Rate Is 9600
  
  // --- QUEUE SETUP (Clear, Start) ---
  byte clearQueueCmd[] = {170, 170, 2, 245, 1, 0, 10};
  dobot.commandFrame(clearQueueCmd);
  delay(100);
  
  byte startQueue[] = {170, 170, 2, 240, 1, 0, 15};
  dobot.commandFrame(startQueue);
  Serial.println("Ready. Entering Incremental Pick-Lift-Drop Loop.");
}

void loop() {
    if (currentDropIndex >= NUM_DROP_POINTS * 2) {
        currentDropIndex = 0;
        pinkIndex = 0;   
        greenIndex = 3;  
        blackIndex = 6;
        Serial.println("--- Full Cycle Complete ---");
        delay(1000);
    }
    
    if (currentDropIndex < NUM_DROP_POINTS) {
        
        // --- PICK UP ---
        dobot.commandFrame(pickupPosHoverCmd); 
        dobot.commandFrame(waitCmd);
        delay(100);

        dobot.commandFrame(pickupPosDownCmd); 
        dobot.commandFrame(waitCmd); 
        delay(100); 

        int sensorValue = readLightSensor();

        dobot.commandFrame(suckOnCmd); 
        delay(500); 
        
        dobot.commandFrame(pickupPosHoverCmd);
        dobot.commandFrame(waitCmd);
        delay(100);
        
        byte* targetDropCmd;
        int targetSlot;
        
        // --- COLOUR CASES ---
        // --- PINK ---
        if (sensorValue >= 0 && sensorValue <= 325) {
            targetSlot = pinkIndex;
            Serial.println("-> Detected: PINK");
            pinkIndex = (pinkIndex >= 2) ? 0 : pinkIndex + 1;
        }
        
        // --- GREEN ---
        else if (sensorValue >= 350 && sensorValue <= 675) {
            targetSlot = greenIndex;
            Serial.println("-> Detected: GREEN");
            greenIndex = (greenIndex >= 5) ? 3 : greenIndex + 1;
        }
        
        // --- BLACK ---
        else if (sensorValue >= 700 && sensorValue <= 1050) {
            targetSlot = blackIndex;
            Serial.println("-> Detected: BLACK");
            blackIndex = (blackIndex >= 8) ? 6 : blackIndex + 1;
        }
        
        // --- UNKNOWN COLOUR ---
        else {
            targetDropCmd = pickupPosHoverCmd; 
            targetSlot = -1;
            Serial.println("-> Detected: OUT OF RANGE. Dropping.");
        }
        
        if (targetSlot != -1) {
            targetDropCmd = dropPositions[targetSlot];
        }

        dobot.commandFrame(targetDropCmd); 
        dobot.commandFrame(waitCmd); 
        delay(100); 
        
    
        dobot.commandFrame(suckOffCmd); 
        Serial.print("DROPPING: Dropped at position");
        if (targetSlot != -1) {
            Serial.println(targetSlot + 1);
        } 
        
        else {
            Serial.println("Hover Position.");
        }
       
        delay(500); 
    
        dobot.commandFrame(pickupPosHoverCmd);
        dobot.commandFrame(waitCmd);
        delay(100); 
    }

    else {


        // --- RETRIEVAL ---
        const int retrievalIndex = NUM_DROP_POINTS * 2 - 1 - currentDropIndex;

        dobot.commandFrame(pickupPosHoverCmd); 
        dobot.commandFrame(waitCmd);
        delay(100);

        dobot.commandFrame(dropPositions[retrievalIndex]);
        Serial.print("Moving to Pick Up Position");
        Serial.println(currentDropIndex + 1);
        dobot.commandFrame(waitCmd); 
        delay(100);

        dobot.commandFrame(suckOnCmd);
        Serial.println("Suction ON: Block collected.");
        delay(500);
        
        dobot.commandFrame(pickupPosHoverCmd);
        dobot.commandFrame(waitCmd);
        delay(100);
        
        dobot.commandFrame(pickupPosDownCmd);
        Serial.print("Moving to Drop Position ");
        dobot.commandFrame(waitCmd); 
        delay(100);

        dobot.commandFrame(suckOffCmd);
        Serial.println("Suction OFF: Block dropped.");
        delay(500); 
        
        dobot.commandFrame(pickupPosHoverCmd);
        dobot.commandFrame(waitCmd);
        delay(100);
    }
}

