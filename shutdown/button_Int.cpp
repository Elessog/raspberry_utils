#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/reboot.h>
#include <sys/reboot.h>
#include <malloc.h>
#include <stdlib.h>

#include "Timer.h"

#define BtnPin    7
#define LedPin    0

int *is_shutdown_engaged;
int button_pipe[2];
int pushed = 1;
Timer timer;


void myBtnISR(void)
{

  if (!timer.isRunning()){
    timer.start();
  }
  else
  {
      if(timer.timePassed()>2)
      {
          timer.stop();
          timer.start();
      }
      else
      {
          return;
      }
  }

  printf("Button is considered pushed\n");
  if (*is_shutdown_engaged){
      *is_shutdown_engaged=0;
  }
  else
  {
      char *c={'\0'};
      write(button_pipe[1],&c,1);
  }
}

void active_on_pushed(void)
{

    int light=1;
    int counter = 20;
    fd_set pdset;
    FD_ZERO(&pdset);
    FD_SET(button_pipe[0], &pdset);
    int max =button_pipe[0];
    int buffer[10];
    select(max+1, &pdset, NULL, NULL, NULL);

    read(button_pipe[0],buffer,10);

    *is_shutdown_engaged = 1;

    digitalWrite(LedPin, 1);
    printf("Shutdown is engaged you have 10 seconds to stop it\n");

    while(counter-- && *is_shutdown_engaged)
    {
        delay(1000);
        light=!light;
        digitalWrite(LedPin,light);
    }

    digitalWrite(LedPin,0);

    if (*is_shutdown_engaged)
    {
        sync();
        exit(EXIT_SUCCESS);
        //reboot(LINUX_REBOOT_CMD_POWER_OFF);
    }
    printf("Shutdown cancelled !!!\n");
}


int main(void)
{

        is_shutdown_engaged =(int*) malloc(sizeof(int));
        *is_shutdown_engaged = 0;

        timer = Timer();

        //init pipe for button
        pipe(button_pipe);

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

        if(wiringPiISR(BtnPin, INT_EDGE_FALLING, myBtnISR)){
		printf("setup ISR failed !");
		return 1;
	}

	pinMode(LedPin, OUTPUT);
        digitalWrite(LedPin, 0);
	while(1)
           active_on_pushed();

	return 0;
}
