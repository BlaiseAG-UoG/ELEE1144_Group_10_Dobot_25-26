# DOBOTSIM.PY FILE
# VERSION: 1.5.1
#
# DOBOT BLOCK MOVEMENT AND COMMAND ASSIGNEMENT
# CONTRIBUTERS - bg7890g@gre.ac.uk - rd8814j@gre.ac.uk - da1437y@gre.ac.uk
#
# V 1.0.0 - Simple script to grab the positions for our preferred placements, uses getPoseCmd to send coordinates and then we will use those to send back.
#
# V 1.1.0 - Now added the locations declaring them as bytes so we can send the functions back to the robot in a write state instead of a read state. The loop is
#           a simple verification tool just telling the Dobot where to go.
#
# V 1.2.0 - Added the drop points as an array of commands and added a drop index so we can count the block/cycles without the code being too large. Also added
#           suction commands to trial using blocks.
#
# V 1.3.0 - Retrieval system was now added, this code should back iterate through the positions and pick all the blocks up and returned to home. Also added a waitCmd for future code changes.
#
# V 1.3.1 - Replaced long delays with new waitCmd so they will execute efficiently rather than us telling it when to do so.
#
# V 1.3.2 - Adding already supplied light sensor code as we know it works via file lightSensor.cpp. This is produced by the university.
#
# V 1.4.0 - Added our own colour sensing based on the results we got back from our colour test. Uses light levels to determine what colour band it is in. The applied sensor is 8mm away.
#
# V 1.5.0 - Added the python script used to simulate block placement based on colour. The python coordinates simulator will be added in a later version.
#
# V 1.5.1 - Added the python coordinates verification tool, dobotCordSim.py checked the numbers match up with how the Dobot would see it.

import struct

# --- RAW COMMANDS ---
RAW_COMMANDS = [
    # 0
    [170, 170, 19, 84, 3, 0, 224, 42, 128, 67, 66, 208, 238, 192, 48, 202, 192, 65, 18, 117, 213, 191, 6],
    # 1
    [170, 170, 19, 84, 3, 0, 77, 144, 145, 67, 157, 182, 9, 191, 182, 119, 33, 194, 169, 210, 216, 189, 189],
    # 2
    [170, 170, 19, 84, 3, 0, 164, 100, 20, 67, 199, 237, 53, 195, 216, 122, 50, 194, 45, 48, 75, 194, 238],
    # 3
    [170, 170, 19, 84, 3, 0, 167, 239, 3, 67, 109, 141, 83, 195, 30, 150, 47, 194, 48, 51, 104, 194, 139],
    # 4
    [170, 170, 19, 84, 3, 0, 12, 128, 233, 66, 244, 73, 54, 195, 174, 91, 46, 194, 111, 114, 101, 194, 187],
    # 5
    [170, 170, 19, 84, 3, 0, 176, 180, 203, 65, 84, 71, 118, 195, 240, 5, 53, 194, 176, 49, 168, 194, 46],
    # 6
    [170, 170, 19, 84, 3, 0, 237, 127, 40, 66, 226, 2, 89, 195, 12, 153, 45, 194, 134, 7, 158, 194, 82],
    # 7
    [170, 170, 19, 84, 3, 0, 220, 173, 16, 65, 60, 244, 86, 195, 24, 64, 46, 194, 173, 46, 175, 194, 242],
    # 8
    [170, 170, 19, 84, 3, 0, 252, 85, 91, 67, 218, 204, 198, 194, 2, 108, 48, 194, 3, 9, 195, 193, 156],
    # 9
    [170, 170, 19, 84, 3, 0, 38, 155, 74, 67, 116, 226, 3, 195, 76, 136, 48, 194, 60, 63, 4, 194, 56],
    # 10
    [170, 170, 19, 84, 3, 0, 65, 45, 60, 67, 220, 182, 199, 194, 122, 65, 46, 194, 153, 159, 223, 193, 30]
]

def parse_dobot_ptp(raw_command):
     
    Y_bytes = raw_command[6:10]
    X_bytes = raw_command[10:14]
    Z_bytes = raw_command[14:18]
    R_bytes = raw_command[18:22]
    
    X_value = struct.unpack('<f', bytes(X_bytes))[0]
    Y_value = struct.unpack('<f', bytes(Y_bytes))[0]
    Z_value = struct.unpack('<f', bytes(Z_bytes))[0]
    R_value = struct.unpack('<f', bytes(R_bytes))[0]
    
    return X_value, Y_value, Z_value, R_value

def print_trajectory_table(commands):
    print("\n--- DOBOT COORDINATE VERIFICATION ---")
    print("----------------------------------------------------------------")
    print(" # |   X (Forward)  |  Y (Side-to-Side) |   Z (Up/Down)  |  R (Rotation) ")
    print("---|----------------|-------------------|----------------|---------------")

    for i, cmd in enumerate(commands):
        x, y, z, r = parse_dobot_ptp(cmd)
        
        label = str(i)
        if i == 0: label = "Hover"
        if i == 1: label = "Down"

        print(f" {label:2} | {x:14.2f} | {y:17.2f} | {z:14.2f} | {r:12.2f}")

    print("----------------------------------------------------------------")


if __name__ == "__main__":
    print_trajectory_table(RAW_COMMANDS)