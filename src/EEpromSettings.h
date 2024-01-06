#ifndef EEPROMSETTINGS_H
#define EEPROMSETTINGS_H

#include "Arduino.h"

/*TODO:
 - example ifdef
 - example documentation
 - CRC check?
*/

using ptr = void*;

struct settingPointer {
    ptr pointer;
    size_t size;
};

class EEpromSettings {
    public:
        EEpromSettings(byte projID, settingPointer* settingPointers, size_t settingsCount, bool overwrite = true);
        ~EEpromSettings();
        byte getEEpromProjID();
        void updatePointers(ptr settingsPointers[]);
        bool save();
        bool load();
    // private:
        byte _projID;
        settingPointer* _settingPointers;
        size_t _settingsCount;
};

#endif //EEPROMSETTINGS_H