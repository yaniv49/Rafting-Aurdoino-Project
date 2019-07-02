#include <RCSwitch.h>
#include <Keyboard.h>
RCSwitch mySwitch = RCSwitch();
#define LED LED_BUILTIN
unsigned int val;
int rightValue = 0;
int leftValue = 2;
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  pinMode(LED,OUTPUT);
}

void loop() {
  if (mySwitch.available()) {
     rightValue = (mySwitch.getReceivedValue() & 12) >> 2;
 while(rightValue == 0)
        {
        Serial.println("Right - Waiting"); 
          rightValue = (mySwitch.getReceivedValue() & 12) >> 2;
          delay(3);
        }
     
           leftValue = (mySwitch.getReceivedValue() & 3);
        while(leftValue == 0)
        {
            Serial.println("Left - Waiting"); 
          leftValue = (mySwitch.getReceivedValue() & 3);
           delay(3);
        }

        if(rightValue == 2 && leftValue == 2)
        {
   Keyboard.press((char) 32);
      delay(1250);
      Keyboard.release((char) 32);
        }
        else
        if(rightValue == 2 && leftValue == 1)
        {
                Keyboard.press(KEY_RIGHT_ARROW);
      delay(1250);
      Keyboard.release(KEY_RIGHT_ARROW);
        }
        else
        if(rightValue == 1 && leftValue == 2)
        {
                Keyboard.press(KEY_LEFT_ARROW);
      delay(1250);
      Keyboard.release(KEY_LEFT_ARROW);
        }
  
      Serial.print("Right Mashot: ");
      Serial.println( rightValue ); 

       Serial.print("Left Mashot ");
        Serial.println( leftValue );
        mySwitch.resetAvailable();
        
        delay(20);
  }
}


/*

        Serial.println("GO RIGHT!!!!!!!!!!!!!!");
       //  Keyboard.press(KEY_RIGHT_ARROW);
         delay(1250);
 // Keyboard.release(KEY_RIGHT_ARROW);

*/
