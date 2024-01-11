#ifndef EEPROMVARIABLE_H
#define EEPROMVARIABLE_H

#include "Arduino.h"

using ptr = void*;

struct variablePointer {
    ptr pointer;
    size_t size;
};

/**
 * 
 */
class EEpromVariable {
    public:
        EEpromVariable(byte projID, variablePointer* variablePointers, size_t variablesCount, bool overwrite = true);
        ~EEpromVariable();
        byte getEEpromProjID();
        bool save();
        bool load();
    // private:
        byte _projID; // The project ID.
        variablePointer* _variablePointers; // The array of variable pointers.
        size_t _variablesCount; // The count of variables.
};

#endif //EEPROMVARIABLE_H