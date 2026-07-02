# Maze Solver Car

## Overview

The Maze Solver Car is an autonomous robot built using an Arduino Uno that can navigate through a maze without human intervention. The robot uses three HC-SR04 ultrasonic sensors to detect obstacles in front, left, and right directions, allowing it to make real-time navigation decisions. An L298N motor driver controls the four DC motors mounted on a four-wheel chassis, enabling the robot to move forward, reverse, and turn as needed.

The navigation algorithm is based on distance measurements from the ultrasonic sensors and follows a rule-based decision-making approach. When an obstacle is detected, the robot determines the best movement based on the available paths. At dead ends, it reverses and turns toward the side with more open space, while at intersections it follows the left-hand rule.

## Features

* Autonomous maze navigation
* Real-time obstacle detection
* Three-direction distance sensing (Front, Left, Right)
* Forward, reverse, left, and right movement
* Dead-end detection and recovery
* Left-hand rule navigation
* PWM motor speed control

---

## Hardware Components

* Arduino Uno
* 3 × HC-SR04 Ultrasonic Sensors
* L298N Motor Driver
* Four-wheel robot chassis
* 4 DC Motors
* Battery Pack
* Jumper Wires

## Pin Configuration

| Component            | Arduino Pin |
| -------------------- | ----------- |
| Front Sensor Trigger | D2          |
| Front Sensor Echo    | D3          |
| Left Sensor Trigger  | D12         |
| Left Sensor Echo     | D13         |
| Right Sensor Trigger | D4          |
| Right Sensor Echo    | D7          |
| Motor Driver ENA     | D5 (PWM)    |
| Motor Driver ENB     | D6 (PWM)    |
| Motor Driver IN1     | D8          |
| Motor Driver IN2     | D9          |
| Motor Driver IN3     | D10         |
| Motor Driver IN4     | D11         |

---

## How It Works

1. The robot continuously measures the distance in front, left, and right using three ultrasonic sensors.
2. If no obstacle is detected within the predefined threshold, it continues moving forward.
3. If an obstacle is detected in front, the robot determines the next movement based on the available paths.
4. When both front and one side are blocked, it turns toward the open side.
5. If all three directions are blocked, the robot reverses and turns toward the side with the greater available distance.
6. The process repeats until the robot successfully navigates through the maze.

---

## Navigation Logic

| Sensor Condition             | Robot Action                                       |
| ---------------------------- | -------------------------------------------------- |
| Front, Left, and Right clear | Move Forward                                       |
| Front blocked                | Turn Left                                          |
| Front + Right blocked        | Turn Left                                          |
| Front + Left blocked         | Turn Right                                         |
| Left blocked                 | Move Forward                                       |
| Right blocked                | Move Forward                                       |
| Front + Left + Right blocked | Reverse, then turn toward the side with more space |

---

## Motor Parameters

| Parameter          |   Value |
| ------------------ | ------: |
| Detection Distance |   20 cm |
| Forward Speed      |  PWM 90 |
| Turning Speed      | PWM 120 |
| Turn Duration      |  440 ms |
