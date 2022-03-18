/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Servo.h"

// Arm servo enable
DigitalOut enable(PA_6);

// Servos of the arms
Servo base(PA_7,110,-100);        // 0 is center
Servo shoulder(PD_14,50,-50);     // 0 is center
Servo elbow(PD_15,100,-100);      // 5 is center
Servo wrist_vert(PE_9,110,-100);  // -3 is center
Servo wrist_rot(PE_11,100,-100);  // -5 is center
Servo gripper(PE_13,10,-50);      // -20 is center

static BufferedSerial serial_port(USBTX, USBRX);

int main() {
  // initialize serial
  serial_port.set_baud(115200);
  serial_port.set_format(8,BufferedSerial::None,1);

  // we read on byte a time
  char buf[1] = {0};

  // initialize arm
  enable.write(0);
  base.attach(0);
  shoulder.attach(0);
  elbow.attach(5);
  wrist_vert.attach(-3);
  wrist_rot.attach(-5);
  gripper.attach(-20);
  enable.write(1);
  int pos = 0; 
  while(1) {
    if(serial_port.read(buf,1)) {
      if(buf[0] == 'q')
        base.increasePos();
      if(buf[0] == 'a')
        base.decreasePos();
      if(buf[0] == 'w')
        shoulder.increasePos();
      if(buf[0] == 's')
        shoulder.decreasePos();
      if(buf[0] == 'e')
        elbow.increasePos();
      if(buf[0] == 'd')
        elbow.decreasePos();
      if(buf[0] == 'r')
        wrist_vert.increasePos();
      if(buf[0] == 'f')
        wrist_vert.decreasePos();
      if(buf[0] == 't')
        wrist_rot.increasePos();
      if(buf[0] == 'g')
        wrist_rot.decreasePos();
      if(buf[0] == 'y')
        gripper.increasePos();
      if(buf[0] == 'h')
        gripper.decreasePos();
    }
  } 
}
