# 🌡️ Temperature Control System with LED Indicators and Servo Motor 

## Overview
This project is a temperature monitoring and control system that uses a temperature sensor, servo motor, and LEDs to alert the user to temperature fluctuations. The system allows the user to set a threshold temperature in degrees Celsius (°C) and provides two options for program termination:

1. Running for a specified number of seconds.
2. Ending after a specified number of servo motor activations.

The program monitors the temperature continuously, turning the 🔴 red LED on when the temperature exceeds the threshold and activating the 🔵 blue LED and servo motor (to a 45-degree position) when it falls below the threshold.

## Components
- **🌡️ Temperature Sensor:** Monitors the current temperature in real-time.
- **⚙️ Servo Motor:** Adjusts its position based on temperature changes, turning approximately 45 degrees when the temperature falls below the threshold.
- **💡 LED Indicators:**
   - **🔴 Red LED:** Turns on when the temperature is above the threshold, indicating high temperature.
   - **🔵 Blue LED:** Turns on when the temperature is below the threshold, indicating low temperature.

## How It Works
1. **Threshold Input:** The program prompts the user to enter a temperature threshold in Celsius.
2. **Exit Strategy:** The user selects an exit strategy:
    - ⏳ Run for a specified duration in seconds.
    - 🔄 End after a certain number of servo motor activations.
3. **Temperature Monitoring:**
    - If the temperature is above the threshold, the 🔴 red LED is activated, and the 🔵 blue LED turns off.
    - If the temperature drops below the threshold, the 🔴 red LED turns off, the 🔵 blue LED turns on, and the ⚙️ servo motor moves to 45 degrees.
    - Temperature updates are displayed on the console 5 times per second.

