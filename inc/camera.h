int current_camera_x = 0;
int current_camera_y = 0;
#define HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES 152
#define HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES 153
#define HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES 115
#define HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES 116

static void camera_play(){
    if(player_x < FIX32(0)){
        player_x = FIX32(0);
    } else if(player_x > FIX32(MAP_WIDTH - PLAYER_WIDTH)){
        player_x = FIX32(MAP_WIDTH - PLAYER_WIDTH);
    }

    if(player_y < FIX32(0)){
        player_y = FIX32(0);
    } else if(player_y > FIX32(MAP_HEIGHT - PLAYER_HEIGHT)){
        player_y = FIX32(MAP_HEIGHT - PLAYER_HEIGHT);
    }

    int player_x_map_integer = fix32ToInt(player_x);
    int player_y_map_integer = fix32ToInt(player_y);

    int player_x_position_on_screen = player_x_map_integer - current_camera_x;
    int player_y_position_on_screen = player_y_map_integer - current_camera_y;

    int new_camera_x, new_camera_y;

    if(player_x_position_on_screen > HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES){
        new_camera_x = player_x_map_integer - HOW_FAR_TO_RIGHT_BEFORE_CAMERA_MOVES;        
    } else if(player_x_position_on_screen < HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES){
        new_camera_x = player_x_map_integer - HOW_FAR_TO_LEFT_BEFORE_CAMERA_MOVES;
    } else{
        new_camera_x = current_camera_x;
    }

    if(player_y_position_on_screen > HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES){
        new_camera_y = player_y_map_integer - HOW_FAR_TO_BOTTOM_BEFORE_CAMERA_MOVES;        
    } else if(player_y_position_on_screen < HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES){
        new_camera_y = player_y_map_integer - HOW_FAR_TO_TOP_BEFORE_CAMERA_MOVES;
    } else{
        new_camera_y = current_camera_y;
    }

    if(new_camera_x < 0){
        new_camera_x = 0;
    } else if(new_camera_x > (MAP_WIDTH - HORIZONTAL_RESOLUTION)){
        new_camera_x = MAP_WIDTH - HORIZONTAL_RESOLUTION;
    }
    
    if(new_camera_y < 0){
        new_camera_y = 0;
    } else if(new_camera_y > (MAP_HEIGHT - VERTICAL_RESOLUTION)){
        new_camera_y = MAP_HEIGHT - VERTICAL_RESOLUTION;
    }

    if((current_camera_x != new_camera_x) || (current_camera_y != new_camera_y)){
        current_camera_x = new_camera_x;  // Corregido
        current_camera_y = new_camera_y;

        MAP_scrollTo(level_1_map, new_camera_x, new_camera_y);
    }

    SPR_setPosition(player, fix32ToInt(player_x) - new_camera_x, fix32ToInt(player_y) - new_camera_y);
}
