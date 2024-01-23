//
// Created by solar on 1/20/2024.
//

#ifndef FC2T_CLICKER_CLICKER_H
#define FC2T_CLICKER_CLICKER_H


namespace clicker{
    //spike config
    inline bool LeftSpike;
    inline bool RightSpike;
    inline int LeftSpikeChance;
    inline int RightSpikeChance;
    inline int RightSpikeAmount;
    inline int LeftSpikeAmount;
    //drop config
    inline bool LeftDrop;
    inline bool RightDrop;
    inline int LeftDropChance;
    inline int RightDropChance;
    inline int LeftDropAmount;
    inline int RightDropAmount;
    //clicker config
    inline int LeftClickerRange = 2;
    inline int RightClickerRange = 2;
    inline bool LeftClickerStatus = false;
    inline int LeftTargetedCPS;
    inline bool RightClickerStatus = false;
    inline int RightTargetedCPS;
    void backgroundTask();
    void startBackgroundTask();
}

#endif //FC2T_CLICKER_CLICKER_H
