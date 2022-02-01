#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <wiringPi.h>

#define PORT 8080
#define NUMB_CLIENTS 3

struct tCLIENT {
	int Socket;
	pthread_t pThread;
	unsigned char IpAddr[4];
	int flgSend;
	int flgWork;
} Clients[NUMB_CLIENTS];

int  NumbClients, flgSendAll, flgNewString;
char BufferToSent[200], MainString[200];

unsigned short int Outputs, Relays;
unsigned long Inputs, tmpInputs;

unsigned long CheckLongU[32] = {
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
};
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

void *ListenThread(void *);
void *ReadThread(void *);

void SetOutByte(unsigned char Byte) {
	unsigned char c = '\x01';
	for(int i = 0; i < 8; i++) {
		if(Byte & c)
			digitalWrite(PiOut[i], 1);
		else
			digitalWrite(PiOut[i], 0);
		c *= 2;
	}
}

unsigned char ReadInByte(void) {
	unsigned char c = 0;
	for(int i = 0; i < 8; i++) {
		if(digitalRead(PiIn[i]))
			c |= (unsigned char)CheckLongU[i];
	}
	return(c);
}

void ReadInputs(void) {
	digitalWrite(nE1, 1);
	digitalWrite( E2, 1);
	digitalWrite(nE3, 0);
	digitalWrite( A2, 1);
//	-	-	-	-	-	-	-	-	-	-
	digitalWrite( A0, 0);
	digitalWrite( A1, 0);
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	tmpInputs = (unsigned long)ReadInByte();
	digitalWrite(nE1, 1);
//	-	-	-	-	-	-	-	-	-	-
	digitalWrite( A0, 1);
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	tmpInputs += (unsigned long)ReadInByte() * 0x00000100;
	digitalWrite(nE1, 1);
//	-	-	-	-	-	-	-	-	-	-
	digitalWrite( A0, 0);
	digitalWrite( A1, 1);
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	tmpInputs += (unsigned long)ReadInByte() * 0x00010000;
	digitalWrite(nE1, 1);
//	-	-	-	-	-	-	-	-	-	-
	digitalWrite( A0, 1);
	digitalWrite( A1, 1);
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	tmpInputs += (unsigned long)ReadInByte() * 0x01000000;
	digitalWrite(nE1, 1);
}

void WriteRelays(void) {
	digitalWrite(nE1, 1);
	digitalWrite( E2, 1);
	digitalWrite(nE3, 0);
	digitalWrite( A0, 0);
	digitalWrite( A1, 0);
	digitalWrite( A2, 0);
	SetOutByte((unsigned char)Relays);
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	digitalWrite(nE1, 1);
	digitalWrite( A0, 1);
	SetOutByte((unsigned char)(Relays >> 8));
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	digitalWrite(nE1, 1);
}

void WriteOutputs(void) {
	digitalWrite(nE1, 1);
	digitalWrite( E2, 1);
	digitalWrite(nE3, 0);
	digitalWrite( A0, 0);
	digitalWrite( A1, 1);
	digitalWrite( A2, 0);
	SetOutByte((unsigned char)Outputs);
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	digitalWrite(nE1, 1);
	digitalWrite( A0, 1);
	SetOutByte((unsigned char)(Outputs >> 8));
	for(int i = 0; i < 10; i++)
		digitalWrite(nE1, 0);
	digitalWrite(nE1, 1);
}

void SentToAll(void) {
	for(int i = 0; i < NUMB_CLIENTS; i++)
		if(Clients[i].flgWork)
			Clients[i].flgSend = 1;
}

int NewThread(pthread_t *pPThread, void *Funct(), void *arg) {
	int rc;
	pthread_attr_t attr;
	void *status;
	pthread_attr_init(&attr);
	printf("main() : creating thread.\n");
	rc = pthread_create(pPThread, &attr, Funct, arg);
	if(rc) {
		printf("Error:unable to create thread, %u", rc);
		exit(-1);
	}
	pthread_attr_destroy(&attr);
}

void *ReadThread(void *nClient) {
	int NumbBit, NumbRecive, MyNumber, flgWhile;
	struct tCLIENT *MyClient;
	char rcvBuffer[1024] = { 0 };
	flgWhile = 1;
	MyNumber = *(int *)nClient;
	MyClient = &Clients[MyNumber];
	printf("Client#%u=%u.%u.%u.%u\n", MyNumber, MyClient->IpAddr[0], MyClient->IpAddr[1], MyClient->IpAddr[2], MyClient->IpAddr[3]);
	do {
		NumbRecive = recv(MyClient->Socket, rcvBuffer, 100, MSG_DONTWAIT);
		if(NumbRecive > 0) {
			rcvBuffer[NumbRecive] = 0;
			printf("%u = <%s> = %u ", MyNumber, rcvBuffer, NumbRecive);
			NumbBit = atoi(&rcvBuffer[1]);
			if(NumbBit < 0 || NumbBit > 15) {
				printf("WRONG NUMBER BIT.\n");
			} else if(rcvBuffer[0] == 'o') {
				Outputs ^= (unsigned short int)CheckLongU[NumbBit];
				WriteOutputs();
				printf("Outputs = %04X\n", Outputs);
				flgSendAll = 1;
			} else if(rcvBuffer[0] == 'r') {
				Relays &= ~(unsigned short int)CheckLongU[NumbBit];
				WriteRelays();
				printf("Relays  = %04X\n", Relays);
				flgSendAll = 1;
			} else if(rcvBuffer[0] == 'R') {
				Relays |= (unsigned short int)CheckLongU[NumbBit];
				WriteRelays();
				printf("Relays  = %04X\n", Relays);
				flgSendAll = 1;
			} else
				printf("WRONG COMMAND\n");
			memset(rcvBuffer, 0, 1024);
		} else if(errno != EAGAIN) {
			printf("errno=%u\n", errno);
			flgWhile = 0;
		}
		if(!MyClient->flgWork) {
			close(MyClient->Socket);
			flgWhile = 0;
		}
		if(MyClient->flgSend) {
			send(MyClient->Socket, BufferToSent, strlen(BufferToSent), MSG_DONTWAIT);
			MyClient->flgSend = 0;
		}
	} while(flgWhile);
	printf("Exit ReadThread #%u\n", MyNumber);
	pthread_exit(NULL);
}

void *ListenThread(void *pArg) {
	int serverFD;
	struct sockaddr_in addressL;
	int opt = 1;
	int AddrLenL = sizeof(addressL);
	char *hello = "Hello from server";
	// Creating socket file descriptor
	if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	// Forcefully attaching socket to the port 8080
	if(setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	addressL.sin_family = AF_INET;
	addressL.sin_addr.s_addr = INADDR_ANY;
	addressL.sin_port = htons(PORT);
	// Forcefully attaching socket to the port 8080
	if(bind(serverFD, (struct sockaddr *)&addressL, AddrLenL) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	do {
		int NewSocket, AddrLenN, NextClient;
		struct sockaddr addressN;
		AddrLenN = sizeof(addressN);
		if(listen(serverFD, 3) < 0) {
			perror("ERROR: listen");
			exit(EXIT_FAILURE);
		}
		if((NewSocket = accept(serverFD, &addressN, (socklen_t*)&AddrLenN)) < 0) {
			perror("ERROR: accept");
			exit(EXIT_FAILURE);
		}
		printf("Accepted\n"); 
		unsigned char *cp;
		cp = (unsigned char *)&addressN;
		for(int j = 0; j < AddrLenN; j++, cp++)
			printf("%u.", *cp);
		printf("\n=================================\n");
		for(NextClient = 0; NextClient < NUMB_CLIENTS && Clients[NextClient].Socket; NextClient++)
			;
		if(NextClient < NUMB_CLIENTS) {
			sprintf(BufferToSent, "%08X.%04X.%04X", Inputs, Outputs, Relays);
			Clients[NextClient].Socket = NewSocket;
			memcpy(Clients[NextClient].IpAddr, &((struct sockaddr_in *)&addressN)->sin_addr, 4);
			Clients[NextClient].flgWork = 1;
			Clients[NextClient].flgSend = 1;
			NewThread(&Clients[NextClient].pThread, ReadThread, &NextClient);
			NumbClients++;
		} else {
			printf("Too many DiO.\n");
			send(NewSocket, "! Too many DiO !", 17, 0);
			close(NewSocket);
		}
	} while(1);
	pthread_exit(NULL);
}

void *GetStringThread(void *argv) {
	char *cp;
	do {
		cp = fgets(MainString, 20, stdin);
		flgNewString = 1;
	} while(1);
	pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
	int i, flgExit, bit, OldBit, flgIO;
	sleep(1); //	sleep(15);
	memset(BufferToSent, 0, 199); //sizeof(BufferToSent));
	printf("\n---- DiO Server Start -------------------------\n");
//	if(!strcmp("no", argv[1])) {
//		flgIO = 0;
//	} else
//		flgIO = 1;
//	printf("flgIO = %u, argc = %u, %s, %s, %s\n", flgIO, argc, argv[0], argv[1], argv[2]);
	flgExit = 0;
	Outputs = 0;
	Relays = 0;
	Inputs = 0;
	NumbClients = 0;
	flgNewString = 0;
	OldBit = 0;
	pthread_t Lthread, GSThread;
	for(i = 0; i < 3; i++) {
		printf("sleep 1#%u\n", i);
		sleep(1);
	}
	if(wiringPiSetup() == -1) {
		printf("wrong wiringPiSetup\n");
		return(1);
	}
	printf("wiringPi Setup o.k.\n");
	sleep(1);
	for(i = 0; i < 8; i++)
		pullUpDnControl(PiIn[i], PUD_UP);
	for(i = 0; i < 8; i++) {
		pinMode(PiOut[i], OUTPUT);
		pinMode(PiIn[i], INPUT);
	}
	pinMode(nE3, OUTPUT);
	pinMode( E2, OUTPUT);
	pinMode(nE1, OUTPUT);
	pinMode( A2, OUTPUT);
	pinMode( A1, OUTPUT);
	pinMode( A0, OUTPUT);
	digitalWrite(nE1, 1);
	for(i = 0; i < 17; i++) {
		Outputs = (unsigned short int)CheckLongU[i];
		WriteOutputs();
		usleep(200000);
	}
	ReadInputs();
	Inputs = tmpInputs;
	printf("======================   START  =======================\n");
	sprintf(BufferToSent, "%08X %04X %04X", Inputs, Outputs, Relays);
	for(i = 0; i < NUMB_CLIENTS; i++)
		Clients[i].Socket = 0;
	NewThread(&Lthread, ListenThread, 0);
	if(flgIO)
		NewThread(&GSThread, GetStringThread, 0);
	do {
		if(flgNewString) {
			flgNewString = 0;
			if(!strcmp(MainString, "exit\n")) {
				printf("EXIT !!!\n");
				flgExit = 1;
			} else
				printf("===========================\nhelp: exit\n                     What ?\n");
		}
		ReadInputs();
		if(Inputs != tmpInputs) {
			Inputs = tmpInputs;
			flgSendAll = 1;
			printf("Inputs = %08X\n", Inputs);
		}
		if(flgSendAll) {
			printf("flgSendAll = %08X %04X %04X \n", Inputs, Outputs, Relays);
			sprintf(BufferToSent, "%08X %04X %04X", Inputs, Outputs, Relays);
			SentToAll();
			flgSendAll = 0;
		}
		usleep(100000);
	} while(!flgExit);
	printf("\n---- DiO Server Stop -------------------------\n");
	return(0);
}
