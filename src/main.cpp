// MAIN.CPP FILE
// VERSION: 1.0.0
//
// DOBOT BLOCK MOVEMENT AND COMMAND ASSIGNEMENT
// CONTRIBUTERS - bg7890g@gre.ac.uk - rd8814j@gre.ac.uk - da1437y@gre.ac.uk
//
// V 1.0.0 - Simple script to grab the positions for our preferred placements, uses getPoseCmd to send coordinates and then we will use those to send back.

#include <Arduino.h>
#include <Dobot.h>

Dobot dobot = Dobot();

byte goHomeCmd[] = {170, 170, 6, 31, 1, 0, 0, 0, 0, 224};
byte getPoseCmd[] = {170, 170, 2, 10, 0, 246};

void setup() {
    Serial.begin(9600);
    dobot.begin();
    dobot.commandFrame(goHomeCmd);
    delay(15000);
}

void loop() {
    Serial.begin(9600);
    dobot.commandFrame(getPoseCmd);
    delay(5000);
}