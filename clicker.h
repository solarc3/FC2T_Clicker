#ifndef FC2T_CLICKER_CLICKER_H
#define FC2T_CLICKER_CLICKER_H

#include <vector>
#include <string>
#include <utility>
#include "../fc2.hpp"

namespace clicker {
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
    inline int LeftTargetedCPS = 1;
    inline bool RightClickerStatus = false;
    inline int RightTargetedCPS = 1;
    //keybinds
    inline unsigned int Leftclickerkey;
    inline unsigned int Rightclickerkey;
    inline const char *options[] = {"Hold", "Toggle"};
    inline int current = 0;
    inline const char *rightOptions[] = {"Hold", "Toggle"};
    inline int rightCurrent = 0;
    inline int LeftcurrentCPS;
    inline int RightcurrentCPS;
    inline int EventDuration = 5;
    inline int GlobalSleep = 300;
    [[noreturn]]void clicker(unsigned int &leftKeyHexValue, unsigned int &rightKeyHexValue, bool &leftClickerStatus,
                                   bool &rightClickerStatus, int &leftCurrent, int &rightCurrent);    void BackgroundTask();
    void updateCPSTask();
    void KeySelectionCombo(const char *combo_label, unsigned int &selectedKey);
    [[noreturn]] void update(int &EventDuration, int &GlobalSleep);
    void sendclick(FC2_TEAM_MOUSE_CODE code, int cps);
    inline std::vector<std::pair<std::string, unsigned int>> keyMap = {
            {"LBUTTON",    0x01},
            {"RBUTTON",    0x02},
            {"CANCEL",     0x03},
            {"MBUTTON",    0x04},
            {"XBUTTON1",   0x05},
            {"XBUTTON2",   0x06},
            {"BACK",       0x08},
            {"TAB",        0x09},
            {"CLEAR",      0x0C},
            {"RETURN",     0x0D},
            {"SHIFT",      0x10},
            {"CONTROL",    0x11},
            {"MENU",       0x12},
            {"PAUSE",      0x13},
            {"CAPS LOCK",    0x14},
            {"ESCAPE",     0x1B},
            {"SPACE",      0x20},
            {"PAGE UP",      0x21},
            {"PAGE DOWN",       0x22},
            {"END",        0x23},
            {"HOME",       0x24},
            {"LEFT ARROW",       0x25},
            {"UP ARROW",         0x26},
            {"RIGHT ARROW",      0x27},
            {"DOWN ARROW",       0x28},
            {"SELECT",     0x29},
            {"PRINT",      0x2A},
            {"EXECUTE",    0x2B},
            {"PRINT SCREEN",   0x2C},
            {"INSERT",     0x2D},
            {"DELETE",     0x2E},
            {"HELP",       0x2F},
            {"0",             0x30},
            {"1",             0x31},
            {"2",             0x32},
            {"3",             0x33},
            {"4",             0x34},
            {"5",             0x35},
            {"6",             0x36},
            {"7",             0x37},
            {"8",             0x38},
            {"9",             0x39},
            {"A",             0x41},
            {"B",             0x42},
            {"C",             0x43},
            {"D",             0x44},
            {"E",             0x45},
            {"F",             0x46},
            {"G",             0x47},
            {"H",             0x48},
            {"I",             0x49},
            {"J",             0x4A},
            {"K",             0x4B},
            {"L",             0x4C},
            {"M",             0x4D},
            {"N",             0x4E},
            {"O",             0x4F},
            {"P",             0x50},
            {"Q",             0x51},
            {"R",             0x52},
            {"S",             0x53},
            {"T",             0x54},
            {"U",             0x55},
            {"V",             0x56},
            {"W",             0x57},
            {"X",             0x58},
            {"Y",             0x59},
            {"Z",             0x5A},
            {"LWIN",       0x5B},
            {"RWIN",       0x5C},
            {"APPS",       0x5D},
            {"SLEEP",      0x5F},
            {"NUMPAD 0",    0x60},
            {"NUMPAD 1",    0x61},
            {"NUMPAD 2",    0x62},
            {"NUMPAD 3",    0x63},
            {"NUMPAD 4",    0x64},
            {"NUMPAD 5",    0x65},
            {"NUMPAD 6",    0x66},
            {"NUMPAD 7",    0x67},
            {"NUMPAD 8",    0x68},
            {"NUMPAD 9",    0x69},
            {"MULTIPLY",   0x6A},
            {"ADD",        0x6B},
            {"SEPARATOR",  0x6C},
            {"SUBTRACT",   0x6D},
            {"DECIMAL",    0x6E},
            {"DIVIDE",     0x6F},
            {"F1",         0x70},
            {"F2",         0x71},
            {"F3",         0x72},
            {"F4",         0x73},
            {"F5",         0x74},
            {"F6",         0x75},
            {"F7",         0x76},
            {"F8",         0x77},
            {"F9",         0x78},
            {"F10",        0x79},
            {"F11",        0x7A},
            {"F12",        0x7B},
            {"F13",        0x7C},
            {"F14",        0x7D},
            {"F15",        0x7E},
            {"F16",        0x7F},
            {"F17",        0x80},
            {"F18",        0x81},
            {"F19",        0x82},
            {"F20",        0x83},
            {"F21",        0x84},
            {"F22",        0x85},
            {"F23",        0x86},
            {"F24",        0x87},
            {"NUM LOCK",    0x90},
            {"SCROLL",     0x91},
            {"LSHIFT",     0xA0},
            {"RSHIFT",     0xA1},
            {"LCONTROL",   0xA2},
            {"RCONTROL",   0xA3}
    };


}

#endif //FC2T_CLICKER_CLICKER_H
