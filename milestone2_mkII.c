#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, dgtl3,  button3,        sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port2,           motor2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           motor3,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           motor4,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// WHEN YOU FINISH EACH EXERCISE, INCREMENT THIS VALUE

bool button1_pushed; //flag to store button1 input
bool button2_pushed; //flag to store button2 input
bool button3_pushed;

/* monitorInput()
*
*  Used to flag button inputs
*       - this avoids errors caused by program recognizing input, taking action, and
*         reading input again before button is released
*/
void monitorInput()
{
  if(SensorValue(button1) && !button1_pushed)
  {
    button1_pushed = true;
  }

  if(SensorValue(button2) && !button2_pushed)
  {
    button2_pushed = true;
  }

  if(SensorValue(button3) && !button3_pushed)
  {
    button3_pushed = true;
  }
}

void exercise_3()
{

	enum T_exercise3_state {
		STOPPED = 0,
		FORWARDS,
		TURN,
		DROP,
	};

	T_exercise3_state exercise3_state = STOPPED;

	while(true)
	{
	  monitorInput();

	switch(exercise3_state){
		case STOPPED:
		motor[motor1] = 0;
		motor[motor2]=0;
		motor[motor4] = 0;
		if(button1_pushed){
		exercise3_state = FORWARDS;
		resetMotorEncoder(motor1);
	}
	if(button2_pushed){
		exercise3_state = TURN;
		resetMotorEncoder(motor1);
	}

	if(button3_pushed){
	exercise3_state = DROP;
}
	break;

	case FORWARDS:
	motor[motor1] = 25;
	motor[motor2] = 25;
	if(abs(getMotorEncoder(motor1)) > 1750){
	exercise3_state = STOPPED;
	button1_pushed = false;
}

	break;

	case TURN:
	motor[motor1] = 50;
	motor[motor2] = -50;
	if(abs(getMotorEncoder(motor1)) > 250){
	exercise3_state = STOPPED;
	button2_pushed = false;
}

	break;

	case DROP:
	motor[motor4] = 20;
	wait1Msec(2000);

	exercise3_state = STOPPED;
	button3_pushed = false;

	break;

}
      /* INSERT CODE HERE
      * - make sure EXERCISE_NUMBER is set to 3
		  */


  }//end while

}//end exercse_3


task main()
{
	button1_pushed = button2_pushed = false;

       exercise_3();

}// end main
