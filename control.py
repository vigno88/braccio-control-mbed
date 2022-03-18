#!/usr/bin/env python3
import keyboard
import serial

# Change this to your need
SERIAL_PORT = "/dev/ttyACM0"

def main():
  print("Welcome to robot control program.\nSee README for more")
  ser = serial.Serial(SERIAL_PORT,115200)
  
  # Add listeners to all keys
  keyboard.add_hotkey('q', lambda: ser.write(b'q'))
  keyboard.add_hotkey('w', lambda: ser.write(b'w'))
  keyboard.add_hotkey('e', lambda: ser.write(b'e'))
  keyboard.add_hotkey('r', lambda: ser.write(b'r'))
  keyboard.add_hotkey('t', lambda: ser.write(b't'))
  keyboard.add_hotkey('y', lambda: ser.write(b'y'))
  keyboard.add_hotkey('a', lambda: ser.write(b'a'))
  keyboard.add_hotkey('s', lambda: ser.write(b's'))
  keyboard.add_hotkey('d', lambda: ser.write(b'd'))
  keyboard.add_hotkey('f', lambda: ser.write(b'f'))
  keyboard.add_hotkey('g', lambda: ser.write(b'g'))
  keyboard.add_hotkey('h', lambda: ser.write(b'h'))
  
  # infinite loop to keep program alive
  while True:
    pass

if __name__ == "__main__":
  main()
