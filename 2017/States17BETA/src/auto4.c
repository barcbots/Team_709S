#include "constants.h"
#include "ethanlib.h"

void auto4() {
  gyroReset(gyro);
  encoderReset(lencoder);
  encoderReset(rencoder);
  jerk();     // This is intended to drop and lock the intake
  delay(400); // waits 440 milliseconds for the intake to drop (AND LOCK)
  // GO FORWARD & PICK UP 1-3 STARS (+ intake), BACK UP TO PREVIOUS POSITION
  driveInchNoFix(24, 127); // Drives 24
  arr[0] = 0;
  arr[1] = POTHALF;
  liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                            TASK_PRIORITY_DEFAULT);
  driveInch(13, 127); // 6
  mutexTake(potMutex, -1);
  int j = analogReadCalibrated(POT);
  mutexGive(potMutex);
  while (j < POTHALF / 1.5) {
    mutexTake(potMutex, 5);
    j = analogReadCalibrated(POT);
    mutexGive(potMutex);
    delay(1);
  }
  driveInch(-22, 127); // Drives 38 inches backward at 63 power
  // TURN BACK OF ROBOT TO WALL< LIFT UP, HIT WALL, DUMP
  // turnNoFix(2, 127);        // Turns 83 degrees to the right at 40 power
  // turn(88, 55);
  smartTurn(90, 100);
  driveSet(-127, -127); // Sets the drive to go backwards at 70 power
  timerReset(0);
  arr[0] = 600; // 300
  arr[1] = POTTOP + 50;
  liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                            TASK_PRIORITY_DEFAULT);
  TaskHandle gyroResetIn = taskCreate(gyroResetAfter, TASK_DEFAULT_STACK_SIZE,
                                      (void *)1000, TASK_PRIORITY_DEFAULT);
  while (digitalRead(isWall) == 1 && digitalRead(isWall2) == 1 &&
         timer(0) < 4000) { // Repeats until the button on the robot is pressed
                            // or 4 seconds pass
    delay(1);
  }
  driveSet(0, 0); // Stops the robot
  mutexTake(potMutex, -1);
  j = analogReadCalibrated(POT);
  mutexGive(potMutex);
  while (j < POTTOP) {
    mutexTake(potMutex, 5);
    j = analogReadCalibrated(POT);
    mutexGive(potMutex);
    delay(1);
  }
  delay(600);
  // LIFT TO BOTTOM, TURN & DRIVE FORWARD (GET CUBE) LIFT UP
  arr[0] = 0;
  arr[1] = POTBOTTOM; // Takes the lift down to the bottom
  liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                            TASK_PRIORITY_DEFAULT);
  delay(1500);
  /*
  liftSet(-52);
  delay(100);
  */
  liftSet(LIFTZERO);
  smartTurnTo(-35, 127); // -43
  driveInchNoFix(24, 127); // 25
  arr[0] = 600;
  arr[1] = POTHALF + 200;
  liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                            TASK_PRIORITY_DEFAULT);
  driveInch(10, 127);
  //
  delay(250);
  turnNoFix(20, 70);
  driveSet(-127, -127);
  timerReset(0);
  arr[0] = 0;
  arr[1] = POTTOP; // Brings the lift to the top
  liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                            TASK_PRIORITY_DEFAULT);
  while (digitalRead(isWall) == 1 && digitalRead(isWall2) == 1 &&
         timer(0) < 2000) { // Repeats until the bumper sensor on the robot is
                            // pressed or 3 seconds pass
    delay(1);
  }
  driveStop();
  gyroReset(gyro);
  encoderReset(lencoder);
  encoderReset(rencoder);
  /////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////
  liftTo(POTHALF + 200);
  smartTurn(27, 90);

  driveInch(50, 127);
  smartTurn(30, 90);
  delay(4000);
  arr[0] = 600;
  arr[1] = POTTOP + 50; // Brings the lift to the top
  timerReset(0);
  driveSet(-127, -127);
  liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                            TASK_PRIORITY_DEFAULT);
  while (digitalRead(isWall) == 1 && digitalRead(isWall2) == 1 &&
         timer(0) < 4000) { // Repeats until the bumper sensor on the robot is
                            // pressed or 3 seconds pass
    delay(1);
  }
  delay(500);
  driveStop();
  mutexTake(potMutex, -1);
  j = analogReadCalibrated(POT);
  mutexGive(potMutex);
  while (j < POTTOP) {
    mutexTake(potMutex, 5);
    j = analogReadCalibrated(POT);
    mutexGive(potMutex);
    delay(1);
  }
  delay(600);
  liftTo(POTHALF + 200);

  for (size_t iii = 0; iii < 2; iii++) {
    driveInch(50, 127);
    delay(4000);
    arr[0] = 1000;
    timerReset(0);
    arr[1] = POTTOP + 50; // Brings the lift to the top
    driveSet(-127, -127);
    liftToHandle = taskCreate(liftToTask, TASK_DEFAULT_STACK_SIZE, (void *)arr,
                              TASK_PRIORITY_DEFAULT);
    while (digitalRead(isWall) == 1 && digitalRead(isWall2) == 1 &&
           timer(0) < 2000) { // Repeats until the bumper sensor on the robot is
                              // pressed or 3 seconds pass
      delay(1);
    }
    delay(500);
    driveStop();
    mutexTake(potMutex, -1);
    j = analogReadCalibrated(POT);
    mutexGive(potMutex);
    while (j < POTTOP) {
      mutexTake(potMutex, 5);
      j = analogReadCalibrated(POT);
      mutexGive(potMutex);
      delay(1);
    }
    delay(600);
    liftTo(POTHALF + 200);
  }
  liftTo(POTBOTTOM);
}
