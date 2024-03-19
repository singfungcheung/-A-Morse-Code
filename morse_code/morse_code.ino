/*
 * This introductory project converts a given string into morse code.
 * The Built-in LED will blink along with an actual LED and sound.
 */
#include <Arduino.h>
#include <string.h>

#define RED 3
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

const String findMorseCode(char input, char morse_input[50]) {
    // Loop through the morse code map.
    for (int i = 0; i < sizeof(morse_map) / sizeof(morse_map[0]); i++) {
        // Check if the input character matches the current character in the map.
        if (morse_map[i].letter == input) {
            // Return the corresponding morse code.
            for (int j = 0; j < sizeof(morse_map[i].code) / sizeof(morse_map[i].code[0]); j++) {
              morse_input[j] = morse_map[i].code[j];
            }
            return morse_map[i].code;
        }
    }
}

void clearBuffer(char* user_input) {
    for (int i = 0; i < 50; i++) {
        user_input[i] = '\0';
    }
}

unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval_long = 1000;  // interval at which to blink (milliseconds)
const long interval_short = 500;  // interval at which to blink (milliseconds)

// constants won't change. Used here to set a pin number:
const int ledPin = LED_BUILTIN;  // the number of the LED pin

// Variables will change:
int ledState = LOW;  // ledState used to set the LED
char user_input[50]; // Define a character array to store the input string.
int index = 0; // Index to keep track of the position in the array
char morse_input[50];
 
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
  pinMode(RED, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  if (Serial.available()) {
    // Read characters from the serial buffer until a newline ('\n') character is received or the array is full.
    while (Serial.available() && index < 48) {
        char incoming_char = Serial.read(); // Read the next character from the serial buffer.
        // Check if the input character is a lowercase letter, convert to uppercase if it is.
        if (islower(incoming_char)) {
            // Convert the lowercase letter to uppercase.
            incoming_char = toupper(incoming_char);
        }
        user_input[index] = incoming_char; // Store the character in the array.
        index++; // Move to the next position in the array.
    }
    user_input[index] = '\0'; // Null-terminate the string.
    int input_length = strlen(user_input);
    // Loop through the characters in the input string and print each character.
    for (int i = 0; i < input_length; i++) {
        char current_char = user_input[i];
        Serial.print(current_char);
        const String morseCode = findMorseCode(current_char, morse_input);
        for (int j = 0; morse_input[j] != '\0'; j++) {
                char morse_char = morse_input[j];
                Serial.print(morse_char);
                if (morse_char == '.') {
                    digitalWrite(LED_BUILTIN, HIGH);
                    digitalWrite(RED, HIGH);  
                    delay(500);
                }
                else {
                  digitalWrite(LED_BUILTIN, HIGH);
                  digitalWrite(RED, HIGH);  
                  delay(1000);
                }
                digitalWrite(LED_BUILTIN, LOW);
                digitalWrite(RED, LOW);  
                delay(500);
            }
            clearBuffer(morse_input);
            Serial.print("\n");  
        }
        clearBuffer(user_input);
        index = 0; 
    }
    
}
