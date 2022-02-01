#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

#define ESC 0x1B

		 //bit  D0  D1  D2  D3  D4  D5  D6  D7 
		 //pin   3   5   7   8  10  11  12  13
int PiOut[8] = { 8,  9,  7, 15, 16,  0,  1,  2 }; //wiringPi
		 //bit Ri0 Ri1 Ri2 Ri3 Ri4 Ri5 Ri6 Ri7 
		 //pin  22  24  26  28  32  36  38  40
int PiIn[8]  = { 6, 10, 11, 31, 26, 27, 28, 29 }; //wiringPi

int nE3 = 30; // pin 27
int  E2 = 21; // pin 29
int nE1 = 22; // pin 31
int  A2 = 23; // pin 33
int  A1 = 24; // pin 35
int  A0 = 25; // pin 37

int i, digit;
char String[1000], *cp;
unsigned char Bits[8] = { '\x01', '\x02', '\x04', '\x08', '\x10', '\x20', '\x40', '\x80' };

unsigned char ReadInByte(void) {
	unsigned char c = 0;
	for(int i = 0; i < 8; i++) {
		if(digitalRead(PiIn[i]))
			c |= Bits[i];
	}
	return(c);
}

int main(int argc, char const *argv[]) {
	printf("\n---- TestDiO Raspberry Start -----\n");
	if(wiringPiSetup() == -1) {
		printf("wrong wiringPiSetup\n");
		return(1);
	}
	printf("wiringPi Setup o.k.\n");
	for(i = 0; i < 8; i++) {
		pinMode(PiOut[i], OUTPUT);
		pinMode(PiIn[i], INPUT);
	}
	for(i = 0; i < 8; i++)
		pullUpDnControl(PiIn[i], PUD_UP);
	pinMode(nE3, OUTPUT);
	pinMode( E2, OUTPUT);
	pinMode(nE1, OUTPUT);
	pinMode( A2, OUTPUT);
	pinMode( A1, OUTPUT);
	pinMode( A0, OUTPUT);
	printf("\nPres empty string to read inputs, or :\n");
	printf("exit, A0=x, A1=x, A2=x, E1=x, E2=x, E3=x, D0...D7=x, where: x=0 or 1\n");
	do {
		cp = fgets(String, 100, stdin);
		for(i = 0; String[i] && String[i] != '\n'; i++)
			;
		String[i] = 0;
		if('a' <= String[0] && String[0] <= 'z')
			String[0] &= '\x5F';
		if('a' <= String[1] && String[1] <= 'z')
			String[1] &= '\x5F';
		if('a' <= String[2] && String[2] <= 'z')
			String[2] &= '\x5F';
		if('a' <= String[3] && String[3] <= 'z')
			String[3] &= '\x5F';
		if(digit = String[3] - '0')
			digit = 1;
		if       (!strncmp(String, "A0=", 3)) {
			digitalWrite(A0, digit);
			printf("set A0 = %d\n", digit);
		} else if(!strncmp(String, "A1=", 3)) {
			digitalWrite(A1, digit);
			printf("set A1 = %d\n", digit);
		} else if(!strncmp(String, "A2=", 3)) {
			digitalWrite(A2, digit);
			printf("set A2 = %d\n", digit);
		} else if(!strncmp(String, "E1=", 3)) {
			digitalWrite(nE1, digit);
			printf("set E1 = %d\n", digit);
		} else if(!strncmp(String, "E2=", 3)) {
			digitalWrite(E2, digit);
			printf("set E2 = %d\n", digit);
		} else if(!strncmp(String, "E3=", 3)) {
			digitalWrite(nE3, digit);
			printf("set E3 = %d\n", digit);
		} else if(!strncmp(String, "D0=", 3)) {
			digitalWrite(PiOut[0], digit);
			printf("set D0 = %d\n", digit);
		} else if(!strncmp(String, "D1=", 3)) {
			digitalWrite(PiOut[1], digit);
			printf("set D1 = %d\n", digit);
		} else if(!strncmp(String, "D2=", 3)) {
			digitalWrite(PiOut[2], digit);
			printf("set D2 = %d\n", digit);
		} else if(!strncmp(String, "D3=", 3)) {
			digitalWrite(PiOut[3], digit);
			printf("set D3 = %d\n", digit);
		} else if(!strncmp(String, "D4=", 3)) {
			digitalWrite(PiOut[4], digit);
			printf("set D4 = %d\n", digit);
		} else if(!strncmp(String, "D5=", 3)) {
			digitalWrite(PiOut[5], digit);
			printf("set D5 = %d\n", digit);
		} else if(!strncmp(String, "D6=", 3)) {
			digitalWrite(PiOut[6], digit);
			printf("set D6 = %d\n", digit);
		} else if(!strncmp(String, "D7=", 3)) {
			digitalWrite(PiOut[7], digit);
			printf("set D7 = %d\n", digit);
		} else if(!strlen(String)) {
			printf("inByte = %02X\n", ReadInByte());
		} else {
			printf("String = \"%s\" ???\n", String);
		}
	} while(strcmp(String, "EXIT"));
	printf("EXIT.\n");
}
