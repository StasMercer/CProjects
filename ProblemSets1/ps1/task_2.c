#include <superkarel.h>

void turn_right();

int main(){
	turn_on("task_2.kw");
	set_step_delay(100);
	while(no_beepers_present()){
		if(front_is_clear() && right_is_blocked()){
            step();
        }else{
            turn_left();
        }
	}
    pick_beeper();
	turn_left();
    turn_left();
    

    while(front_is_clear()){
        step();
        if(front_is_blocked()){
            turn_right();
        }
    }
	turn_off();

}

void turn_right(){
	
	set_step_delay(0);
	turn_left();
	turn_left();
	turn_left();
	set_step_delay(100);

}




