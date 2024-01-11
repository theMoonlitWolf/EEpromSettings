#include <Arduino.h>
#include <EEpromVariable.h>

/**Description:
 * This example shows how to use the library. Comments in this sketch are used to explain different parts.
*/

// Save example data to eeprom. Run this sketch once, than set this value to false and upload again.
#define SAVE_EXAMPLE_DATA true
// #define SAVE_EXAMPLE_DATA false

// Project ID is a 1 byte nubmer (0-255), strored in the first byte of the EEPROM (addres 0). Shoud be unique for all projects intended for the same board.
// The libary uses this value to see what project is the data on the EEPROM from. If different, the data will be overwritten with default values from your sketch.
#define PROJECT_ID 1

// Example srtucture
struct myStruct {
    byte x;
    char y;
};

/* Create variables variables.
 * Needs to be dynamically allocated (with new or malloc), so it has a constant adress in RAM.
 * Save the pointer values and use them like normal variables:
 *    for simple types (int, byte, float, bool ...) use: '*variableName' for read and '*variableName = value' for write
 *    for char arrays (c-strings) use like normal: 'variableName'
 *    for structures and classes use -> insted of the dot: 'variableName->member'
 */
char* a = new char[3];
int* b = new int;
myStruct* c = new myStruct;
float* d = new float;

// Create an array of pointers to the variables variables with its sizes. the lenght of this array will be needed in the constructor.
#define VARIABLES_NUM 3
variablePointer variablePointers[VARIABLES_NUM] = {
    {a, sizeof(a)},
    {b, sizeof(b)},
    {c, sizeof(c)}
};

// Constructor
EEpromVariable eepromVariable(PROJECT_ID, variablePointers, VARIABLES_NUM);

void setup() {
    Serial.begin(115200);
    Serial.println();

    // Terminate the empty char array (c-string) (even tho I'm not sure if it's needed)
    a[2] = '\0';

    // Set some data - for the first run to be saved to EEPROM.
    #if SAVE_EXAMPLE_DATA == true
    strcpy(a, "AB\0");
    *b = 42;
    c->x = 5;
    c->y = 'f';
    #endif

    // Set some different data - for the second run to be visibly overwritten by the data from EEPROM.
    #if SAVE_EXAMPLE_DATA == false
    strcpy(a, "XX");
    *b = 0;
    c->x = 0;
    c->y = 'x';
    #endif

    // Print Project ID
    Serial.print("ProjectID:"); Serial.print(PROJECT_ID); Serial.print(", eepromProjectID: "); Serial.println(eepromVariable.getEEpromProjID());
    Serial.println();

    // Print hard coded data
    Serial.println("Default values:");
    Serial.print("a = "); Serial.println(a);
    Serial.print("b = "); Serial.println(*b);
    Serial.print("c.x = "); Serial.println(c->x);
    Serial.print("c.y = "); Serial.println(c->y);
    Serial.println();

    // Save data to EEPROM - only the first run
    #if SAVE_EXAMPLE_DATA == true
    eepromVariable.save();
    #endif

    // Load data from EEPROM and print it to Serial (EEpromVariable.load() returns bool, true if the load was successful)
    if (eepromVariable.load()) {
        Serial.print("a = "); Serial.println(a);
        Serial.print("b = "); Serial.println(*b);
        Serial.print("c.x = "); Serial.println(c->x);
        Serial.print("c.y = "); Serial.println(c->y);
    } else {
        Serial.println("Failed to load values from EEPROM - different project ID?");
    }
    Serial.println();

}

void loop() {
    //loop
}