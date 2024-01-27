#ifndef FC2T_CLICKER_JITTER_H
#define FC2T_CLICKER_JITTER_H
#include "../fc2.hpp"


namespace jitter{
    inline bool LeftJitter;
    inline bool RightJitter;
    inline int LeftJitterAmount;
    inline int RightJitterAmount;

    [[noreturn]] void move(FC2_TEAM_MOUSE_CODE code, unsigned int &keyHexValue, int &current);
    void LeftBackgroundTask();
    void RightBackgroundTask();

}


#endif //FC2T_CLICKER_JITTER_H
