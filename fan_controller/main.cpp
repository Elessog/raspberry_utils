#include <wiringPi.h>
#include <stdio.h>
#include <malloc.h>

#define RelayPin      2
#define TEMPERATURE_SOURCE "/sys/class/thermal/thermal_zone0/temp"
#define MAX_TEMP 45
#define MIN_TEMP 30

FILE *fp;

void get_temperature(double *temperature)
{
    int temperature_m;
    int n_returned;

    fp=fopen(TEMPERATURE_SOURCE,"r");

    if (fp==NULL)
        return;

    n_returned = fscanf(fp,"%d",&temperature_m);

   if (n_returned != 1)
        return;

    fclose(fp);
    *temperature = temperature_m/1000.0;
}

int main(void)
{

    double *temperature = (double*) malloc(sizeof(double));
    *temperature = 34;

    if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return 1;
    }

    pinMode(RelayPin, OUTPUT);

    while(1){

        get_temperature(temperature);
//        printf("Temperature is %f\n",*temperature);

        if (*temperature < MIN_TEMP)
            digitalWrite(RelayPin, LOW);
        else if (*temperature > MAX_TEMP)
            digitalWrite(RelayPin, HIGH);

        delay(5000);

    }


    free(temperature);

    return 0;
}
