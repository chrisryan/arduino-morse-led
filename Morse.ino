/*
 * Morse LED
 * Turns on an LED on/off using morse code to communicate a message.
 *
 * Licensed under MIT
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// number of milliseconds that a pulse is for displaying the morse code
// a dot is one pulse in time.
int pulse = 100;

// the message you want to display
// must be A-Z and space
char message[] = "Arduino In Morse";

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

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  // DEBUG: at startup blink out the morse signal for 5
  //        which is 5 dot's and easy to understand.
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

  letter = toupper(letter);
  
  int index = (letter - '0') * 5;
  if (index < 0 || index >= MAXDOTDASH) {
    return; // ignore any input that is outside out range
  }

  for(int i = index; i < index + 5; i++) {
    if (dotdash[i]) {
      glow(dotdash[i]);
    }
  }
}

// Light the LED for the specified pulse width and then wait for 1 pulse
// A dot is 1 pulse long, a dash is 3 pulses long.
void glow(int width) {
  digitalWrite(led, HIGH);
  delay(pulse * width);
  digitalWrite(led, LOW);
  delay(pulse * 1);
}

// A space is 3 pulses long but all dots/dashes are followed by
// a single pulse already so we only need the difference.
void space() {
  delay(pulse * 2);
}

// An endword is 7 pulses long but all character sequences are
// followed by a space so we only need the difference.
void endword() {
  delay(pulse * 4);
}

