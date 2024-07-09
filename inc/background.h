u16 ind = TILE_USER_INDEX;
u16 len = 128;
u16 level_pallete[64];

/**
 * @brief Initializes the background by setting up the palette, copying the background image's palette,
 *        drawing the image on the background plane, and then fading in the palette.
 *
 * @details This function performs the following tasks:
 *          1. Sets the first 64 colors of the palette to black using PAL_setColors.
 *          2. Copies the first 64 colors from the background image's palette to the level_palette array.
 *          3. Draws the background image on the background plane (BG_B) using VDP_drawImageEx.
 *          4. Fades in the palette from black to the level_palette colors over 100 frames using PAL_fadeIn.
 *
 * @param void No parameters are required for this function.
 *
 * @return void The function does not return any value.
 */
static void initBackground() {
    PAL_setColors(0, palette_black, 64, DMA);
    memcpy(&level_pallete[0], bg1.palette->data, len);
    VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    PAL_fadeIn(0,63,level_pallete, 100, TRUE);
}
