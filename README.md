# 🎵 Arduino Ultrasonic Gamepad Controller for Strudel

**Control music with distance!** This project turns an ultrasonic sensor into a musical controller for [Strudel.cc](https://strudel.cc).

---

## 📖 What This Does

- Arduino Leonardo reads an HC-SR04 ultrasonic sensor
- Sends distance data as a USB gamepad signal
- Strudel.cc reads the gamepad input
- **Move your hand → changes pitch in real time!**

---

## 🛠️ Parts You Need

| Part | Quantity |
| :--- | :--- |
| Arduino Leonardo | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| Breadboard | 1 |
| Jumper Wires | 4 |
| USB Cable | 1 |

---

## 🔌 Wiring

| HC-SR04 | Arduino Leonardo |
| :--- | :--- |
| VCC | 5V |
| GND | GND |
| TRIG | Pin 2 |
| ECHO | Pin 3 |

---

## 💻 Arduino Code

Upload this to your Leonardo:

```cpp
#include <Joystick.h>

const int trigPin = 2;
const int echoPin = 3;

Joystick_ Joystick;

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Read sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  // Constrain
  if (distance > 400) distance = 400;
  if (distance < 2) distance = 2;
  
  // Map to joystick (0-255)
  // Close = 255, Far = 0
  int axisValue = map(distance, 2, 400, 255, 0);
  
  // Send as gamepad
  Joystick.setXAxis(axisValue);
  Joystick.sendState();
  
  // Debug
  Serial.print("Dist: ");
  Serial.print(distance);
  Serial.print(" cm\tAxis: ");
  Serial.println(axisValue);
  
  delay(50);
}
```

### Library Install

If you get `'Joystick_' does not name a type`:

1. Download ZIP from: https://github.com/MHeironimus/ArduinoJoystickLibrary
2. Arduino IDE: **Sketch → Include Library → Add .ZIP Library**

If still broken, change `Joystick_ Joystick;` to `Joystick Joystick;`

---

## 🎹 Strudel Code

1. Open [Strudel.cc](https://strudel.cc) in Chrome
2. Click **Packages** tab → add **`@strudel/gamepad`**
3. Paste this:

```javascript
// Your Arduino is gamepad #0
const gp = gamepad(0);

// Map distance to pitch (100Hz to 2000Hz)
// Close = high pitch, Far = low pitch
let freq = gp.x1.range(100, 2000)

setCpm(140 / 4) // 140 BPM

// Drums
$: s("bd ~ bd ~")
   .stack(s("~ sd ~ sd"))
   .stack(s("hh ~ hh ~"))
   .gain(0.3)

// Melody controlled by distance
$: note("c4")
   .sound("vibraphone_soft")
   .freq(freq)
   .gain(0.9)
   .release(0.2)
```

### Note on Inversion

The code above gives: **Close = Higher Pitch, Far = Lower Pitch**.

If your sensor does the opposite and you want to invert it, use this instead:

```javascript
let freq = gp.x1.range(2000, 100) // Close = 100Hz, Far = 2000Hz
```

---

## 🚀 How It Works

| Step | What Happens |
| :--- | :--- |
| 1 | Arduino reads distance from sensor |
| 2 | Distance mapped to 0-255 (joystick value) |
| 3 | Leonardo sends as USB gamepad signal |
| 4 | Strudel reads gamepad using `@strudel/gamepad` |
| 5 | Distance controls pitch (freq) in real time |

---

## 🔧 Troubleshooting

**No sound?**
- Check volume
- Make sure code is running (click Play)
- Try a different sound: `"sawtooth"` or `"square"`

**No gamepad detected?**
- Test at: https://gamepad-tester.com/
- Try `const gp = gamepad(1);`

**Sensor not reading?**
- Check wiring (VCC, GND, TRIG, ECHO)
- Open Serial Monitor to see values

---

## 📚 Resources

- [Strudel.cc](https://strudel.cc) — Live coding music
- [Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary)

---

**Done! Move your hand and make music. 🎵**
