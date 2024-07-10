#include <genesis.h>
#include <resources.h>
#include <colition_maps.h>
#include <background.h>
#include <snitch.h>
#include <player.h>
#include <camera.h>

int main(){
    initBackground();
    JOY_setEventHandler(joyEventHandler);
    initPlayer();
    initSnitch(); // Inicializar el sprite snitch

    while(1){
        handleInputEvent();
        updatePlayerPosition();
        initCollision();
        attackEvent();
        camera_play();
        updateSnitchPosition();
        checkCollisionWithSnitch();
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
