#include "EEpromSettings.h"
#include <EEPROM.h>

EEpromSettings::EEpromSettings(byte projID, settingPointer* settingPointers, size_t settingsCount, bool overwrite) : _projID(projID), _settingsCount(settingsCount) {
    _settingPointers = new settingPointer[settingsCount];
    _settingPointers = settingPointers;

    if(overwrite && EEPROM.read(0) != _projID) {
        EEPROM.update(0, _projID);
        save();
        Serial.println("Overwritten -> Saved defaults to EEPROM");
    }
};

EEpromSettings::~EEpromSettings() {
    delete[] _settingPointers;
};

byte EEpromSettings::getEEpromProjID() {
    return EEPROM.read(0);
}

bool EEpromSettings::save() {
    if (EEPROM.read(0) == _projID) {
        int adress = 1;
        for (size_t i = 0; i < _settingsCount; i++) {
            for (size_t j = 0; j < _settingPointers[i].size; j++) {
                uint8_t* ptr = static_cast<byte*>(_settingPointers[i].pointer)+j;
                EEPROM.update(adress, *ptr);
                adress++;
            }
            // EEPROM.put(adress, _settingPointers[i].pointer);
            // adress += _settingPointers[i].size;
            
        }
        Serial.println("Saved values to EEPROM");
        return true;
    }
    Serial.println("Failed to save values to EEPROM");
    return false;
};

bool EEpromSettings::load() {
    if (EEPROM.read(0) == _projID) {
        int adress = 1;
        for (size_t i = 0; i < _settingsCount; i++) {
            for (size_t j = 0; j < _settingPointers[i].size; j++) {
                byte* ptr = static_cast<byte*>(_settingPointers[i].pointer)+j;
                *ptr = (byte)EEPROM.read(adress);
                adress++;
            }
            // EEPROM.get(adress, _settingPointers[i].pointer);
            // adress += _settingPointers[i].size;
        }
        Serial.println("Loaded values from EEPROM");
        return true;
    }
    Serial.println("Failed to load values from EEPROM");
    return false;
};
