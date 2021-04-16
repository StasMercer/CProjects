#include <superkarel.h>


void turn_right();
void grab_line();
bool is_beeper_right();
bool is_beeper_left();
void step_back();
bool go_line_bellow();
void go_forward();
void place_beepers();
void face_north();
void find_beeper();

int main(){
	turn_on("task_3.kw");
	set_step_delay(50);

    while (front_is_clear())
    {
        grab_line();
        if(!go_line_bellow()){
            break;
        }
        
        
    }

    find_beeper();

    face_north();
    go_forward();
    turn_left();

    while(beepers_present()){
        pick_beeper();
    }

    while(beepers_in_bag()){
        place_beepers();
    }
	
    find_beeper();

   
    face_north();
    go_forward();
    turn_left();
    go_forward();

    turn_left();
    turn_left();

	turn_off();

}


void place_beepers(){
    while(beepers_in_bag()){
        if(right_is_blocked() || is_beeper_right()){
            put_beeper();
        }
        step();
    }

    if(go_line_bellow()){
        while(no_beepers_present() && front_is_clear()){
            step();
        }

        turn_left();
        turn_left();

        while(beepers_present()){
            pick_beeper();
        }
    }
    
    
    
}

void go_forward(){
    while (front_is_clear())
    {
        step();
    }
    
}

void turn_right(){
	
	set_step_delay(0);
	turn_left();
	turn_left();
	turn_left();
	set_step_delay(50);

}

bool go_line_bellow(){
    while(not_facing_west()){
        turn_left();
    }

    while (front_is_clear())
    {
        step();
    }
    if(left_is_clear()){
        turn_left();
        step();
        turn_left();
        return true;
    }else{
        turn_left();
        turn_left();
        return false;
    }
    
    

}

void grab_line(){
    while (front_is_clear())
    {
        if(beepers_present()){
            pick_beeper();
        }
        step();
    }
    if(beepers_in_bag()){
            while(left_is_clear() && !is_beeper_left()){
                step_back();
            }

            while (beepers_in_bag())
            {
                put_beeper();
    
            }
    }
    
    

    
}

bool is_beeper_right(){
    if (right_is_clear()){
        turn_right();
        step();
        if(beepers_present()){
            step_back();
            turn_left();
            return true;
        }else{
        
            step_back();
            turn_left();
            return false;
        }
        
    }
    return false;
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
    set_step_delay(50);
}

void face_north(){
    while (!facing_north())
    {
        turn_left();
    }
    
}

void find_beeper(){

    while(not_facing_west()){
        turn_left();
    }

    if(front_is_blocked()){
        turn_left();
        turn_left();
    }

    while(no_beepers_present()){
        if(front_is_clear()){
            step();
        }else
        {
            face_north();
            step();
            if(right_is_blocked()){
                turn_left();
            }else
            {
                turn_right();
            }
            
        } 
    }
}

