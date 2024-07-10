#include <genesis.h>
#include <resources.h>
#include <colition_maps.h>
#include <player.h>
#include <background.h>
#include <camera.h>



int main(){
    initBackground();
    JOY_setEventHandler(joyEventHandler);
    initPlayer();

    while(1){
        handleInputEvent();
        updatePlayerPosition();
        initCollision();
        attackEvent();
        camera_play();
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}

