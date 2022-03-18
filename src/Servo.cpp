#include <Servo.h>

#define MAP(v, minIn, maxIn, minOut, maxOut) ((v - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut)
#define DEG_TO_PULSE(d) MAP(d, SERVO_MIN_DEGREE, SERVO_MAX_DEGREE, SERVO_MIN_PULSE, SERVO_MAX_PULSE)
#define PULSE_TO_DEG(p) MAP(p, SERVO_MIN_PULSE, SERVO_MAX_PULSE, SERVO_MIN_DEGREE, SERVO_MAX_DEGREE)

Servo::Servo(PinName pin, int maxAngle, int minAngle) : 
  pulsePin(pin), maxDegree(maxAngle), minDegree(minAngle) {}

void Servo::attach(int startPos) {
    currentDeg = startPos;
    currentPulse = DEG_TO_PULSE(startPos);
    refreshTicker.attach(callback(this, &Servo::startPulse), 
      std::chrono::microseconds(SERVO_REFRESH_RATE_US));
}

void Servo::detach() {
    refreshTicker.detach();
    pulseTimer.detach();
}

void Servo::write(int pos) {
    if (pos >= maxDegree || pos <= minDegree)
      return;
    currentDeg = pos;
    currentPulse = DEG_TO_PULSE(pos);
}

int Servo::read() {
    return PULSE_TO_DEG(currentPulse);
}

void Servo::startPulse() {
    pulsePin = 1;
    pulseTimer.attach(callback(this, &Servo::endPulse),
      std::chrono::microseconds(currentPulse));
}

void Servo::endPulse() {
    pulsePin = 0;
}

void Servo::increasePos() {
    write(++currentDeg);
}
void Servo::decreasePos() {
    write(--currentDeg);
}
