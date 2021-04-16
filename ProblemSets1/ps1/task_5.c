#include <superkarel.h>

void turn_right();
void go_forward();
void face_north();
void face_east();
void face_west();
void face_south();
void step_back();
bool is_beeper_front();

void get_center_x();
void get_center_y();

bool beetwen_beepers();
void turn_back();

void find_center();



int main(){
	turn_on("task_5.kw");
	set_step_delay(100);

	get_center_x();
    

    get_center_y();
    while(beepers_present()){
        pick_beeper();
    }

    
    find_center();
    step();
    while(beepers_present() || not_facing_north()){
        if(front_is_clear()){
            if(no_beepers_present()){
                put_beeper();
            }
            step();
        }else{
            turn_left();
        }

    }

    put_beeper();
    face_west();
    step();
    while(no_beepers_present()){
        step();
    }
    pick_beeper();
    face_north();
	turn_off();

}


void find_center(){
    
    while(no_beepers_present()){
        step();
        
    }

    face_north();
    put_beeper();

    while(front_is_clear()){
        pick_beeper();
        step();
    }

    turn_back();
    step();
    while(no_beepers_present()){
        step();
    }

    while(front_is_clear()){
        step();
        pick_beeper();
    }
    put_beeper();
    turn_back();
    step();
    while(no_beepers_present()){
        step();
    }
    face_east();
    go_forward();
    face_north();
    

}



void get_center_x(){
    face_south();
    go_forward();
    face_west();
    go_forward();

    face_east();
    put_beeper();

    go_forward();
    put_beeper();
    turn_back();
    go_forward();
    turn_back();

    while(!beetwen_beepers()){
        
        while(!is_beeper_front()){
            step();
        }
        
        put_beeper();
        turn_back();
        while(!is_beeper_front()){
            step();
        }
        turn_back();
        put_beeper();
        
    }

    face_north();
    while(front_is_clear()){
        step();
        if(no_beepers_present()){
            put_beeper();
        }
    }

    face_south();
    go_forward();
    face_east();

    pick_beeper();
    
}


void get_center_y(){
    go_forward();
    face_north();
    go_forward();
    put_beeper();
    turn_back();
    go_forward();
    turn_back();
    while(!beetwen_beepers()){
        
        while(!is_beeper_front()){
            step();
        }
        
        put_beeper();
        turn_back();
        while(!is_beeper_front()){
            step();
        }
        turn_back();
        put_beeper();
        
    }
    face_west();
}

bool beetwen_beepers(){
    if(is_beeper_front()){
        turn_back();
        if(is_beeper_front()){
            turn_back();
            return true;
        }
        turn_back();
        return false;
    }
    return false;
}

void face_south(){
    while (!facing_south()){
        turn_left();
    }
}
void face_west(){
    while(!facing_west()){
        turn_left();
    }
}

void face_east(){
    while(not_facing_east()){
        turn_left();
    }
}

void face_north(){
    while (!facing_north())
    {
        turn_left();
    }
    
}


void go_forward(){
    while (front_is_clear())
    {
        step();
    }
    
}

bool is_beeper_front(){

    if (front_is_clear()){
        step();
        if(beepers_present()){
            step_back();
            return true;
        }else{
            step_back();
            return false;
        }
        
    }
    return false;
}

void step_back(){
    set_step_delay(0);
    turn_left();
    turn_left();
    step();
    turn_left();
    turn_left();
    set_step_delay(100);
}

void turn_right(){
	
	set_step_delay(0);
	turn_left();
	turn_left();
	turn_left();
	set_step_delay(100);

}

void turn_back(){
    turn_left();
    turn_left();
}




