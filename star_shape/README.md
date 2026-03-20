# Star Shape ATtiny85 LED Badge

A star-shaped LED badge built around the **ATtiny85** microcontroller.  
This project combines decorative PCB design, embedded programming, and compact battery-powered LED animation in a single board.

The badge is designed as both:
- a visual electronics project
- an educational ATtiny85 + KiCad portfolio project

---

## 1. Project Purpose

The goal of this project is to create a **star-shaped PCB badge** that can drive multiple LEDs with animation patterns using an **ATtiny85**.

This project is useful for learning:
- schematic design in KiCad
- PCB layout and routing
- generating Gerber and drill files
- using an ATtiny85 in a real hardware design
- programming through a 2x3 AVR ISP header
- designing decorative shape-based PCBs

---

## 2. Main Features

- Star-shaped PCB
- ATtiny85 microcontroller
- 5 LEDs
- Push button for interaction / mode changing
- On/off switch
- CR2032 battery powered
- ISP programming header
- Compact embedded design
- Suitable for decorative and educational use

---

## 3. What This Badge Can Do

This badge can be programmed to run different LED animations such as:
- sequential LED blinking
- alternating patterns
- all LEDs flashing together
- rotating or circular patterns
- mirrored animations
- idle and active modes
- button-controlled animation mode switching

With firmware changes, the project can be expanded further.

---

## 4. Folder Structure

```text
star_shape/
├── kicad/
│   ├── star_shape.kicad_pro
│   ├── star_shape.kicad_sch
│   └── star_shape.kicad_pcb
│
├── gerbers/
│   ├── ...fabrication files...
│
├── images/
│   ├── pcb.png
│   ├── schematic.png
│   ├── 3d view.png
│   ├── bom-table.png
│   └── Header.png
│
└── code/
    └── attiny_led_demo.ino
```

## 5. Hardware Overview

The badge is built around the **ATtiny85**, which controls the LEDs and reads the push button.

### Main hardware blocks

- ATtiny85: main controller
- 5 LEDs: visual output
- 5 current-limiting resistors
- Push button: user input
- On/off switch: power control
- CR2032 battery holder: portable power source
- 100nF capacitor: supply decoupling
- 10k resistor: reset pull-up
- 2x3 ISP header: programming interface

---

## 6. Bill of Materials (BOM)

A BOM image is included here:

![BOM Table](images/bom-table.png)

Typical component list:
- 1 × ATtiny85
- 5 × LEDs
- 5 × 220Ω resistors
- 1 × 10kΩ resistor
- 1 × 100nF capacitor
- 1 × push button
- 1 × on/off switch
- 1 × CR2032 battery holder
- 1 × 2x3 ISP header

---

## 7. PCB Images

### PCB Layout
![PCB Layout](images/pcb.png)

### Schematic
![Schematic](images/schematic.png)

### 3D View
![3D View](images/3d_view.png)

---

## 8. Pin Mapping

The ATtiny85 pins are used for LED control, button input, reset handling, and programming.

### Functional mapping

- **PB0** → LED control / programming line
- **PB1** → LED control / programming line
- **PB2** → LED control / programming line
- **PB4** → push button input
- **PB5 / RESET** → reset line
- **VCC / GND** → power input

Because this is a compact design, some pins are shared carefully between LED control and programming functions.

---

## 9. ISP Header Connections

The board uses a standard **2x3 AVR ISP header** for programming the ATtiny85.

### ISP header mapping

- **Pin 1** → RESET
- **Pin 2** → VCC
- **Pin 3** → PB1 / MOSI
- **Pin 4** → PB0 / MISO
- **Pin 5** → PB2 / SCK
- **Pin 6** → GND

A visual reference is included here:

![ISP Header Pins](images/Header.png)

---

## 10. How to Power the Board

This project is designed to run from a **CR2032 coin cell battery**.

### Power path

1. Insert the CR2032 battery into the holder.
2. Turn the board on using the on/off switch.
3. The ATtiny85 receives power and starts running the programmed animation.

### Notes

- The CR2032 is compact and suitable for lightweight badge-style projects.
- LED brightness and current usage should be considered to avoid draining the battery too quickly.
- The firmware can be optimized later for lower power consumption.

---

## 11. How to Program the ATtiny85

The ATtiny85 is programmed through the **2x3 ISP header**.

### Required tools

You can use one of the following:
- USBasp
- Arduino as ISP
- another AVR-compatible programmer

### General programming process

1. Connect the programmer to the 2x3 ISP header.
2. Make sure the board has power, or that the programmer provides it correctly if supported.
3. Upload the firmware to the ATtiny85.
4. Disconnect the programmer.
5. Turn the board on and test the LED behavior.

---

## 12. Example Firmware

An example firmware file is included in:

```text
code/attiny_led_demo.ino
```

This demo code shows how to:
- initialize the LED pins
- read the push button
- switch animation modes
- generate several LED patterns

### Example behavior
- mode 1: sequential blink
- mode 2: alternating blink
- mode 3: all LEDs flash
- mode 4: rotating pattern

---

## 13. Example Code

```cpp
/*
  Star Shape ATtiny85 LED Badge Demo

  Example firmware for a decorative LED badge based on the ATtiny85.

  Features:
  - 5 LEDs
  - 1 push button
  - multiple animation modes
  - button-controlled mode switching
*/

const int buttonPin = 4;   // PB4

const int led1 = 0;        // PB0
const int led2 = 1;        // PB1
const int led3 = 2;        // PB2
const int led4 = 3;        // PB3
const int led5 = 0;        // Example placeholder if shared logic is used

int mode = 0;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void loop() {
  handleButton();

  switch (mode) {
    case 0:
      sequentialBlink();
      break;
    case 1:
      alternatingBlink();
      break;
    case 2:
      allFlash();
      break;
    case 3:
      rotatingPattern();
      break;
    default:
      mode = 0;
      break;
  }
}

void handleButton() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      mode++;
      if (mode > 3) {
        mode = 0;
      }
    }
  }

  lastButtonState = reading;
}

void sequentialBlink() {
  digitalWrite(led1, HIGH); delay(100); digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH); delay(100); digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH); delay(100); digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH); delay(100); digitalWrite(led4, LOW);
}

void alternatingBlink() {
  digitalWrite(led1, HIGH);
  digitalWrite(led3, HIGH);
  delay(150);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);

  digitalWrite(led2, HIGH);
  digitalWrite(led4, HIGH);
  delay(150);
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);
}

void allFlash() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(200);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(200);
}

void rotatingPattern() {
  digitalWrite(led1, HIGH); delay(80); digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH); delay(80); digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH); delay(80); digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH); delay(80); digitalWrite(led4, LOW);
}
```

---

## 14. How the Example Code Works

The example firmware performs these steps:

### Startup
- initialize LED pins as outputs
- configure the button pin as input with pull-up
- set the default animation mode

### Main loop
- check the push button
- change mode when the button is pressed
- run the selected animation

### Animation logic
The firmware cycles through multiple visual modes:
- sequential blinking
- alternating groups
- all LEDs flashing together
- rotating movement effect

This demonstrates:
- digital output control
- button reading
- mode switching
- timing-based animation logic

---

## 15. How to Use the Badge

### Basic use
1. Insert the battery.
2. Turn on the power switch.
3. Observe the default animation.
4. Press the button to change animation modes.

### Educational use
This board can be used to practice:
- ATtiny programming
- LED control logic
- low-power design basics
- decorative PCB design

### Demonstration use
This board can also be used as:
- a portfolio project
- a classroom demonstration
- a beginner embedded systems example
- a decorative wearable electronics concept

---

## 16. What You Can Modify

This project is intentionally flexible.

You can improve or customize it by changing:
- LED colors
- animation timing
- button behavior
- board artwork
- number of modes
- power optimization strategy
- LED placement for a different star style

You can also reuse the same design idea for:
- a heart-shaped badge
- a logo-shaped PCB
- a gift badge
- a themed wearable board

---

## 17. Design Notes

This project was built as a practical exercise in:
- KiCad schematic capture
- PCB layout and routing
- Gerber generation
- ATtiny85 hardware integration
- GitHub documentation and project organization

It is not just a blinking LED board; it is intended as a compact, polished, and shareable design project.

---

## 18. Manufacturing Notes

Fabrication files are stored in:

```text
gerbers/
```

These include:
- copper layers
- mask layers
- silkscreen layers
- board outline
- drill files

Before fabrication, always verify:
- LED polarity
- ATtiny85 orientation
- switch footprint compatibility
- battery holder footprint compatibility
- programming header orientation

---

## 19. Recommended Checks Before Assembly

Before ordering or soldering the board, check:
- ATtiny85 pin orientation
- LED polarity
- resistor values
- push button footprint
- on/off switch footprint
- battery holder footprint
- ISP header orientation
- solder bridge risk on small pads
- board outline integrity

---

## 20. Suggested Improvements for Future Revisions

Possible future improvements:
- lower power firmware
- PWM fade animations
- cleaner visual LED symmetry
- fully optimized badge layout
- assembly photographs
- finished hardware photos
- animated GIF or demo video
- alternate shape variants
