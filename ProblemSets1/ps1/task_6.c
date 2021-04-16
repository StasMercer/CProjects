#include <superkarel.h>

void turn_right();
void go_forward();
void face_north();
void face_east();
void face_west();
void face_south();
void step_back();
bool is_beeper_front();

void turn_back();

bool beetwen_beepers();

void turn_by_beeper();

int main(){
	turn_on("task_6.kw");
	set_step_delay(400);

    do{
        while(no_beepers_present()){
            step();
        }
        face_north();

        turn_by_beeper();
        turn_back();

    }while(beetwen_beepers());
	
	turn_off();

}


bool beetwen_beepers(){
    put_beeper();
    while(front_is_clear()){
        step();
        if(beepers_present()){
            turn_back();
            step();
            while(no_beepers_present()){
                step();
            }
            turn_back();
            pick_beeper();
            return true;
        }
    }

    turn_back();
    
    if(no_beepers_present()){
        step();
        while(no_beepers_present()){
            step();
        }
    }
    pick_beeper();
    return false;
}

void turn_by_beeper(){

    if(beepers_present()){
        pick_beeper();
        turn_by_beeper();
    }

    turn_left();
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




