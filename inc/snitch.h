#include <genesis.h>
#include <resources.h>

#define SNITCH_WIDTH  32
#define SNITCH_HEIGHT 32

Sprite* snitch_sprite;
fix32 snitch_x = FIX32(128);
fix32 snitch_y = FIX32(128);
fix32 snitch_velocity = FIX32(5);

// Dirección actual del movimiento: 0 = izquierda, 1 = derecha, 2 = arriba, 3 = abajo
int current_direction = 0;
// Contador para mantener la dirección actual durante algunos ciclos antes de cambiar
int direction_counter = 0;

static void initSnitch() {
    PAL_setPalette(PAL2, snitch.palette->data, DMA);
    snitch_sprite = SPR_addSprite(&snitch, fix32ToInt(snitch_x), fix32ToInt(snitch_y), TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
}

static void randomizeSnitchPosition() {
    snitch_x = FIX32(random() % (MAP_WIDTH - SNITCH_WIDTH));
    snitch_y = FIX32(random() % (MAP_HEIGHT - SNITCH_HEIGHT));
}

static void updateSnitchPosition() {
    // Cambiar de dirección aleatoriamente cada 20 ciclos
    if (direction_counter > 20) {
        current_direction = random() % 4;
        direction_counter = 0;
    } else {
        direction_counter++;
    }

    switch (current_direction) {
        case 0: // Mover a la izquierda
            if (snitch_x > FIX32(0)) {
                snitch_x -= snitch_velocity;
            } else {
                randomizeSnitchPosition(); // Reaparecer en un punto aleatorio
            }
            break;
        case 1: // Mover a la derecha
            if (snitch_x < FIX32(MAP_WIDTH - SNITCH_WIDTH)) {
                snitch_x += snitch_velocity;
            } else {
                randomizeSnitchPosition(); // Reaparecer en un punto aleatorio
            }
            break;
        case 2: // Mover hacia arriba
            if (snitch_y > FIX32(0)) {
                snitch_y -= snitch_velocity;
            } else {
                randomizeSnitchPosition(); // Reaparecer en un punto aleatorio
            }
            break;
        case 3: // Mover hacia abajo
            if (snitch_y < FIX32(MAP_HEIGHT - SNITCH_HEIGHT)) {
                snitch_y += snitch_velocity;
            } else {
                randomizeSnitchPosition(); // Reaparecer en un punto aleatorio
            }
            break;
    }

    // Actualizar la posición del sprite
    SPR_setPosition(snitch_sprite, fix32ToInt(snitch_x), fix32ToInt(snitch_y));
}