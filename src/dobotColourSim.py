# DOBOTSIM.PY FILE
# VERSION: 1.5.0
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

import random

# --- CONFIGURATION ---
NUM_DROP_POINTS = 9
FULL_CYCLE_LENGTH = NUM_DROP_POINTS * 2

# --- INITIAL STATE ---
current_index = 0
pink_index = 0
green_index = 3
black_index = 6
total_blocks_processed = 0

# --- SIMULATED INPUTS --- (CHANGE VALUES TO WHATEVER YOU WANT TO SIMULATE)
SIMULATED_SENSOR_VALUES = [
    100, 500, 800,
    150, 550, 850,
    300, 650, 9999
]

def simulate_sensor_read():
    if total_blocks_processed < len(SIMULATED_SENSOR_VALUES):
        return SIMULATED_SENSOR_VALUES[total_blocks_processed]
    else:
        return 0 

def get_color_and_slot(sensor_value):
    global pink_index, green_index, black_index
    
    if not (sensor_value >= 0 and sensor_value <= 1050):
        return "UNKNOWN", -1, None

    if sensor_value >= 0 and sensor_value <= 325:
        target_slot = pink_index
        pink_index = (pink_index >= 2) and 0 or pink_index + 1
        return "PINK", target_slot, pink_index
        
    elif sensor_value >= 350 and sensor_value <= 675:
        target_slot = green_index
        green_index = (green_index >= 5) and 3 or green_index + 1
        return "GREEN", target_slot, green_index

    elif sensor_value >= 700 and sensor_value <= 1050:
        target_slot = black_index
        black_index = (black_index >= 8) and 6 or black_index + 1
        return "BLACK", target_slot, black_index

    else:
        return "UNSORTED/GAP", -1, None


def run_simulation():
    global current_index, pink_index, green_index, black_index, total_blocks_processed
    
    print("\n--- DOBOT SORTING LOGIC SIMULATOR ---")
    print(f"| Step | Phase | Sensor | Color | Drop Slot | Next Pink | Next Green | Next Black |")
    print("-----------------------------------------------------------------------------------")
    
    while current_index < FULL_CYCLE_LENGTH:
        
        if current_index < NUM_DROP_POINTS:
            phase = "DROP"
            
            # --- DROP LOGIC ---
            sensor = simulate_sensor_read()
            color, target_slot, next_index = get_color_and_slot(sensor)
            
            if color == "PINK": 
                pink_index = next_index
                total_blocks_processed += 1
            elif color == "GREEN": 
                green_index = next_index
                total_blocks_processed += 1
            elif color == "BLACK": 
                black_index = next_index
                total_blocks_processed += 1
            elif color == "UNSORTED/GAP":
                target_slot = "Error"
                total_blocks_processed += 1
            else:
                target_slot = "Hover"
                total_blocks_processed += 1

            
            print(f"| {current_index+1:4} | {phase:5} | {sensor:6} | {color:5} | {target_slot:8} | {pink_index:9} | {green_index:10} | {black_index:9} |")
            
        else:
            # --- RETRIEVAL LOGIC ---
            phase = "RETRIEVE"
            retrieval_slot = FULL_CYCLE_LENGTH - 1 - current_index 
            
            print(f"| {current_index+1:4} | {phase:5} |   ---  |  ---  | {retrieval_slot:8} | {pink_index:9} | {green_index:10} | {black_index:9} |")

        current_index += 1

    print("-----------------------------------------------------------------------------------")
    print("Simulation Complete.")
    
if __name__ == "__main__":
    run_simulation()