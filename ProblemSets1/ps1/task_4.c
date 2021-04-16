#include <superkarel.h>

void turn_right();
void fill_line();
void go_forward();
bool detect_line();
void face_north();
void face_east();


int main(){
	turn_on("task_4.kw");
	set_step_delay(100);
	while(front_is_clear() || detect_line()){
        if(detect_line()){
            fill_line();
        }
        
        face_east();
        if(front_is_clear()){
            step();
        }else
        {
            break;
        }
        
        
    }
    face_east();
	turn_off();

}

void fill_line(){
    face_north();
    while(front_is_clear()){
        if(no_beepers_present()){
            put_beeper();
        }
        step();
    }
    if(no_beepers_present()){
        put_beeper();
    }

    turn_left();
    turn_left();
    go_forward();
    
}

bool detect_line(){
    face_north();
    while(front_is_clear()){
        if (beepers_present())
        {
            turn_left();
            turn_left();
            go_forward();
            return true;
        }
        step();
        
    }

    turn_left();
    turn_left();
    go_forward();
    return false;
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

void turn_right(){
	
	set_step_delay(0);
	turn_left();
	turn_left();
	turn_left();
	set_step_delay(100);

}




