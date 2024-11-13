//#include "include/json.hpp"
#include "include/Sea2.h"

struct game_data {
    float x;
    float y;
    int id;
    float hp;
    int view;
};

struct game_data_list {
    game_data data[200];
    game_data team[200];
    int team_count;
    int count;
    int rientation;
};
game_data_list *game2_ = new game_data_list();

int main()
{
    game2_ = (game_data_list*) smmap::build_mmap_void("/storage/emulated/0/sgame/sgame.mmap", false, sizeof(game_data_list));
    
    game2_->count = 1;
    game2_->data[0].hp =100;
    game2_->data[0].id =196;
    game2_->data[0].x =100 ;
    game2_->data[0].y =25;
    game2_->data[0].view =257;
    
    game2_->team_count = 5;
    
    game2_->team[0].hp =149;
    game2_->team[0].id =502;
    game2_->team[0].x =100 ;
    game2_->team[0].y =25;
    game2_->team[0].view =257;
    
    
    
    game2_->team[1].hp =100;
    game2_->team[1].id =136;
    game2_->team[1].x =100 ;
    game2_->team[1].y =25;
    game2_->team[1].view =1;
    
    
    game2_->team[2].hp =100;
    game2_->team[2].id =152;
    game2_->team[2].x =100 ;
    game2_->team[2].y =25;
    game2_->team[2].view =1;
    
    game2_->team[3].hp =100;
    game2_->team[3].id =197;
    game2_->team[3].x =100 ;
    game2_->team[3].y =25;
    game2_->team[3].view =257;
    
    
    game2_->team[4].hp =100;
    game2_->team[4].id =577;
    game2_->team[4].x =100 ;
    game2_->team[4].y =25;
    game2_->team[4].view =257;
    
	return 0;
}