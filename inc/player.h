#define PLAYER1_STILL    0
#define PLAYER1_WALK     1
#define PLAYER1_ATACK_A  2
#define PLAYER1_IDLE     3
#define ATTACK1_DURATION 112

#define PLAYER_WIDTH         48
#define PLAYER_HEIGHT        48
#define PLAYER_COLBOX_LEFT   16
#define PLAYER_COLBOX_RIGHT  16
#define PLAYER_COLBOX_TOP    1
#define PLAYER_COLBOX_BOTTOM 48

Sprite* player;
fix32 player_x = FIX32(272);
fix32 player_y = FIX32(422);
fix32 attackTime = FIX32(0);
fix32 player_velocity = FIX32(3);
bool player_move_left = FALSE;
bool player_move_right = FALSE;
bool player_move_up = FALSE;
bool player_move_down = FALSE;

char info_x[10];
char info_y[10];

static void initPlayer() {
    SPR_init();
    PAL_setPalette(PAL1, sprite.palette->data, DMA);
    player = SPR_addSprite(&sprite, fix32ToInt(player_x), fix32ToInt(player_y), TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}

static void handleInputEvent() {
    u16 value = JOY_readJoypad(JOY_1);

    player_move_left = (value & BUTTON_LEFT);
    player_move_right = (value & BUTTON_RIGHT);
    player_move_up = (value & BUTTON_UP);
    player_move_down = (value & BUTTON_DOWN);
}

static void joyEventHandler(u16 joy, u16 changed, u16 state) {
    if (changed & state & BUTTON_A && attackTime == 0) {
        SPR_setAnim(player, PLAYER1_ATACK_A);
        attackTime = FIX32(1);
    }
}

static void attackEvent() {
    if (attackTime > 0 && attackTime < FIX32(ATTACK1_DURATION)) {
        attackTime += FIX32(1);
    } else {
        attackTime = FIX32(0);
    }
}

static void updatePlayerPosition() {
    if (player_move_left && !player_move_right) {
        player_x -= player_velocity;
        SPR_setAnim(player, PLAYER1_STILL);
        SPR_setHFlip(player, TRUE);
    } else if (player_move_right && !player_move_left) {
        player_x += player_velocity;
        SPR_setAnim(player, PLAYER1_STILL);
        SPR_setHFlip(player, FALSE);
    }

    if (player_move_up && !player_move_down) {
        player_y -= player_velocity;
        SPR_setAnim(player, PLAYER1_STILL);
    } else if (player_move_down && !player_move_up) {
        player_y += player_velocity;
        SPR_setAnim(player, PLAYER1_STILL);
    }

    if (!player_move_left && !player_move_right && !player_move_up && !player_move_down) {
        SPR_setAnim(player, PLAYER1_STILL);
    }

    SPR_setPosition(player, fix32ToInt(player_x), fix32ToInt(player_y));
}

static void initCollision() {
    s16 player_left_collision_coordinates;
    s16 player_right_collision_coordinates;
    s16 player_top_collision_coordinates = fix32ToInt(player_y) + PLAYER_COLBOX_TOP;
    s16 player_bottom_collision_coordinates = fix32ToInt(player_y) + PLAYER_COLBOX_BOTTOM;

    s16 xtilecoord_left_collision_player;
    s16 xtilecoord_right_collision_player;
    s16 ytilecoord_top_collision_player = player_top_collision_coordinates >> 4;
    s16 ytilecoord_bottom_collision_player = player_bottom_collision_coordinates >> 4;

    s16 array_index_topleft_colbox;
    s16 array_index_topright_colbox;
    s16 array_index_bottomleft_colbox;
    s16 array_index_bottomright_colbox;

    u8 tile_collision_type_topleft;
    u8 tile_collision_type_topright;
    u8 tile_collision_type_bottomleft;
    u8 tile_collision_type_bottomright;

    s16 blocked_left_coord;
    s16 blocked_right_coord;

    if (player_move_left) {
        player_left_collision_coordinates = fix32ToInt(player_x) + PLAYER_COLBOX_LEFT;
        xtilecoord_left_collision_player = player_left_collision_coordinates >> 4;
        array_index_topleft_colbox = xtilecoord_left_collision_player + (ytilecoord_top_collision_player * LENGTH_OF_LEVEL_COLITION_ARRAY);
        tile_collision_type_topleft = LEVEL_COL[array_index_topleft_colbox];

        array_index_bottomleft_colbox = xtilecoord_left_collision_player + (ytilecoord_bottom_collision_player * LENGTH_OF_LEVEL_COLITION_ARRAY);
        tile_collision_type_bottomleft = LEVEL_COL[array_index_bottomleft_colbox];

        if (tile_collision_type_topleft == SOLID_TILE || tile_collision_type_bottomleft == SOLID_TILE) {
            blocked_left_coord = (xtilecoord_left_collision_player << 4) - PLAYER_COLBOX_LEFT;
            player_x = FIX32(blocked_left_coord);
            player_move_left = FALSE;
        }
    } else if (player_move_right) {
        player_right_collision_coordinates = fix32ToInt(player_x) + PLAYER_COLBOX_RIGHT;
        xtilecoord_right_collision_player = player_right_collision_coordinates >> 4;
        array_index_topright_colbox = xtilecoord_right_collision_player + (ytilecoord_top_collision_player * LENGTH_OF_LEVEL_COLITION_ARRAY);
        tile_collision_type_topright = LEVEL_COL[array_index_topright_colbox];

        array_index_bottomright_colbox = xtilecoord_right_collision_player + (ytilecoord_bottom_collision_player * LENGTH_OF_LEVEL_COLITION_ARRAY);
        tile_collision_type_bottomright = LEVEL_COL[array_index_bottomright_colbox];

        if (tile_collision_type_topright == SOLID_TILE || tile_collision_type_bottomright == SOLID_TILE) {
            blocked_right_coord = (xtilecoord_right_collision_player << 4) - PLAYER_COLBOX_RIGHT;
            player_x = FIX32(blocked_right_coord);
            player_move_right = FALSE;
        }
    }

    sprintf(info_x, "%10li", fix32ToInt(player_x));
    VDP_drawTextBG(BG_A, info_x, 0, 5);
    sprintf(info_y, "%10li", fix32ToInt(player_y));
    VDP_drawTextBG(BG_A, info_y, 0, 6);
}

static void checkCollisionWithSnitch() {
    int player_left = fix32ToInt(player_x);
    int player_right = player_left + PLAYER_WIDTH;
    int player_top = fix32ToInt(player_y);
    int player_bottom = player_top + PLAYER_HEIGHT;

    int snitch_left = fix32ToInt(snitch_x);
    int snitch_right = snitch_left + SNITCH_WIDTH;
    int snitch_top = fix32ToInt(snitch_y);
    int snitch_bottom = snitch_top + SNITCH_HEIGHT;

    if (player_right > snitch_left && player_left < snitch_right &&
        player_bottom > snitch_top && player_top < snitch_bottom) {
        snitch_caught_count++;  // Incrementar el contador de snitch atrapados
        randomizeSnitchPosition();  // Reaparecer el snitch en un punto aleatorio
    }
}
