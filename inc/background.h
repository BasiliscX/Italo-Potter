#define HORIZONTAL_RESOLUTION 320
#define VERTICAL_RESOLUTION 224
#define MAP_WIDTH 512
#define MAP_HEIGHT 512


Map* level_1_map;
u16 ind = TILE_USER_INDEX;
u16 len = 128;
u16 level_pallete[64];


static void initBackground() {
    VDP_loadTileSet(&stadium_tileset, ind, DMA);
    level_1_map = MAP_create(&stadium_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
    PAL_setPalette(PAL0, gh_palette.data, DMA);
    // MAP_scrollTo(level_1_map, 786, 1066);
    // MAP_scrollTo(level_1_map, 0, 768);
}
