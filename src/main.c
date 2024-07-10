#include <genesis.h>
#include <resources.h>
#include <colition_maps.h>
#include <player.h>
#include <background.h>
#include <camera.h>
#include <snitch.h>
#include <dementor.h>
#include <big_cloud.h>

int main() {
    initBackground();
    JOY_setEventHandler(joyEventHandler);
    initPlayer();
    initSnitch(); // Inicializar el sprite snitch
    initDementors(); // Inicializar los sprites dementores
    initBigCloud(); // Inicializar el sprite big cloud

    while(1) {
        handleInputEvent();
        updatePlayerPosition();
        initCollision();
        attackEvent();
        camera_play();
        updateSnitchPosition(); // Actualizar la posición del sprite snitch
        checkCollisionWithPlayer(); // Verificar colisión con el jugador
        updateDementorPositions(); // Actualizar la posición de los sprites dementores
        // updateBigCloudPosition(); // Actualizar la posición del sprite big cloud
        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
