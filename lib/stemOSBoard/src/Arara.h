#ifndef Arara_h
#define Arara_h

#include "Task.h"

class Arara: Task {
    private:
    public:
        virtual void init() = 0;
        virtual void loopCode() = 0;
        virtual void run(void * data);
};
#endif