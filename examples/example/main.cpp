#include <Arduino.h>
#include <EEpromSettings.h>


struct myStruct {
    byte x;
    char y;
};

// char a[3] = "AB";
// int b = 1;
// myStruct c = { 5, 'f' };

char a[3] = "XX";
int b = 6;
myStruct c = { 0, 'x' };


#define SETTINGS_NUM 3
settingPointer settingPointers[SETTINGS_NUM];
settingPointer* settingsPtrUpdater() {
    settingPointers[0] = {&a, sizeof(a)};
    settingPointers[1] = {&b, sizeof(b)};
    settingPointers[2] = {&c, sizeof(c)};
    return settingPointers;
}

EEpromSettings eepromSettings(1, settingsPtrUpdater, SETTINGS_NUM, false);

void setup() {
    Serial.begin(115200);
    Serial.println();

    Serial.print("poiter to b = "); Serial.println((int)&b);

    Serial.print("ProjectID: 1, eepromProjectID: "); Serial.println(eepromSettings.getEEpromProjID());

    Serial.println("Default values:");
    Serial.print("a = "); Serial.println(a);
    Serial.print("b = "); Serial.println(b);
    Serial.print("c.x = "); Serial.println(c.x);
    Serial.print("c.y = "); Serial.println(c.y);

    // eepromSettings.save();

    if (eepromSettings.load()) {
        Serial.print("a = "); Serial.println(a);
        Serial.print("b = "); Serial.println(b);
        Serial.print("c.x = "); Serial.println(c.x);
        Serial.print("c.y = "); Serial.println(c.y);
    } else {
        Serial.println("Failed to load values from EEPROM - different project ID?");
    }

    Serial.println("b value from pointer from settingPointers:");
    Serial.println((int)settingPointers[1].pointer);
    Serial.println(*static_cast<int*>(settingPointers[1].pointer));

    Serial.println("b value from pointer from eepromSettings._settingPointers:");
    Serial.println((int)eepromSettings._settingPointers[1].pointer);
    Serial.println(*static_cast<int*>(eepromSettings._settingPointers[1].pointer));

    Serial.print("poiter to b = "); Serial.println((int)&b);

}

void loop() {
    //loop
}