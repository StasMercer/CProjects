#include <superkarel.h>

void turn_right();
void go_forward();
void face_north();
void face_east();
void face_west();
void face_south();
void step_back();
bool is_beeper_left();

void turn_back();
bool is_right_ok();
void mark_enters();


int main(){
	turn_on("task_7.kw");
	set_step_delay(100);
    mark_enters();
    while(is_right_ok()){
        
    }
    
	turn_off();

}


void mark_enters(){
    while(front_is_clear()){
        if(left_is_clear() && !is_beeper_left()){
            turn_left();
            step();
            put_beeper();
            put_beeper();
            step_back();
            turn_right();
        }
        step();
        
    }
    if(left_is_clear() && !is_beeper_left()){
        turn_left();
        step();
        put_beeper();
        put_beeper();

        step_back();
        turn_right();
    }
    turn_back();
    go_forward();
    turn_back();
    while(!is_beeper_left()){
        step();
    }
}

bool is_right_ok(){
    if(is_beeper_left()){
        turn_left();
        step();
        pick_beeper();
        step();

        while(no_beepers_present()){
            if(front_is_clear() && right_is_blocked()){
                step();
                continue;
            }
                
            if(front_is_blocked() &&
            right_is_blocked() && 
            left_is_clear()){
                turn_left();
                step();
                continue;
            }
            
        
        

            if(right_is_clear()){
                turn_right();
                step();
                continue;
            }
            turn_back();

        }
    }
    
    pick_beeper();

    if(beepers_present()){
        
        step();
        face_east();
        if(front_is_clear()){
            step();
        }else
        {
            return false;
        }
        

        while(!is_beeper_left()){
            if(front_is_blocked()){
                return false;
            }
            step();
        }
        
        return true;
    }

    step();
    face_east();
    if(front_is_clear()){
            step();
    }
    else
    {
        return false;
    }
    
    while(!is_beeper_left()){
        if(front_is_blocked()){
            return false;
        }
        step();
    }
        

    return true;

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

bool is_beeper_left(){

    if (left_is_clear()){
        turn_left();
        step();
        if(beepers_present()){
            step_back();
            turn_right();
            return true;
        }else{
            
            step_back();
            turn_right();
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




