# SMS_QT

**SMS_QT** is a **simple graphical SMS client** for **serial-based GSM modems**, built using the **Qt framework**.

It provides a lightweight interface for sending and receiving SMS messages over AT-command–compatible modems connected via serial ports.

---

## Features

- Works with **serial GSM modems**
- Send and receive SMS using **AT commands**
- Simple and minimal **Qt-based GUI**
- Suitable for embedded and desktop systems
- No external services or network dependencies

---

## Architecture Overview

- **Frontend:** Qt Widgets GUI
- **Inside:** Serial communication layer
- **Protocol:** AT command interface for GSM modems

The application communicates directly with the modem via a serial port and handles SMS operations locally.

---

## Building

### Requirements

- Qt SDK (Qt5 or Qt6)
- CMake
- C++ compiler (GCC / Clang)
- Serial GSM modem (for runtime testing)

---

### Build Steps

```bash
mkdir build
cd build
cmake ..
make
