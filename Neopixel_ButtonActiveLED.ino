#include <Adafruit_NeoPixel.h>

#define PIN            D2
#define NUMPIXELS      60

int buttonPin = D4;          // digital pin for button
int delayval = 7;            // delay between roller

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const uint32_t offColor = pixels.Color(255, 0, 0);

void setup() {
  Serial.begin(9600); // send and receive at 9600 baud
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show(); // set no color
  pixels.setBrightness(50);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    staticColor(offColor);
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      targetHit(pixels.Color(0, 255, 0), delayval);
      Serial.print("Target hit: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void targetHit(uint32_t c, uint8_t wait) {
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, c);

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(wait); // Delay for a period of time (in milliseconds).
  }
  delay(250);
  staticColor(c);
  delay(75);
  staticColor(offColor);
  delay(75);
  staticColor(c);
  delay(75);
  staticColor(offColor);
  delay(75);
  staticColor(c);
  delay(75);
  staticColor(offColor);
  delay(75);
  staticColor(c);

  //pixels off
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, offColor);

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(wait); // Delay for a period of time (in milliseconds).
  }
}

void staticColor(uint32_t c) {
    for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, c);  
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}
