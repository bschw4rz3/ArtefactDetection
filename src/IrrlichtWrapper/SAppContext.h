#ifndef SAppContext_H
#define SAppContext_H

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice* device;
    s32             counter;
};

#endif