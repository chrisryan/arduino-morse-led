/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int pulse = 100;

char message[] = "ARDUINO IN MORSE";

// Store the morse code letters in 5 byte increments
// 1 is a dot, 3 is a dash, 0 is no char
int dotdash[] = {
  3, 3, 3, 3, 3, // 0 -----
  1, 3, 3, 3, 3, // 1 .----
  1, 1, 3, 3, 3, // 3 ..---
  1, 1, 1, 3, 3, // 3 ...--
  1, 1, 1, 1, 3, // 4 ....-
  1, 1, 1, 1, 1, // 5 .....
  3, 1, 1, 1, 1, // 6 -....
  3, 3, 1, 1, 1, // 7 --...
  3, 3, 3, 1, 1, // 8 ---..
  3, 3, 3, 3, 1, // 9 ----.
  0, 0, 0, 0, 0, // :
  0, 0, 0, 0, 0, // ;
  0, 0, 0, 0, 0, // <
  0, 0, 0, 0, 0, // =
  0, 0, 0, 0, 0, // >
  0, 0, 0, 0, 0, // ?
  0, 0, 0, 0, 0, // @
  1, 3, 0, 0, 0, // A .-
  3, 1, 1, 1, 0, // B -...
  3, 1, 3, 1, 0, // C -.-.
  3, 1, 1, 0, 0, // D -..
  1, 0, 0, 0, 0, // E .
  1, 1, 3, 1, 0, // F ..-.
  3, 3, 1, 0, 0, // G --.
  1, 1, 1, 1, 0, // H ....
  1, 1, 0, 0, 0, // I ..
  1, 3, 3, 3, 0, // J .---
  3, 1, 3, 0, 0, // K -.-
  1, 3, 1, 1, 0, // L .-..
  3, 3, 0, 0, 0, // M --
  3, 1, 0, 0, 0, // N -.
  3, 3, 3, 0, 0, // O ---
  1, 3, 3, 1, 0, // P .--.
  3, 3, 1, 3, 0, // Q --.-
  1, 3, 1, 0, 0, // R .-.
  1, 1, 1, 0, 0, // S ...
  3, 0, 0, 0, 0, // T -
  1, 1, 3, 0, 0, // U ..-
  1, 1, 1, 3, 0, // V ...-
  1, 3, 3, 0, 0, // W .--
  3, 1, 1, 3, 0, // X -..-
  3, 1, 3, 3, 0, // Y -.--
  3, 3, 1, 1, 0, // Z --..
  0, 0, 0, 0, 0 // null
};
#define MAXDOTDASH (sizeof(dotdash)/sizeof(int))

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  morse('5');
  endword(); 
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; message[i] != '\0'; i++) {
    morse(message[i]);
    space();
  }
  endword();
}

void morse(char letter) {
  if (letter == ' ') {
     return endword();
  }

  int index = (letter - '0') * 5;
  if (index < 0 || index >= MAXDOTDASH) {
    return;
  }

  for(int i = index; i < index + 5; i++) {
    if (dotdash[i]) {
      glow(dotdash[i]);
    }
  }
}

void dot() {
  glow(1);
}

void dash() {
  glow(3);
}

void glow(int width) {
  digitalWrite(led, HIGH);
  delay(pulse * width);
  digitalWrite(led, LOW);
  delay(pulse * 1);
}

void space() {
  delay(pulse * 2);
}

void endword() {
  delay(pulse * 4);
}

