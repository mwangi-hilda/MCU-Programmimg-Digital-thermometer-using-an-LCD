# AVR Digital Thermometer with LM35 & 16x2 LCD
This project implements a **Digital Thermometer** using an **LM35 analog temperature sensor** and a **16x2 LCD**, controlled by an **ATmega2560 microcontroller**. The system reads temperature values using the internal ADC, converts them to Celsius, and displays them on the LCD in real time.

---

## Project Overview

- Displays real-time temperature like: `Temp: 28.4 C`
- Uses **ADC0** for analog readings from LM35
- Uses **4-bit mode** to communicate with LCD (to save pins)
- Written in **AVR C++ (GCC)** and compiled in **Microchip Studio**
- Includes **Proteus simulation** (.pdsprj)

---

## Hardware Requirements

| Component        | Quantity | Notes                                 |
|------------------|----------|----------------------------------------|
| ATmega328P       | 1        | Microcontroller (Arduino UNO chip)     |
| LM35             | 1        | Analog temp sensor (10mV/°C)           |
| 16x2 LCD         | 1        | HD44780-compatible                     |
| 10k Potentiometer| 1        | Controls LCD contrast (V0 pin)         |
| 5V Power Source  | 1        | For MCU, LCD, and LM35                 |

---

## How It Works

1. **LM35** produces 10mV for every °C.
2. **ADC** converts this voltage to a digital value (0–1023 for 0–5V).
3. Code converts the ADC result to temperature:
   ```c
   voltage = adc_value * 5.0 / 1024.0;
   temperature = voltage * 100;

  ## Proteus Set-Up
  <img width="882" height="637" alt="image" src="https://github.com/user-attachments/assets/0b7faed5-37ce-4077-a6c6-6890c8cf5fd2" />

