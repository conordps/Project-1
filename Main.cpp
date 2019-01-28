#include <Arduino.h>
//#include <Serial.h>

#define t_D13 5
#define t_ON 10
#define t_OFF 15
#define t_BLINK 20
#define t_LED 25
#define t_GREEN 30
#define t_RED 35
#define t_SET 40
#define t_STATUS 45
#define t_LEDS 50
#define t_VERSION 55
#define t_HELP 60

const byte numBytes = 128;
const byte numCommands = 15;
const byte numEntries = 4;
byte receivedBytes[numBytes];
byte wordArray[numCommands][numEntries];
byte commandArray[numEntries];
boolean newDataFlag = false;

byte receiveMessage(byte numReceived);
void showNewData(byte numReceived);
void parseArray(byte numReceived);

void setup(){
	Serial.begin(9600);
	Serial.println("<Arduino is ready>");
	pinMode(13, OUTPUT);

}


void loop(){

	byte numReceived = 0;
	digitalWrite(13, HIGH); delay(1000);
	digitalWrite(13, LOW); delay(1000);
	numReceived = receiveMessage(numReceived);
	showNewData(numReceived);
	parseArray(numReceived);
}

byte receiveMessage(byte numReceived){

	static boolean receiveInProgress = false;
	static byte index = 0;
	byte carriageReturn = 13;
	byte rb;

	while(Serial.available() > 0 && newDataFlag == false){

		rb = Serial.read();
		
		if(rb > 0){
                     receiveInProgress = true;
                }

		
		if(receiveInProgress == true){
		
			if( rb != carriageReturn){
				receivedBytes[index] = rb;
				index++;
				if(index >= numBytes){
					index = numBytes -1;
				}
			}
			else{
				receivedBytes[index] = '\0';
				receiveInProgress = false;
				numReceived = index;
				index = 0;
				newDataFlag = true;
			}
		}
		
	}
	return numReceived;
}

void showNewData(byte numReceived){

	if(newDataFlag == true){
		Serial.print("This just in...!");
		for(byte n = 0; n < numReceived; n++){
			Serial.print(char(receivedBytes[n]));
			Serial.print(' ');
		}
		Serial.println();
		newDataFlag = false;	
	}
	return;
}

void setupCommandList(){

	wordArray[0][0] = 'D';
	wordArray[0][1] = '1';
	wordArray[0][2] = 3;
	wordArray[0][3] = t_D13;

	wordArray[1][0] = 'O';
	wordArray[1][1] = 'N';
	wordArray[1][2] = 2;
	wordArray[1][3] = t_ON;

	wordArray[2][0] = 'O';
	wordArray[2][1] = 'F';
	wordArray[2][2] = 3;
	wordArray[2][3] = t_OFF;
	
	wordArray[3][0] = 'B';
	wordArray[3][1] = 'L';
	wordArray[3][2] = 5;
	wordArray[3][3] = t_BLINK;
	
	wordArray[4][0] = 'L';
	wordArray[4][1] = 'E';
	wordArray[4][2] = 3;
	wordArray[4][3] = t_LED;
	
	wordArray[5][0] = 'R';
	wordArray[5][1] = 'E';
	wordArray[5][2] = 3;
	wordArray[5][3] = t_RED;
	
	wordArray[6][0] = 'G';
	wordArray[6][1] = 'R';
	wordArray[6][2] = 5;
	wordArray[6][3] = t_GREEN;

	wordArray[7][0] = 'S';
	wordArray[7][1] = 'E';
	wordArray[7][2] = 3;
	wordArray[7][3] = t_SET;
	
	wordArray[8][0] = 'S';
	wordArray[8][1] = 'T';
	wordArray[8][2] = 6;
	wordArray[8][3] = t_STATUS;
	
	wordArray[9][0] = 'L';
	wordArray[9][1] = 'E';
	wordArray[9][2] = 4;
	wordArray[9][3] = t_LEDS;

	wordArray[10][0] = 'V';
	wordArray[10][1] = 'E';
	wordArray[10][2] = 7;
	wordArray[10][3] = t_VERSION;
	
	wordArray[11][0] = 'H';
	wordArray[11][1] = 'E';
	wordArray[11][2] = 4;
	wordArray[11][3] = t_HELP;
	return;
}
void parseArray(byte numReceived){
	
	byte one = 1;
	byte two = 2;
	if(numReceived > 0){
	for(byte n = 0; n < numReceived; n++){
			if((char(receivedBytes[n]) == wordArray[0][0])  
			&& (char(receivedBytes[n + one]) == wordArray[0][1]) 
			&& (char(receivedBytes[n + two]) == wordArray[0][2]) 	
			){Serial.print("Found it!\n");}
			
	}
	}
	else{
		Serial.print("No array values to parse.\n");
	}		
}

