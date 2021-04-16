#include <superkarel.h>


void jump_over();
void turn_right();
void go_back();
	

int main(){
	turn_on("task_1.kw");
	set_step_delay(100);
	while(!facing_east()){
		turn_left();
	}

	put_beeper();
	if(front_is_clear()){
		while (front_is_clear())
		{
			step();
		}
	}else{
		turn_left();
		step();
	}
	
	
	while(!beepers_present()){
		
			jump_over();
		
	}

	pick_beeper();
	while (not_facing_north())
	{
		turn_left();
	}
	

	while(!beepers_present()){
		go_back();
	}
	pick_beeper();
	turn_left();
	

	turn_off();

}

void turn_right(){
	
	set_step_delay(0);
	turn_left();
	turn_left();
	turn_left();
	set_step_delay(100);

}


void jump_over(){

	if(right_is_clear()){
		turn_right();
		step();
	}
	
	while(!right_is_clear() && front_is_clear()){
			step();
	}
	
	
	
	if(front_is_blocked() && right_is_blocked()){
		turn_left();
	}

	
}

void go_back(){
	
	
	while(front_is_clear()){
		
			step();
		
	}
	turn_left();
	step();
	turn_left();
	while(front_is_clear()){
		step();
	}

	turn_left();
	turn_left();
}

