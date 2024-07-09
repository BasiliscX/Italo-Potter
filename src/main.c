#include <genesis.h>
#include <resources.h>
#include <background.h>
#include <colition_maps.h>
#include <player.h>

int main(){
    
    initBackground();
    JOY_setEventHandler(joyEventHandler);
    initPlayer();

    while(1){
        SPR_update();
        initColition();
        attackEvent();
        SYS_doVBlankProcess();
    }
    return (0);
}
