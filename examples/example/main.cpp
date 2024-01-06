#include <Arduino.h>
#include <EEpromSettings.h>

#define PROJECT_ID 1

struct myStruct {
    byte x;
    char y;
};

char* a = new char[3];
int* b = new int;
myStruct* c = new myStruct;


#define SETTINGS_NUM 3
settingPointer settingPointers[SETTINGS_NUM] = {
    {a, sizeof(a)},
    {b, sizeof(b)},
    {c, sizeof(c)}
};

EEpromSettings eepromSettings(PROJECT_ID, settingPointers, SETTINGS_NUM);

void setup() {
    Serial.begin(115200);
    Serial.println();

    a[2] = '\0';

    // strcpy(a, "AB\0");
    // *b = 42;
    // c->x = 5;
    // c->y = 'f';
    
    strcpy(a, "XX");
    *b = 0;
    c->x = 0;
    c->y = 'x';

    Serial.print("poiter to b = "); Serial.println((int)b);
    Serial.println();

    Serial.print("ProjectID: 1, eepromProjectID: "); Serial.println(eepromSettings.getEEpromProjID());
    Serial.println();

    Serial.println("Default values:");
    Serial.print("a = "); Serial.println(a);
    Serial.print("b = "); Serial.println(*b);
    Serial.print("c.x = "); Serial.println(c->x);
    Serial.print("c.y = "); Serial.println(c->y);
    Serial.println();

    // eepromSettings.save();

    if (eepromSettings.load()) {
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