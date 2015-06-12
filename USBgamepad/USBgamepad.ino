/*
 * USBgamepad.ino
 *
 * Created: 6/11/2015 12:37:39 PM
 * Author: Tobias Nuss
 */ 


String inputString;


void toggleLed()
{
	for (int i=0; i<10; i++)
	{
		digitalWrite(13, HIGH);
		delay(100);
		digitalWrite(13, LOW);
		delay(100);
	}
}


void Update()
{
	inputString = "";         // a string to hold incoming data
	boolean stringComplete = false;  // whether the string is complete
	
	int cnt = 0;
	
	// get 20 characters
	while (cnt != 20) {
		if (Serial1.available()) {
			char inChar = (char)Serial1.read();
			inputString += inChar;
		}
		cnt++;
	}
	stringComplete = true;
	
	int start_value = Start(inputString);
	String pressedKey[8] = "";
	char *ptrToString = &inputString[start_value];
	
	for (int i=0; i<7; i++)
	{
		pressedKey[i] = ptrToString;
		ptrToString++;	
	}
	
	for (int i=0; i<7; i++)
	{
		Serial.print(pressedKey[i]);
	}
	
	

}

int Start(String arrayToCheck)
{
	char start[3] = {0x01, 0x7f, 0x7f};
	char *ptrToStart = start;
	int cnt = 0;
	bool ok = false;
	
	do 
	{	
		if (arrayToCheck[cnt] == *ptrToStart)
		{
			ptrToStart++;
			if (arrayToCheck[cnt+1] == *ptrToStart)
			{
				ptrToStart++;
				if (arrayToCheck[cnt+2] == *ptrToStart)
				{
					ok = true;
				}
				else 
					ok = false;
			}
		}
		cnt++;
	} while ( (ok = false) && (*ptrToStart<20) );

	return cnt;
}

void setup()
{
	Serial.begin(9600);
	Serial1.begin(9600); // Pins 0&1 - Rx&Tx
	while(!Serial);
	inputString.reserve(1000);
	pinMode(13, OUTPUT);
}


void loop()
{

	 //Update();
	

}
