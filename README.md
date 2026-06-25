# IoT-Grass-Cutter-Robot
🤖 Autonomous IoT grass cutter robot built with Arduino UNO — obstacle avoidance via HC-SR04, BLDC cutting motor, WiFi remote control. BCA 4th Sem project.
<div align="center">

<!-- Banner -->
<img src="https://capsule-render.vercel.app/api?type=waving&color=1A56A0&height=200&section=header&text=IoT%20Grass%20Cutter%20Robot&fontSize=42&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Autonomous%20Lawn%20Mower%20%7C%20Arduino%20UNO%20%7C%20IoT%20Integrated&descAlignY=58&descColor=CADCFC" />

<br/>

<!-- Badges -->
![Arduino](https://img.shields.io/badge/Arduino-UNO%20R3-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-ESP8266%2FESP32-FF6900?style=for-the-badge&logo=esphome&logoColor=white)
![C++](https://img.shields.io/badge/C++-Embedded-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-28A745?style=for-the-badge)
![University](https://img.shields.io/badge/Apeejay%20Stya-University-1A56A0?style=for-the-badge)

<br/>

> 🤖 **An autonomous IoT-powered robot that automatically cuts grass and trims weeds — no human intervention required.**

</div>

---

## 📌 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Hardware Components](#-hardware-components)
- [Circuit & Pin Connections](#-circuit--pin-connections)
- [Software & Libraries](#-software--libraries)
- [How It Works](#-how-it-works)
- [IoT Integration](#-iot-integration)
- [Results](#-results)
- [Future Scope](#-future-scope)
- [Team](#-team)
- [License](#-license)

---

## 🌿 About the Project

This project presents the design and development of an **IoT-Based Automatic Grass Cutter and Weed Trimmer Robot** — an autonomous system built on the **Arduino UNO R3** microcontroller platform.

The robot:
- 🚗 Navigates lawns **autonomously** using ultrasonic obstacle detection
- ✂️ Cuts grass using a **BLDC Brushless DC Motor** with 4 blades
- 📡 Connects to the **internet via WiFi (ESP8266/ESP32)** for remote control
- 📱 Can be **monitored and controlled** through a mobile application
- ⚙️ Features a **variable-height cutting head** for different grass types

> **Course:** Internet of Things & Its Applications  
> **Semester:** BCA 2nd Year — 4th Semester  
> **University:** Apeejay Stya University, 2025–2026  
> **Supervisor:** Prof. Parikshit

---

## ✨ Features

| Feature | Description |
|---|---|
| 🤖 **Autonomous Navigation** | Moves independently, no manual control needed |
| 🚧 **Obstacle Detection** | HC-SR04 ultrasonic sensor detects objects up to 4m |
| 🔄 **Smart Path Planning** | Servo scans left/right and chooses the clearer path |
| ✂️ **Variable Height Cutting** | Adjustable cutting head for 3 different grass heights |
| 📡 **IoT Remote Control** | Start/stop via mobile app over WiFi |
| 🔔 **Alert Notifications** | Battery low & obstacle alerts sent to phone |
| ⏰ **Auto Scheduling** | Set automatic mowing times via IoT dashboard |
| 🔋 **Long Battery Life** | 11.1V 14000mAh LiPo — 2+ hours runtime |

---

## 🔧 Hardware Components

```
📦 Component List
├── 1x  Arduino UNO R3          → Main Microcontroller (Brain)
├── 1x  L293D Motor Driver Shield → Controls 4 DC motors
├── 4x  Johnson DC Gear Motor 12V → 4-Wheel Drive (200 RPM)
├── 1x  BLDC Brushless DC Motor  → High-speed grass cutting
├── 1x  HC-SR04 Ultrasonic Sensor → Obstacle detection
├── 1x  SG90 Servo Motor         → Left/Right scanning head
├── 1x  ESC + Servo Tester       → Controls BLDC speed
├── 1x  LiPo Battery 11.1V 14Ah  → Main power supply
├── 1x  WiFi Module ESP8266/ESP32 → IoT connectivity
├── 4x  Cutting Blades           → Attached to BLDC motor
├── 4+1x Wheels (Large + Medium)  → 4WD locomotion
└── 1x  Sunboard/Metal Chassis   → Robot body frame
```

---

## ⚡ Circuit & Pin Connections

| Component | Pin/Port | Arduino Connection | Purpose |
|---|---|---|---|
| L293D Shield | Motor Shield | Stacked on UNO | Controls motor direction & speed |
| DC Motor 1 (Front-Left) | M1 Port | L293D Shield M1 | Front-Left wheel |
| DC Motor 2 (Front-Right) | M2 Port | L293D Shield M2 | Front-Right wheel |
| DC Motor 3 (Rear-Left) | M3 Port | L293D Shield M3 | Rear-Left wheel |
| DC Motor 4 (Rear-Right) | M4 Port | L293D Shield M4 | Rear-Right wheel |
| Ultrasonic TRIG | TRIG Pin | Arduino **A0** | Sends ultrasonic pulse |
| Ultrasonic ECHO | ECHO Pin | Arduino **A1** | Receives reflected pulse |
| SG90 Servo | PWM Signal | Arduino **D10** | Head pan for scanning |
| BLDC Motor | 3-wire | ESC → Servo Tester → 11.1V | Cutting blade |
| LiPo Battery | VCC/GND | EXT_PWR on Shield | Powers entire robot |

---

## 💻 Software & Libraries

```cpp
// Libraries Used
#include <AFMotor.h>   // Adafruit Motor Shield library → DC motor control
#include <Servo.h>     // Standard Arduino servo        → SG90 motor control
```

**Install via Arduino IDE Library Manager:**
- `AFMotor` by Adafruit
- `Servo` (built-in)

---

## ⚙️ How It Works

```
┌─────────────────────────────────────────────────────┐
│                   ROBOT LOGIC FLOW                  │
├─────────────────────────────────────────────────────┤
│                                                     │
│  START → Servo centers at 90° (facing forward)      │
│       ↓                                             │
│  Ultrasonic measures distance every loop            │
│       ↓                                             │
│  distance > 20cm?                                   │
│  ├── YES → All 4 motors FORWARD → keep cutting      │
│  └── NO  → STOP all motors (obstacle detected!)     │
│           ↓                                         │
│       Servo scans RIGHT (30°) → measure distR       │
│       Servo scans LEFT (150°) → measure distL       │
│           ↓                                         │
│       distR > distL?                                │
│       ├── YES → Turn RIGHT (400ms)                  │
│       └── NO  → Turn LEFT  (400ms)                  │
│           ↓                                         │
│       Resume FORWARD movement → repeat              │
│                                                     │
└─────────────────────────────────────────────────────┘
```

---

## 📡 IoT Integration

```
📱 Mobile App
     ↕  (WiFi / MQTT / HTTP)
☁️  Cloud Server (AWS IoT / Firebase)
     ↕  (Serial Communication)
🔌 ESP8266 / ESP32 WiFi Module
     ↕  (UART / I2C)
🤖 Arduino UNO (Main Controller)
```

**IoT Features:**
- ✅ Real-time sensor data monitoring (distance, battery %)
- ✅ Remote Start / Stop commands via mobile app
- ✅ Automated mowing schedule programming
- ✅ Push notifications on obstacle detection
- ✅ Battery low alert system

---

## 📊 Results

| Test | Result |
|---|---|
| Obstacle detection range | 2 cm – 3.5 m ✅ |
| Stop threshold accuracy | 20 cm (reliable) ✅ |
| Turning response time | ~400–600 ms ✅ |
| Max grass height (cutting) | ~8 cm ✅ |
| Battery runtime | 2+ hours ✅ |
| IoT remote command latency | < 2 seconds ✅ |

---

## 🚀 Future Scope

- [ ] 🛰️ **GPS Navigation** — Pre-programmed routes with auto return-to-base
- [ ] 🤖 **AI Terrain Mapping** — ML-based garden map & path optimization
- [ ] ☀️ **Solar Charging** — Self-sustaining energy system
- [ ] 👁️ **Computer Vision** — Camera for grass height & weed detection
- [ ] 🔊 **Voice Control** — Alexa / Google Home integration
- [ ] 🏢 **Multi-Robot Fleet** — Coordinated bots for large areas
- [ ] 🛡️ **All-Terrain Chassis** — Waterproof design for wet conditions

---

## 👥 Team

| Name | Role |
|---|---|
| **Shubham Kumar** ⭐ | Team Lead / Hardware Design / Coding |
| Vishwash Anand | Arduino Programming |
| Khushi | Circuit Design |
| Ritika | Documentation |
| Naitik | Mechanical Assembly |
| Krish | Sensor Integration |
| Tema | Testing & QA |
| Ochen | Power Management |
| Caleb | Presentation Design |
| Roshan Kumar | Research & Analysis |

---

## 📄 License

MIT license

This project is for **academic purposes** under Apeejay Stya University.  
Feel free to fork, learn, and build upon it! ⭐

---

<div align="center">

**Made with ❤️ by Team IoT | BCA 4th Sem | Apeejay Stya University | 2025**

<img src="https://capsule-render.vercel.app/api?type=waving&color=1A56A0&height=100&section=footer" />

</div>
