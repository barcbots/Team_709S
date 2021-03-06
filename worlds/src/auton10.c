#include "lib.h"

void auto10() {
  calibrate();
  jerk();     // This is intended to drop and lock the intake
  // GO FORWARD & PICK UP 1-3 STARS (+ preload), BACK UP TO PREVIOUS POSITION

  // driveInchNoFix(27, 127); // Drives 38 inches forward at 127 power

  int startp = rGyros() - 3;
  int startEnc = encoderGet(lencoder);
  long power = 127;
  long lpower = power;
  long rpower = power;
  int tolerance = 2;
  float changer;
  while (encoderGet(lencoder) - startEnc < 19 * INCHESMULTIPLIER) { // 45
    changer = (abs(rGyros() - startp) - tolerance) * 15;
    if (rGyros() - startp > tolerance) {
      lpower = power - changer;
      rpower = power + changer;
    } else if (rGyros() - startp < -tolerance) {
      lpower = power + changer;
      rpower = power - changer;
    }
    driveSet(lpower, rpower);
    delay(50);
  }

  rLiftTo(0, POTHALF);

  driveInchNoFix(16, 90); // 6 14

  wLift(POTHALF * .6);

  driveInchNoFix(-30
    , 127); // -43
  {
    driveSet(100, 100);
    delay(50);
    driveStop();
  }
  driveInchNoFix(-11, 70);

  // TURN BACK OF ROBOT TO WALL, LIFT UP, HIT WALL, DUMP

  {
    turnToNoFix(85, 77);
    driveSet(-158, 158);
    delay(250);
    driveStop();
  }

  rLiftTo(900, POTTOP); // 650 550 600 675 735

  checknum = 3;

  timerReset(1);
  driveSet(-157, -157);
  while ((digitalRead(isWall) == 1 && digitalRead(isWall2) == 1) &&
         timer(1) < MAX_TIME_TO_WALL) { // Repeats until the button on the robot
                                        // is pressed
                                        // or 4 seconds pass
    delay(5);
    checknum = 4;
  }

  checknum = 5;

  driveStop(); // Stops the robot

  calibrate();
  delay(15000);
};
