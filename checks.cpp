#include "checks.h"
#include "../fc2.hpp"


bool checks::protectionLevel(){
    const std::string data = fc2::api("getMember&protection&beautify");
    std::string key = "\"protection\":";
    size_t keyPosition = data.find(key);
    if (keyPosition == std::string::npos) {
        std::cerr << "Key 'protection' not found." << std::endl;
        return 1;
    }
    size_t start = keyPosition + key.length();
    size_t end = data.find(",", start);
    std::string protectionValueStr = data.substr(start, end - start);
    // trim
    protectionValueStr.erase(0, protectionValueStr.find_first_not_of(" \n\r\t"));
    protectionValueStr.erase(protectionValueStr.find_last_not_of(" \n\r\t") + 1);
    // string to int
    int protectionValue = std::stoi(protectionValueStr);

    // debug
    //std::cout << "Protection value: " << protectionValue << std::endl;
    // true if we can simulate mouse inputs
    if(protectionValue >= 1){
        return true;
    }
    else{
        fc2::lua( "fantasy.log(\"Cant run clicker as you don't meet the minimum protection level\")" );
        return false;
    }
}