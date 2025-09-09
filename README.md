# LPC-2148-learning-projects

## 🎓 Overview
This repository contains my completed work, code samples, and mini-projects from the LPC2148 ARM7-based microcontroller learning course. The course focused on getting hands-on experience with embedded systems programming, peripheral interfacing, and real-time control using the LPC2148 microcontroller from NXP (Philips).
---
The course covered both theoretical concepts and practical implementations, using tools like:
 - Keil uVision IDE (for coding and simulation)
 - Flash Magic (for programming the LPC2148)
 - Proteus / Real hardware setup (for hardware simulation or deployment)

## 📦 Repository Structure
``` bash
lpc2148-learning Projects/
│
├── Code/
│   └── code with Proteus Simulation
├── Target/
│   └── code used with Hardware
├── Proteus/
│
└── README.md
```

## 🔧 Tools & Setup
 - **Microcontroller** : LPC-2148(ARM7TDMI-S core)
 - **IDE** : Keil µVision 4
 - **Programmer** : Flash Magic
 - **Simulation** : Proteus / Real Hardware
 - **Language** : Embedded C

## Topics Covered
 - GPIO 
 - LCD interfacing (16x2)
 - UART Communication
 - Keypad
 - Motor Driver
 - Seven Segments
 - ADC
 - DAC
 - PWM
 - Timers
 - Interrupts (External / Internal)

## 🚀 How to Run the Code
 1. Open the project folder in Keil.
 2. Compile the code.
 3. Generate the ```.hex ``` file.
 4. Use Flash Magic to Program the hex file into target.
 5. (sometimes) Press reset and observe the code execuetion.

## 📌 Key Learnings
 - Understanding of ARM7 microcontroller internals,
 - Hands-on Experience with real-time embedded programming.
 - debugging using keil ide
 - successfully interfaced LPC-2148 pheripherals.



## License
- This repository is for educational purposes and is licensed under the MIT License. You are free to use, modify, or extend the code with proper attribution.

- Note: The MIT License applies only to the original code written by Me. Third-party files such as startup.s and vendor-supplied system files are subject to their own licenses.
