//
// Created by solar on 1/20/2024.
//

#include "main.h"
#include "menu.h"
#include "checks.h"
int main(){
    //check protection level before starting gui, need over 1 for mouse simulation
    if(checks::protectionLevel()){
        menu::start(600,400,L"Prueba");
    }
    else{

    }

    return 0;

}
