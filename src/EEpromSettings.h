#ifndef LIB_H
#define LIB_H

#include "Arduino.h"

/*TODO:
 - EEPROM settings, pointer problems
 - CRC check?
*/

using ptr = void*;

struct settingPointer {
    ptr pointer;
    size_t size;
};

typedef settingPointer* (*PtrUpdater)();

class EEpromSettings {
    public:
        EEpromSettings(byte projID, PtrUpdater pointerUpdater, size_t settingsCount, bool overwrite = true);
        ~EEpromSettings();
        byte getEEpromProjID();
        void updatePointers(ptr settingsPointers[]);
        bool save();
        bool load();
    // private:
        byte _projID;
        settingPointer* _settingPointers;
        size_t _settingsCount;
        PtrUpdater _pointerUpdater;
};

#endif //LIB_H