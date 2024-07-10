#define DEMENTOR_WIDTH  32
#define DEMENTOR_HEIGHT 32

#define NUM_DEMENTORS 2
#define MIN_DISTANCE_BETWEEN_DEMENTORS 32 // Distancia mínima entre dementores

Sprite* dementor_sprites[NUM_DEMENTORS];
fix32 dementor_x[NUM_DEMENTORS] = { FIX32(64), FIX32(128) };
fix32 dementor_y[NUM_DEMENTORS] = { FIX32(64), FIX32(128) };
fix32 dementor_velocity = FIX32(1);

// Función para inicializar los sprites Dementor
static void initDementors() {
    for (int i = 0; i < NUM_DEMENTORS; i++) {
        PAL_setPalette(PAL3, dementor.palette->data, DMA);
        dementor_sprites[i] = SPR_addSprite(&dementor, fix32ToInt(dementor_x[i]), fix32ToInt(dementor_y[i]), TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
    }
}

// Función para mantener distancia mínima entre dementores
static void maintainDistanceBetweenDementors(int index) {
    for (int i = 0; i < NUM_DEMENTORS; i++) {
        if (i != index) {
            fix32 dx = dementor_x[index] - dementor_x[i];
            fix32 dy = dementor_y[index] - dementor_y[i];
            fix32 distance_squared = fix32Mul(dx, dx) + fix32Mul(dy, dy);
            if (distance_squared < FIX32(MIN_DISTANCE_BETWEEN_DEMENTORS * MIN_DISTANCE_BETWEEN_DEMENTORS)) {
                if (dx != FIX32(0)) {
                    dementor_x[index] += fix32Div(dx, FIX32(4));
                }
                if (dy != FIX32(0)) {
                    dementor_y[index] += fix32Div(dy, FIX32(4));
                }
            }
        }
    }
}

// Función para actualizar la posición de los Dementores persiguiendo al jugador
static void updateDementorPositions() {
    // Obtener las posiciones del jugador
    fix32 player_x_pos = player_x;
    fix32 player_y_pos = player_y;

    for (int i = 0; i < NUM_DEMENTORS; i++) {
        // Verificar si el jugador está en la mitad superior del mapa
        if (player_y_pos < FIX32(MAP_HEIGHT / 2)) {
            // Mover hacia el jugador solo si está en la mitad superior del mapa
            if (dementor_x[i] < player_x_pos) {
                dementor_x[i] += dementor_velocity;
            } else if (dementor_x[i] > player_x_pos) {
                dementor_x[i] -= dementor_velocity;
            }

            if (dementor_y[i] < player_y_pos) {
                dementor_y[i] += dementor_velocity;
            } else if (dementor_y[i] > player_y_pos) {
                dementor_y[i] -= dementor_velocity;
            }
        } else {
            // Si el jugador está en la mitad inferior, los Dementores vuelven al borde superior
            if (dementor_y[i] > FIX32(0)) {
                dementor_y[i] -= dementor_velocity;
            }
        }

        // Asegurarse de que el Dementor se mantenga en la mitad superior del mapa
        if (dementor_y[i] > FIX32((MAP_HEIGHT / 2) - DEMENTOR_HEIGHT)) {
            dementor_y[i] = FIX32((MAP_HEIGHT / 2) - DEMENTOR_HEIGHT);
        } else if (dementor_y[i] < FIX32(0)) {
            dementor_y[i] = FIX32(0);
        }

        // Mantener distancia mínima entre dementores
        maintainDistanceBetweenDementors(i);

        // Actualizar la posición del sprite
        SPR_setPosition(dementor_sprites[i], fix32ToInt(dementor_x[i]), fix32ToInt(dementor_y[i]));
    }
}