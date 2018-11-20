 //pins for the LEDs:
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

const int redPin2 = 9;
const int greenPin2 = 10;
const int bluePin2 = 11;

#define REDPIN 3
#define GREENPIN 5
#define BLUEPIN 6

#define FADESPEED 5

void setup() {
// initialize serial:
Serial.begin(9600);

// make the pins outputs:
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);

pinMode(redPin2, OUTPUT);
pinMode(greenPin2, OUTPUT);
pinMode(bluePin2, OUTPUT);

Serial.print("Arduino control RGB LEDs Connected OK ( Sent From Arduinno Board )");
Serial.print('\n');
}

void loop() {

// if there's any serial available, read it:
while (Serial.available() > 0) {
 // look for the next valid integer in the incoming serial stream:
 int red = Serial.parseInt();
 int green = Serial.parseInt();
 int blue = Serial.parseInt();

 int red2 = Serial.parseInt();
 int green2 = Serial.parseInt();
 int blue2 = Serial.parseInt();

 // look for the newline. That's the end of your
 // sentence:
 if (Serial.read() == '\n') {
   // constrain the values to 0 - 255 and invert
   // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
  
   // This is for COMMON ANODE
   //red = 255 - constrain(red, 0, 255);
   //green = 255 - constrain(green, 0, 255);
   //blue = 255 - constrain(blue, 0, 255);
   red = constrain(red, 0, 255);
   green = constrain(green, 0, 255);
   blue = constrain(blue, 0, 255);
  
   red2 = constrain(red2, 0, 255);
   green2 = constrain(green2, 0, 255);
   blue2 = constrain(blue2, 0, 255);

   // fade the red, green, and blue legs of the LED:
   analogWrite(redPin, red);
   analogWrite(greenPin, green);
   analogWrite(bluePin, blue);
  
   analogWrite(redPin2, red2);
   analogWrite(greenPin2, green2);
   analogWrite(bluePin2, blue2);

   // print the three numbers in one string as hexadecimal:
    Serial.print("Data Response : ");
   Serial.print(red, HEX);
   Serial.print(green, HEX);
   Serial.println(blue, HEX);
 }
}
}