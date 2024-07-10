
#define BIG_CLOUD_WIDTH  160
#define BIG_CLOUD_HEIGHT 64

Sprite* big_cloud_sprite;
fix32 big_cloud_x = FIX32(0);
fix32 big_cloud_y = FIX32(32);
fix32 big_cloud_velocity = FIX32(0.5);

// Función para inicializar el sprite Big Cloud
static void initBigCloud() {
    PAL_setPalette(PAL0, big_cloud.palette->data, DMA);
    // big_cloud_sprite = SPR_addSprite(&big_cloud, fix32ToInt(big_cloud_x), fix32ToInt(big_cloud_y), TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
    VDP_drawImageEx(BG_A, &big_cloud, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), fix32ToInt(big_cloud_x), fix32ToInt(big_cloud_y), FALSE, TRUE);
    // ind += big_cloud.tileset->numTile;
}

// Función para actualizar la posición del Big Cloud cruzando el nivel
static void updateBigCloudPosition() {
    big_cloud_x += big_cloud_velocity;
    if (big_cloud_x > FIX32(MAP_WIDTH)) {
        big_cloud_x = FIX32(0) - FIX32(BIG_CLOUD_WIDTH); // Resetear la posición al inicio cuando se sale del nivel
    }
    SPR_setPosition(big_cloud_sprite, fix32ToInt(big_cloud_x), fix32ToInt(big_cloud_y));
}