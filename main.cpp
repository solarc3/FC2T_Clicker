//
// Created by solar on 1/20/2024.
//

#include "main.h"
#include "menu.h"
#include "checks.h"
#include "../fc2.hpp"
int main(){
    //check protection level before starting gui, need over 1 for mouse simulation
    if(checks::protectionLevel()){
        menu::start(400,600,"Prueba");// only start menu if the protection level requirement is met
    }
    else{
        fc2::lua( "fantasy.log(\"Cant run clicker as you don't meet the minimum protection level\")");
    }
    return 0;

}
