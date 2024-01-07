#ifndef EEPROMSETTINGS_H
#define EEPROMSETTINGS_H

#include "Arduino.h"

/* TODO:
 * Docstrings for class and functions
 * README file
 * Post to github and arduino forum
 * CRC check?
 */

using ptr = void*;

struct settingPointer {
    ptr pointer;
    size_t size;
};

/*
*/
class EEpromSettings {
    public:
        EEpromSettings(byte projID, settingPointer* settingPointers, size_t settingsCount, bool overwrite = true);
        ~EEpromSettings();
        byte getEEpromProjID();
        bool save();
        bool load();
    // private:
        byte _projID; // The project ID.
        settingPointer* _settingPointers; // The array of setting pointers.
        size_t _settingsCount; // The count of settings.
};

#endif //EEPROMSETTINGS_H