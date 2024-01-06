#include "EEpromSettings.h"
#include <EEPROM.h>

EEpromSettings::EEpromSettings(byte projID, PtrUpdater pointerUpdater, size_t settingsCount, bool overwrite) : _projID(projID), _settingsCount(settingsCount) {
    _settingPointers = new settingPointer[settingsCount];
    _pointerUpdater = pointerUpdater;

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
        size_t i = 0;
        _settingPointers = _pointerUpdater();
        while (i < _settingsCount) {
            EEPROM.put(adress, _settingPointers[i].pointer);
            adress += _settingPointers[i].size;
            i++;
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
        size_t i = 0;
        while (i < _settingsCount) {
            _settingPointers = _pointerUpdater();
            // Serial.println((int)_settingPointers[i].pointer);
            EEPROM.get(adress, _settingPointers[i].pointer);
            Serial.println((int)_settingPointers[1].pointer);
            adress += _settingPointers[i].size;
            i++;
        }
        Serial.println("Loaded values from EEPROM");
        Serial.println((int)_settingPointers[1].pointer);
        return true;
    }
    Serial.println("Failed to load values from EEPROM");
    return false;
};
