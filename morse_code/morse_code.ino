/*
 * This introductory project converts a given string into morse code.
 * The Built-in LED will blink along with an actual LED and sound.
 */
#include <Arduino.h>

struct MorseMapping {
    char letter;
    String code;
};

MorseMapping morse_map[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}, 
    {'1', ".---"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--.."}, {'8', "---.."},
    {'9', "----."}, {'0', "-----"}
};
 
void setup() {
  /* // This is to print the map to make sure it works.
  Serial.begin(4800);
    // Print the letter and Morse code for each mapping
    for (size_t i = 0; i < sizeof(morse_map) / sizeof(morse_map[0]); ++i) {
        Serial.print("Letter: ");
        Serial.print(morse_map[i].letter);
        Serial.print(", Morse Code: ");
        Serial.println(morse_map[i].code);
    }
  */
  // Initailize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(4800);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Start by implementing the LED.
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on (HIGH is the voltage level)
  delay(500);                      // Wait for a second.
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off (LOW is the voltage level)
  delay(500);

  if (Serial.available()) {
    char user_input[50]; // Define a character array to store the input string
    int index = 0; // Index to keep track of the position in the array

    // Read characters from the serial buffer until a newline ('\n') character is received or the array is full
    while (Serial.available() && index < 49) {
        char incoming_char = Serial.read(); // Read the next character from the serial buffer
        user_input[index] = incoming_char; // Store the character in the array
        index++; // Move to the next position in the array
    }
    user_input[index] = '\0'; // Null-terminate the string

    // Loop through the characters in the input string and print each character
    for (int i = 0; user_input[i] != '\0'; i++) {
        char current_char = user_input[i];
        Serial.print(current_char);
    }
    Serial.println(); // Print a newline character to move to the next line
  }
}
