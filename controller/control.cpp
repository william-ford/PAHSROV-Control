#include "joy.h"
#include "updates.h"
#include "pca9685.h"
#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

using namespace std;

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

int file_12c, fd;
char *filename = (char*)"/dev/i2c-1";

//g++ -o control joy.cpp updates.cpp test.cpp -g -O3 -Wall -Wextra -Wpedantic -std=c++11 -lwiringPi -lwiringPiPca9685

struct dual {
	int LFM;
	int RFM;
};

int calcTick(float impulseMs, int hertz) {
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 4.0f);
}

int xresolver(int trigstate, int joystate) {
	int state;
	if (trigstate) {
		state = 0;
	}
	
}

int trigsolver(int ltrig, int rtrig) {
	int solvedtrig = rtrig - ltrig;
	return solvedtrig;
}

double cubic (double n) {
	return (n*n*n);
}

int doubleRot (int drive, int trig = 0) {
	antidrive = (0 - drive)
	if (trig) {
		antidrive = 0.75 * drive;
	}
	return antidrive;
}

int shifter(int ref, int x) { //negative x for other motor
	int n;
	if (ref > 0)
		n = |x|;
	if (ref < 0)
		n = -|x|;
	return n;
}

int converter(int spec) {
	return (cubic((spec / 32767)) * 102) + 311;
}

int main(int argc, char const *argv[])
{
    mapped coords;

	wiringPiSetup();

	int statechk = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (statechk < 0) {
		printf("Error on setup!");
	}

	pca9685PWMReset(statechk);

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <device>\n", argv[0]);
        fprintf(stderr, "Example: %s /dev/input/js0\n", argv[0]);
        exit(0);
    }

    Joystick* joy = new Joystick(argv[1]);
	printf("Initializing...");
    while (true)
    {
        usleep(1000);
        joy->Update();

		coords = silmu(joy);
		pwmWrite(PIN_BASE , converter(shifter(coords.LJY, coords.LJX));
		pwmWrite(PIN_BASE + 1 , converter(shifter(coords.LJY, (0 - coords.LJX)));
		pwmWrite(PIN_BASE + 2 , converter(coords.RJX);
		pwmWrite(PIN_BASE + 3 , converter(doubleRot(coords.RJX, ));
    }

    return 0;
}
