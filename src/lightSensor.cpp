// LIGHTSENSOR.CPP FILE
// VERSION: 1.3.2
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

#include <Arduino.h>

void setup() {
    Serial.begin(9600);
}

void loop() {

    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    delay(500);
}
