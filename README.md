# Embedded System Robot

An embedded systems project simulating a Mars rover application using the iRobot Create 2 platform with modifications from the ECPE department at Iowa State. The vehicle can navigate a hazard-filled test field, communicate sensor data to a base station, and respond to real-time user commands through a UART-based interface.

<img width="507" height="573" alt="Robot" src="https://github.com/user-attachments/assets/157fc709-d9f7-45ab-9892-d8ff8c258e89" />

## Project Overview
- Autonomous navigation across a test field simulating Martian terrain
- Avoids tall and short obstacles using IR, Ping, bump, and cliff sensors
- Interfaces with a base station to send sensor data and receive movement commands
- Uses UART communication to control robot behavior and display telemetry
- Detects and stops in a predefined destination zone
- Prioritizes emergency sensor responses over base station commands
- Includes custom music playback and MATLAB-based CLI for enhanced interaction

## Features

### Core Functionality
- **Sensor Communication Interface**
  - Base station UI displays bump and cliff sensor states in real-time
  - Remote commands allow the user to move the CyBot and initiate distance sweeps

- **Autonomous Obstacle Avoidance**
  - Uses Ping and IR sensors for tall object detection (≥6 inches)
  - Detects short objects via bump sensors and adjusts motion accordingly
  - Avoids falling into holes using iRobot cliff and wheel-drop sensors

- **Boundary and Field Awareness**
  - Detects out-of-bounds areas using white tape markers
  - Avoids hazards using real-time sensor feedback (no map preloading)

- **Remote Command Processing**
  - Commands received via UART are executed with enforced priority:
    1. Emergency sensor interrupts (bump, cliff)
    2. Base station user commands
    3. Onboard autonomous behavior

- **Destination Zone Navigation**
  - Identifies and stops within a four-pillar goal zone (pillars are 3 inches in diameter)
  - Sends a completion signal to the base station when inside the target area

---

### Bonus Features
- **Music Library**
  - Developed a sound module capable of playing predefined melodies on the CyBot using PWM audio output
  - Can be triggered automatically (e.g., upon reaching the destination zone) or manually via the base station

- **MATLAB Command-Line Interface (CLI)**
  - Created a MATLAB-based terminal interface for controlling the CyBot
  - Supports full movement, sensor sweeps, and live feedback from the robot
  - Adds an intuitive and familiar control layer for engineers and researchers

---

## Hardware Used
- **iRobot Create 2 with custom additions from Iowa State**
- Ping and IR distance sensors
- Bump and cliff detection sensors
- UART communication over USB
- Tiva-C microcontroller
- Base station (PC with terminal and MATLAB interface)

## How It Works
- The robot is placed randomly in the test field with no prior knowledge of terrain
- On startup, the base station can activate the robot using a terminal interface
- The CyBot scans its environment and navigates toward the destination
- It avoids tall/short obstacles and holes using its sensor suite
- When destination pillars are detected, robot enters the zone and notifies the base station
- Upon arrival, it can also play a melody using the music module

## Operating Instructions
- **Start Robot**: Send activation signal via terminal
- **Run Sensor Sweep**: Issue a scan command to gather object distance data
- **Control Movement**: Use `w`, `a`, `s`, `d` style commands or GUI buttons
- **Monitor Sensors**: View cliff and bump sensor readings live
- **Complete Mission**: Trigger Star Wars theme at destination

---

