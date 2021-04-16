#include <Arduino.h>
#include "mastermind.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcd_wrapper.h"
#include <stdbool.h>

char *generate_code(bool repeat, int length)
{

    String str = String();
    String rnd = String(random(10));
    if (length < 1)
        return NULL;

    for (int i = 0; i < length; i++)
    {
        if (!repeat)
        {
            while (str.indexOf(rnd) != -1)
            {
                rnd = String(random(10));
            }
            str += rnd;
        }
        else
        {

            str += random(10);
        }
    }

    char *res = malloc(length + 1);
    memcpy(res, str.c_str(), length + 1);
    res[length] = '\0';

    return res;
}

void get_score(const char *secret, const char *guess, int *peg_a, int *peg_b)
{
    String scrt = String(secret);
    String gs = String(guess);

    for (int i = 0; i < gs.length(); i++)
    {
        int index = scrt.indexOf(gs[i]);
        if (index != -1 && index == i)
        {
            if (index == i)
            {
                *peg_a += 1;
            }
            scrt.replace(gs[i], '_');
        }
    }

    for (int i = 0; i < gs.length(); i++){
        int index = scrt.indexOf(gs[i]);
        if(index != -1){
            *peg_b +=1;
        }
        scrt.replace(gs[i], '_');
    }

    Serial.print("score:");
    Serial.print(*peg_a);
    Serial.print(" ");
    Serial.println(*peg_b);
}

void turn_off_leds()
{
    digitalWrite(LED_BLUE_1, LOW);
    digitalWrite(LED_BLUE_2, LOW);
    digitalWrite(LED_BLUE_3, LOW);
    digitalWrite(LED_BLUE_4, LOW);
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_RED_3, LOW);
    digitalWrite(LED_RED_4, LOW);
}

void render_leds(const int peg_a, const int peg_b)
{

    int reds[4] = {LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4};
    int blues[4] = {LED_BLUE_1, LED_BLUE_2, LED_BLUE_3, LED_BLUE_4};

    if (peg_a + peg_b < 5)
    {
        int i;

        for (i = 0; i < peg_a; i++)
        {
            digitalWrite(reds[i], HIGH);
        }
        for (int k = i; k < (i + peg_b); k++)
        {

            digitalWrite(blues[k], HIGH);
        }
    }
}

void render_history(char *secret, char **history, const int entry_nr)
{
    int peg_a = 0;
    int peg_b = 0;

    get_score(secret, history[entry_nr], &peg_a, &peg_b);
    render_leds(peg_a, peg_b);
    String leds = String(" A"+String(peg_a) + "B" + String(peg_b));
    lcd_print_at(0, 0, String(String(entry_nr) + ": " + history[entry_nr]+ leds).c_str());
}

String update_guess(String guess, char * secret, char ** history, int atempts, int peg_a, int peg_b)
{

    bool triger = false;
    unsigned long time = 0;
    int cursor = atempts-1;
    
    while (digitalRead(BTN_1_PIN) == HIGH)
    {
        
        time +=1;
        if (digitalRead(BTN_2_PIN) == HIGH)
        {
            cursor--;
            if(cursor >= 0){
                
                turn_off_leds();
                render_history(secret, history, cursor);
            }else{
                cursor = 0;
            }
            delay(300);
        }

        if (digitalRead(BTN_3_PIN) == HIGH)
        {
            cursor++;
            if(cursor < atempts){
                turn_off_leds();
                render_history(secret, history, cursor);
            }else{
                cursor = atempts-1;
            }
            delay(300);
        }
    }
    
    if (time < 15000 && time > 0)
    {

        guess[0] = guess[0] + 1;
        if (guess[0] > '9') guess[0] = '0';
        triger = true;
    }

    if (digitalRead(BTN_2_PIN) == HIGH)
    {
        guess[1] = guess[1] + 1;
        if (guess[1] > '9') guess[1] = '0';
        triger = true;
    }

    if (digitalRead(BTN_3_PIN) == HIGH)
    {
        guess[2] = guess[2] + 1;
        if (guess[2] > '9') guess[2] = '0';
        triger = true;
    }

    if (digitalRead(BTN_4_PIN) == HIGH)
    {
        guess[3] = guess[3] + 1;
        if (guess[3] > '9') guess[3] = '0';
        triger = true;
    }
    if (triger)
    {
       
        lcd_print_at(0, 1, String("Your: " + guess).c_str());
    }
    return guess;
}

void play_game(char *secret)
{
    char **history = malloc(10 * sizeof(char *));
    for (int i = 0; i < 10; i++)
    {
        history[i] = malloc(5 * sizeof(char));
    }

    lcd_init();
    turn_off_leds();
    String scrt = String(secret);
    String guess = String("0000");
    int atempts = 0;
    
    bool won = false;
    Serial.println("new");
    Serial.println(secret); 
    
    lcd_clear();
    lcd_print_at(0, 0, String("Mastermind").c_str());
    lcd_print_at(0, 1, String("guesss the secret").c_str());

    delay(2000);
    lcd_clear();
    lcd_print_at(0, 0, "Number guessed");
    lcd_print_at(0, 1, String("Your: 0000").c_str());
    
    int peg_a = 0;
    int peg_b = 0;
    while (atempts < 10 && !won)
    {

        guess = update_guess(guess, secret,  history, atempts, peg_a, peg_b);

        if (digitalRead(BTN_ENTER_PIN) == HIGH)
        {
            turn_off_leds();
            peg_a = 0;
            peg_b = 0;
            
            get_score(secret, guess.c_str(), &peg_a, &peg_b);
            render_leds(peg_a, peg_b);
            if(peg_a == 4){
                won = true;
            }
            lcd_clear();
            memcpy(history[atempts], guess.c_str(), 5*sizeof(char));
            String leds = String(" A"+String(peg_a) + "B" + String(peg_b));
            lcd_print_at(0, 0, String(String(atempts) + ": " + history[atempts]+ leds).c_str());
            //guess = "0000";
            lcd_print_at(0, 1, String("Your: " + guess).c_str());
            atempts += 1;

            
            delay(100);
        }
        delay(100);
    }
    lcd_clear();
    if(won){
        lcd_print_at(0, 0, "Damn boy you won");
    }else{
        lcd_print_at(0, 0, "You loose :(");
        lcd_print_at(0, 1, String("secret:"+ scrt).c_str());
    }

    delay(2000);
    for (int i = 0; i < 10; i++)
    {
        free(history[i]);
    }
    free(history);
}