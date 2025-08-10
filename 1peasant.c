#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//global variable
int num_rounds = 0;// so at the first round > CRITICAL! wouldn't be printed
int shoper = 0;
int chest_choice;
int enemy_number = 0;

int upgrade_health_max = 0;
int upgrade_mana_max = 0;
int upgrade_ms_max = 0;


int max_num_upgrades = 9;// all upgrades are (9 max)

int max_health_swordsmen;
int max_mana_swordsmen;
int max_ms_swordsmen;

int max_health_wizard;
int max_mana_wizard;
int max_ms_wizard;

int max_ms_player;


int ms_checker = 0;

//wizard global variable
int lazer[] = {40, 100, 150, 200, 270, 350};// damage list
int random_damage_WIZARD;
int ice;
int ice_math;
int user_fireball;
int enemy_fireball;

int ice_move_indecater;


//ice_math is ice_sideaffect basically		// this needs to be taken after the math
int const fireball_sideaffect = 30;
int const lightning_sideaffect = -40;
int const lazer_sideaffect = -70;

int wizard_sideaffect;
char *wizard_affect_message[1];

//global variable for coins
int coins = 0;

int prize_coins[] = {100, 150, 200};
int reward_index_coins;

//global variable for ms rewards
int prize_ms[] = {45, 70, 100, 150};
int reward_index_ms;

// global variable for the enemy's attack
int random_index;
int enemy;

// global variables for colored (text)
const char* Bright_Black = "\033[90m";
const char* Bright_Red = "\033[91m";
const char* Bright_Green = "\033[92m";
const char* Bright_Yellow = "\033[93m";
const char* Bright_Blue = "\033[94m";
const char* Bright_Magenta = "\033[95m";
const char* Bright_Cyan = "\033[96m";
const char* Bright_White = "\033[97m";

const char* STANDARD_GREEN = "\x1b[32m";
const char* BRIGHT_GREEN = "\x1b[1;32m";

const char* bright_reset = "\033[0m";

//global variable for spacing issue
int wizard_damage[4];
int wizard_MN[4];


int choice;// move number
/* i put (1) cause if i didn't when the UI function runs for the first time it'll take random value
casue it's a global variable and why not (0) cause later on i'm doing [choice - 1] BYE */
// i was wrong WATER-DROP, new update i think it's working correctly HAPPY-FACE idk how though LOL.


int final_spaces_printed_damage_wizard[4];
int final_spaces_printed_MN_wizard[4];
int final_spaces_printed_damage_hero[3];
int final_spaces_printed_MN_hero[3];

int swords_men_damage[3];
int swords_men_MN[3];
    
// MN = mana_cost
typedef struct {
    char name[20];
    int damage;
    int MN;
    int per_round;
} spell;

typedef struct {
    char name[20];
    int health;
    int MN;
    
    spell known_spells[5];
    int num_known_spells;
    int regeneration_MN_per_round;
    int mental_strength;
} character;

character game_character[2];

//function prototypes
int choose_character();
int wizard();
int swords_men();
int fight_enemy();
int hero_info();
int wizard_picture();
int swords_men_picture();
int start_picture();
int UI_fight();
int spacing();
int battle_user_choice();
int battle_enemy_choice();
int winning_screen();
int losing_screen();
int tying_screen();
int mental_strength_player();
int mental_strength_enemy();
int enemy_choice();
int fireball_affect_wizard();
int UI_shop();
int enter_shop();// to enter the shop or not
int max_status_setter();
int upgrade_shop();
int refill_shop();
int chests_shop();
int guide_information_game_book();
int coins_reward();
int ms_reward();
int story();
int killing_screen();
int mental_strength_player_max();

// Global variables to store the max widths for formatting
int max_damage_width = 0;
int max_mana_width = 0;

int main(void){
	//this would make the enemy choice really random
	srand(time(NULL));
	
	story();
	guide_information_game_book();
	
    // c=choice
    int c;
	c = choose_character();

	if (c == 0){
		printf("\nSure well LOL!\n");
		return 0;
	}
	
	wizard();
    swords_men();
    
    max_status_setter(c);
    

	printf("\n");
	enter_shop();// calling this function before any for the shop at the start
	if (shoper == 1){
		UI_shop(c);// displaying the shop
	}
	
	
    spacing();
	

    if (c == 1){
        hero_info(c);
        sleep(3);
        fight_enemy(c);
        sleep(3);
    } else {// i don't need else if (c == 2) cause there are no other possibilities
        hero_info(c);
        sleep(3);
        fight_enemy(c);
        sleep(3);
	}
    
    
    int d = c;
    int game_loop = max_num_upgrades + 1;//number of enemies 				//cause the max_upgrade is 9 and + 1 is (9 + 1)= 10
    int the_winner = 0;
    
    coins_reward();// to show the coins reward in UI_fight
    ms_reward();// to show the ms reward in UI_fight
    UI_fight(c);
    do{
		ice_move_indecater = 0;
		num_rounds++;
		user_fireball = 0;
		enemy_fireball = 0;
		enemy_choice(c);
		battle_user_choice(c);
		battle_enemy_choice(c);
		// affect for the next round
		UI_fight(c);
		fireball_affect_wizard(c);// first UI_fight for the attacks should be after the function that's adjust the fireball affect
		if (game_character[enemy].health <= 0 && game_character[d - 1].health > 0 && game_character[d - 1].mental_strength > 0){
			game_loop--;//player won
			enemy_number++;// to display the num_enemy you're fighting
			the_winner = 1;// to know who won

			coins += prize_coins[reward_index_coins];// you get some money
			game_character[c - 1].mental_strength += prize_ms[reward_index_ms];
			
			mental_strength_player_max(c);
			
			if (game_loop != 0){
				killing_screen();
				sleep(2);
				UI_fight(c);//just to show the updated coins before entering the shop
				enter_shop();// calling this function before any for the shop at the start
				if (shoper == 1){
					UI_shop(c);// displaying the shop
				}
			
				// restarting the enemies status
				if (c == 1){// (enemy) swordsmen
					 game_character[1].health = 1150;
					 game_character[1].MN = 100;
					 game_character[1].regeneration_MN_per_round = 10;
					 game_character[1].mental_strength = 100;
				}else if(c == 2){// (enemy) wizard
					 game_character[0].health = 750;
					 game_character[0].MN = 250;
					 game_character[0].regeneration_MN_per_round = 45;
					 game_character[0].mental_strength = 100;
				}
				num_rounds = 0;// so when the new enemy comes the first (> CRITICAL!) well appear
				coins_reward();
				ms_reward();
				UI_fight(c);
			}
		}else if((game_character[d - 1].health <= 0 || game_character[d - 1].mental_strength <= 0) && (game_character[enemy].health > 0)){
			game_loop = 0;//player lost
			the_winner = 2;// to know who won
		}else if((game_character[enemy].health <= 0 || game_character[enemy].mental_strength <= 0) && (game_character[d - 1].health <= 0 || game_character[d - 1].mental_strength <= 0)){
			game_loop = 0;//a tie
			the_winner = 3;// to know who won
		}
	} while (game_loop != 0);

	
	//winning conditions
	if (the_winner == 1 && game_character[enemy].mental_strength > 0){
		winning_screen();
		printf("%sCongrats you could scroll up to see what happend!\n%s",
				Bright_Green, bright_reset);
	}else if (the_winner == 1 && game_character[enemy].mental_strength <= 0){
		winning_screen();
		printf("%sCongrats even though you won by luck but, game is game. you could scroll up to see what happend!\n%s",
				Bright_Green, bright_reset);
	}else if (the_winner == 2 && game_character[d - 1].mental_strength > 0){
		losing_screen();
		printf("%sYou lost against A CLANKER bruh you should be stripped from your [manly hood] >:(%s\n",
				Bright_Red, bright_reset);
	}else if (the_winner == 2 && game_character[d - 1].mental_strength <= 0){
		losing_screen();
		printf("%sYou lost against A CLANKER, PLUS that wasn't LUCK a skill issuea are you outta your mind, don't show me your face again twin, >:(%s\n",
				Bright_Red, bright_reset);
	}else if (the_winner == 3 && game_character[enemy].mental_strength > 0){
		tying_screen();
		printf("What a disappointment.\n");
	}else if (the_winner == 3 && game_character[enemy].mental_strength <= 0){
		tying_screen();
		printf("What an unmature.\n");
	}

    return 0;
}

//New Game(spoiler_alert there isn't saved game)
int choose_character(){
    int choice;
    
    start_picture();
    
    printf("hello hero which hero would you like to be:\nNOTE: use numbers to choose\n");
    do{
		printf("1.Wizard\n2.Swords_men\n0.Exit\n");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2 && choice != 0);
	
    return choice;
}

//character
int wizard(){
    /*[150_HL, 100_MN, regeneration_MN 15_MN_per_round]
     * attack      5_DM  0_MN $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ still hasn't been added WATER_DROP lol
     * fireball  10_DM 5_MN time_2rounds 
     * ice         3_DM  25_MN time_3rounds
     * lightning 35_DM 40_MN time_1rounds */
     // special move LAZER 100_DM 60_MN
     
     strcpy(game_character[0].name, "Wizard");
     game_character[0].health = 750;
     game_character[0].MN = 250;
     game_character[0].regeneration_MN_per_round = 45;
     game_character[0].mental_strength = 100;
    
     strcpy(game_character[0].known_spells[0].name, "Fireball");
     wizard_damage[0] = game_character[0].known_spells[0].damage = 100;
     wizard_MN[0] = game_character[0].known_spells[0].MN = 70;
     game_character[0].known_spells[0].per_round = 5;
     strcpy(game_character[0].known_spells[1].name, "Ice");
     wizard_damage[1] = game_character[0].known_spells[1].damage = 70;
     wizard_MN[1] = game_character[0].known_spells[1].MN = 30;
     game_character[0].known_spells[1].per_round = 5;
     strcpy(game_character[0].known_spells[2].name, "Lightning");
     wizard_damage[2] = game_character[0].known_spells[2].damage = 170;
     wizard_MN[2] = game_character[0].known_spells[2].MN = 60;
     game_character[0].known_spells[2].per_round = 0;//1 means only during this round which is instant
    
     strcpy(game_character[0].known_spells[3].name, "LAZER");
     wizard_damage[3] = game_character[0].known_spells[3].damage = 0;
     wizard_MN[3] = game_character[0].known_spells[3].MN = 100;
     game_character[0].known_spells[3].per_round = 30;;//1 means only during this round which is instant
    
     game_character[0].num_known_spells = 4;


    return 0;
}

//character
int swords_men(){
	// the new status is from a hand written paper
	
     /*[250_HL, 50_MN, regeneration_MN 4_MN_per_round]
      * attack   15_DM 0_MN
      * sword   20_DM 10_MN */
      // special move samurai_slice 150_DM 35_MN (((((((+ increase damage 15% every_round))))))
     strcpy(game_character[1].name, "Swords_men");
     game_character[1].health = 1150;
     game_character[1].MN = 100;
     game_character[1].regeneration_MN_per_round = 10;
     game_character[1].mental_strength = 100;
    
     strcpy(game_character[1].known_spells[0].name, "Attack");
     swords_men_damage[0] = game_character[1].known_spells[0].damage = 35;
     swords_men_MN[0] = game_character[1].known_spells[0].MN = 15;
     game_character[1].known_spells[0].per_round = 0;
     strcpy(game_character[1].known_spells[1].name, "Sword");
     swords_men_damage[1] = game_character[1].known_spells[1].damage = 50;
     swords_men_MN[1] = game_character[1].known_spells[1].MN = 0;
     game_character[1].known_spells[1].per_round = 4;
    
     strcpy(game_character[1].known_spells[2].name, "SAMURAI_SLICE");
     swords_men_damage[2] = game_character[1].known_spells[2].damage = 200;
     swords_men_MN[2] = game_character[1].known_spells[2].MN = 25;
     game_character[1].known_spells[2].per_round = 33;//1 means only during this round which is instant
    
     game_character[1].num_known_spells = 3;
    
    
    return 0;
}

//enemy
int fight_enemy(int c){
    int n_moves_enemy;
    
    if (c == 1){
        enemy = 1;
        swords_men_picture();
        n_moves_enemy = game_character[enemy].num_known_spells;
    } else if (c == 2){
        enemy = 0;
        wizard_picture();
        n_moves_enemy = game_character[enemy].num_known_spells;
    }
    
    printf("Enemy: %s\n",game_character[enemy].name);
    
    printf("Moves:");
    for (int i = 0; i < n_moves_enemy; i++){
        printf("    %d.%s", i + 1, game_character[enemy].known_spells[i].name);
}
    printf("\n");
             
    return 0;
}

//player
int hero_info(int c){
    int n_moves_hero;
         
    if (c == 1){
        n_moves_hero = game_character[0].num_known_spells;
        wizard_picture();
    } else if (c == 2){
        n_moves_hero = game_character[1].num_known_spells;
        swords_men_picture();
    }
    
    c--;
    printf("\nHero: %s\n",game_character[c].name);
    
    printf("Moves:");
    for (int i = 0; i < n_moves_hero; i++){
        printf("    %d.%s", i + 1, game_character[c].known_spells[i].name);
    }
    printf("\n\n");
    
    return 0;
}

//image
int wizard_picture(){
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣶⠟⠛⠉⠉⠉⠛⠻⢿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⣍⠻⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⣄⠛⢿⣶⣄⣠⡾⣧⡀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⣦⡉⠻⣫⣾⡽⣷⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⣀⣀⡀⠀⠀⠀⠀⣀⣀⡀⠀⠸⣿⠻⣿⣾⡿⠃⠹⣿⣷⡀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠟⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⣿⣇⠀⠉⠀⠀⠀⠈⠛⠛⠒⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠃⢀⣀⣠⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣀⡀⠘⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⡿⠿⠟⠋⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠙⠛⠿⢿⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⢀⣠⣴⣾⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣷⣦⣄⡀⠀⠀⠀⠀\n"
           "⠀⣀⣴⣾⣿⣛⣁⣤⣤⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣠⣤⣌⣛⣿⣷⣦⣀⠀\n"
           "⣼⡿⣿⣿⣿⣿⣿⣿⠋⠉⢹⡿⠻⣿⣿⡶⠒⠒⠲⣶⣶⣶⣶⣶⣶⡶⠖⠒⠲⢾⣿⣿⠟⢿⡏⠉⠙⣿⣿⣿⣿⣿⣿⢿⣷\n"
           "⢹⣷⡙⢿⣿⣿⠾⠍⠁⠀⣾⠇⠀⢻⠀⢈⣻⣷⣶⣤⣤⡽⠟⢯⣤⣤⣴⣾⣿⡁⠀⡟⠀⠘⣷⠀⠈⠩⠷⣿⣿⡿⢋⣾⡟\n"
           "⠀⠙⢿⣶⣭⣛⡿⠷⠤⣼⠏⢠⢶⣾⠀⠀⠙⠓⢦⣼⣿⡇⠀⢸⣿⣧⣴⠟⠋⠀⠀⣿⡄⡄⠹⣧⠤⠾⠿⣛⣭⣴⡿⠋⠀\n"
           "⠀⠀⠀⠈⠛⠻⠿⣷⣶⠟⢰⡏⢸⣇⠀⠀⠀⠈⠉⢉⣹⠇⠀⠘⣏⡉⠉⠁⠀⠀⠀⢸⡇⢹⡆⠻⣶⣾⠿⠟⠛⠉⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⢠⡏⢠⡟⠀⣼⣿⣄⠀⠀⠀⡼⠋⠻⠀⠀⠀⠾⠉⢳⡀⠀⠀⣠⣿⣷⠀⢹⡄⢹⣆⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⢀⣟⣠⡿⢀⣼⡇⢹⣝⡷⣤⣼⣳⠴⠛⠳⠤⠔⠛⠦⣞⣷⣤⢴⣫⡟⠸⣷⡀⢿⣄⣻⡀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠸⢋⣿⠁⣼⢹⣆⠀⠉⠛⠛⠉⠁⠀⠀⣀⣿⣄⠀⠀⠀⠉⠛⠛⠉⠀⢠⡏⢧⠀⢿⡝⠇⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⣼⡇⣰⠃⠈⢿⣦⣄⣀⣀⣀⣤⡴⠞⠋⠉⠉⠳⢦⣤⣀⣀⣀⣠⣴⡿⠁⠘⣦⢸⣷⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⢿⣿⡏⢠⠄⢸⣧⠉⠉⢻⣀⣠⡶⠞⠛⠉⠛⠳⢶⣤⣀⡟⠉⠉⢸⡇⠀⡄⢹⡿⠟⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⢸⣡⡏⠀⡄⢿⡀⠀⠀⠛⠉⠀⠀⠀⠀⠀⠀⠀⠉⠛⠁⠀⢀⡿⢡⡀⢹⣬⡇⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠸⡿⣇⢸⣿⢸⣷⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⣾⡇⣼⣧⣸⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⠹⣿⡏⡿⣧⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣾⣿⠻⣿⠏⢿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠁⠀⠻⣿⣦⣾⠀⠀⠀⠀⠀⣶⣤⡟⠟⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⢻⣧⡀⠀⠀⣼⡿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣦⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
    );
    
    return 0;
}

//image
int swords_men_picture(){
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠤⢴⣾⣿⣿⣿⣯⠘⠳⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⡟⣾⣿⣿⣠⢠⣀⢻⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠒⢫⣿⣿⣿⣿⣿⣿⢸⡗⣾⣙⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣧⢮⡯⣷⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⡐⣚⣛⡛⠛⠉⢹⣽⣿⣽⠮⠓⣫⣏⠀⠀⣀⣀⣀⡀⠀⠀⠀⠀⠀\n"
           "⠀⠀⢀⣴⠟⠋⠩⠉⢩⣷⣾⣿⣽⣷⣿⠤⢋⡥⠚⠳⣾⡏⠉⠉⠙⠻⢦⡀⠀⠀\n"
           "⠀⢀⡿⢁⠈⢀⡠⢔⣣⠟⠿⣿⣿⣿⣗⡪⠇⠀⣢⡾⠛⣮⡢⢄⡀⠐⡈⢻⡄⠀\n"
           "⣾⠷⠥⠉⠑⡪⣽⠧⠀⠀⠨⡻⣟⣿⠀⣠⠞⡁⠀⠀⠚⣯⣇⡊⠉⠬⠾⣻⡆\n"
           "⡿⠤⣆⣒⡬⠞⣿⡑⠀⠀⠀⠀⠈⢳⣞⠁⠀⠀⠀⠀⢁⣿⠳⢥⣒⣨⠤⢿⣅\n"
           "⣿⣿⢋⠁⠀⢰⡇⠀⠀⠀⢠⢞⢿⣭⡍⢻⢦⡀⠀⠀⠀⢼⡇⠀⠈⠝⣿⣿⡟\n"
           "⠀⣹⡏⢀⣀⣀⣸⣇⣀⣀⣀⣘⣛⣾⢶⠿⠿⣷⣽⡟⠓⢲⠶⠧⢤⣀⡠⢸⣏⠀\n"
           "⢠⣿⡟⡿⡝⠀⠐⠀⠁⠈⠈⡽⠁⠀⢸⣓⣚⣿⣿⠧⣤⣄⡀⠀⠀⠈⣽⣧⣿⡀\n"
           "⠘⢷⣧⣿⢷⣤⣤⣴⡶⣶⣾⣷⢤⣤⢾⠭⢭⣿⣿⣿⣶⣭⣝⡛⠶⠶⣳⣼⣿⡇\n"
           "⠀⠀⠙⠛⠛⠚⠛⠛⣿⣿⣿⣿⣟⣷⡿⠓⠛⠻⠿⢿⠟⢿⠉⠛⠻⠯⠴⠶⠛⠁\n"
           "⠀⠀⠀⠀⠀⠀⠀⢠⣿⣽⡯⢿⣿⡟⠷⠶⢲⡖⠶⢼⣴⣾⣔⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⢀⡾⠁⠈⠛⠷⣾⣧⠀⠀⢸⣶⢾⠛⠉⠔⢿⣂⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⣼⠍⠂⠀⢠⢣⣿⣷⠀⠄⢸⣿⡞⡄⠀⠀⡨⢷⠆⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⢸⡣⣄⡀⠀⣎⣿⣿⣿⠀⡀⢺⣿⣿⡸⡀⢀⡰⢝⡧⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠉⠓⠮⠽⣼⠛⠿⠿⠤⠤⠿⠿⠛⢷⠯⠵⠚⠋⠀⠀⠀⠀⠀⠀\n"
    );
    
    return 0;
}

//image
int start_picture(){
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣫⣶⣾⣿⣿⣶⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣷⣶⣾⣽⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠉⠀⠀⠈⠙⣷⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣱⠟⠉⠀⠀⠀⠉⠿⣟⢿⡿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⡏⣼⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⠇⠁⠀⠀⠀⠀⠀⠀⠀⠹⣟⣷⢹⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⡇⣿⢸⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⢸⣿⢻⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⡸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⢠⢿⡏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣹⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣾⣿⣾⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣯⣷⣻⣿⣦⣀⠀⠀⠀⠀⣠⣴⢯⣾⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡽⣧⡠⣤⡀⠀⠀⠀⠀⣠⣾⠟⢩⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⢟⣹⡿⣳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣌⠻⣮⣙⣿⣶⣶⣟⣋⣵⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣯⣛⡷⠬⢭⣉⣩⣴⣿⣫⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣝⣛⣻⣿⣟⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⡟⠉⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣷⡞⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣦⣈⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣇⣠⡿⠉⠙⣿⡿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠉⢻⡇⠈⢿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡇⢠⡾⠋⢠⡏⠀⠀⣹⣿⢟⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠹⣿⣧⠙⢿⣧⠀⢸⣷⣤⣼⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⢸⡀⢀⣴⠟⠁⢸⡏⠀⠀⣸⣿⣿⣿⠉⠀⠀⢻⣿⣿⣿⠁⠀⠈⣿⣿⣿⣟⠁⠀⢸⣿⠃⠹⣧⠀⠀⣹⣿⠀⠀⢻⣦⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣷⣿⣟⠀⠀⢸⡇⠀⢰⡿⠁⢸⣿⠀⠀⠀⣾⡏⠻⣿⡀⠀⠀⣿⡇⠹⣿⡀⠀⢸⣿⠀⠀⠸⣦⢠⣿⡿⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⣸⣷⡀⣿⠇⠀⠈⢿⣇⠀⣸⡿⠀⠀⢻⣧⠀⣾⡿⠀⠀⢹⣧⠀⣼⣿⡄⠀⢀⣿⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⢀⣾⣿⣶⣿⣧⠀⠀⢠⣿⣷⣿⠁⠀⠀⣸⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣴⣿⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
	);
    
    return 0;
}

// way too complicated [i shoud've putten comments]
int UI_fight(int c){
    int n_enemy_moves;
    int n_hero_moves;
    int d;
    int user_attack;
    int enemy_attack;

    if (c == 1){
        enemy = 1;
        n_enemy_moves = game_character[enemy].num_known_spells;
        n_hero_moves = game_character[0].num_known_spells;
    } else if (c == 2){
        enemy = 0;
        n_enemy_moves = game_character[enemy].num_known_spells;
        n_hero_moves = game_character[1].num_known_spells;
    }
    d = c;
    d = d - 1;
    printf("\n\n\n%sYou're going to fight the enemy: %s\n-------------------------------------------------------\nAnd if you kill him you'll get gold: %d\nAnd you'll get mental_strength: %d					enemy_number: %d%s\n\n\n", // i don't know why there is \n that doesn't work
			Bright_Magenta,
			game_character[enemy].name,
			prize_coins[reward_index_coins],
			prize_ms[reward_index_ms],
			enemy_number,
			bright_reset);
			
	if (strcmp(game_character[c - 1].known_spells[choice - 1].name, "LAZER") == 0){
		user_attack = lazer[random_damage_WIZARD];
	} else{
		user_attack = game_character[c - 1].known_spells[choice - 1].damage;
	}
	
	
	if (strcmp(game_character[enemy].known_spells[random_index].name, "LAZER") == 0){
		enemy_attack = lazer[random_damage_WIZARD];
	} else{
		enemy_attack = game_character[enemy].known_spells[random_index].damage;
	}


    for (int j = 0; j < 2; j++){
        if (j == 0){
			if (num_rounds > 0){
				printf("> %sCRITICAL! %s: %d Damage dealt, %d Mana Cost.%s\n",
						Bright_Yellow,
						game_character[c - 1].known_spells[choice - 1].name,
						user_attack,
						game_character[c - 1].known_spells[choice - 1].MN,
						bright_reset);
				if (c == 1){// the user is wizard
					printf("> %sCRITICAL! Side-Affect: %d_dm Explanation: (%s)%s\n",
								Bright_Yellow,
								wizard_sideaffect,
								wizard_affect_message[0],
								bright_reset);
								
					if (ice_move_indecater > 0){
						printf("> %sCRITICAL! Move: %s damage_affect: [%d ---> %d]%s\n",
							Bright_Yellow,
							game_character[c - 1].known_spells[choice - 1].name,
							game_character[enemy].known_spells[random_index].damage,
							ice_math,
							bright_reset);
					}
				}
			}
            printf("%sHealth:%-4d      %sMN:%-4d      %sregeneration_MN_per_round:%-4d      %smental_strength:%-4d%s\n",
					Bright_Red,
                    game_character[enemy].health,
                    Bright_Blue,
                    game_character[enemy].MN,
                    Bright_Green,
                    game_character[enemy].regeneration_MN_per_round,
                    Bright_Green,// had to, to make it alligned for the spaces
                    game_character[enemy].mental_strength,
                    bright_reset);

            printf("+---------------------------------------------------------------------------+\n");

            printf("%s[Spells]%s\n", Bright_Cyan, bright_reset);
            for (int i = 0; i < n_enemy_moves; i++){
                    printf("   [%d]%-13s       <Damage=%-*d Mana_Cost=%-*d Per_Round=%d>\n",
                            i + 1,
                            game_character[enemy].known_spells[i].name,
                            max_damage_width + 5,
                            game_character[enemy].known_spells[i].damage,
                            max_mana_width + 5,
                            game_character[enemy].known_spells[i].MN,
                            game_character[enemy].known_spells[i].per_round);
                }
        } else if (j == 1){
			printf("\n\n\n");
			if (num_rounds > 0){
				printf("> %sCRITICAL! %s: %d Damage dealt, %d Mana Cost.%s\n",
						Bright_Yellow,
						game_character[enemy].known_spells[random_index].name,
						enemy_attack,
						game_character[enemy].known_spells[random_index].MN,
						bright_reset);
				if (c == 2){// the user is wizard
					printf("> %sCRITICAL! Side-Affect: %d_dm Explanation: (%s)%s\n",
								Bright_Yellow,
								wizard_sideaffect,
								wizard_affect_message[0],
								bright_reset);
								
					if (ice_move_indecater > 0){
						printf("> %sCRITICAL! Move: %s damage_affect: [%d ---> %d]%s\n",
							Bright_Yellow,
							game_character[enemy].known_spells[random_index].name,// you could just print the name manually
							game_character[c - 1].known_spells[choice - 1].damage,
							ice_math,
							bright_reset);
					}
				}
			}
            printf("%sHealth:%-4d      %sMN:%-4d      %sregeneration_MN_per_round:%-4d      %smental_strength:%-4d%s\n",
					Bright_Red,
                    game_character[d].health,
                    Bright_Blue,
                    game_character[d].MN,
                    Bright_Green,
                    game_character[d].regeneration_MN_per_round,
                    Bright_Green,
                    game_character[d].mental_strength,
                    bright_reset);

            printf("+---------------------------------------------------------------------------+\n");

            printf("%s[Spells]%s\n", Bright_Cyan, bright_reset);
            for (int i = 0; i < n_hero_moves; i++){
                printf("   [%d]%-13s       <Damage=%-*d Mana_Cost=%-*d Per_Round=%d>\n",
                        i + 1,
                        game_character[d].known_spells[i].name,
                        max_damage_width + 5,
                        game_character[d].known_spells[i].damage,
                        max_mana_width + 5,
                        game_character[d].known_spells[i].MN,
                        game_character[d].known_spells[i].per_round);
            }
            printf("\n\n");
		}
    }
    printf("%s								Coins:%d%s\n", Bright_Yellow, coins, bright_reset);
	return 0;
}

// it turns out there is an easier way, way easier lol [%-10s] hahah
int spacing(){
    //i will use this function to make spacing and fix the formatting problem 
    for (int i = 0; i < 4; i++){
        final_spaces_printed_damage_wizard[i] = 1;
        int damage = wizard_damage[i];
        while (damage >= 10){
            damage = damage / 10;
            final_spaces_printed_damage_wizard[i]++;
        }
        
    }
    
    for (int i = 0; i < 4; i++){
        final_spaces_printed_MN_wizard[i] = 1;
        int mana = wizard_MN[i];
        while (mana >= 10){
            mana = mana / 10;
            final_spaces_printed_MN_wizard[i]++;
        }
    }
    
    for (int i = 0; i < 3; i++){
        final_spaces_printed_damage_hero[i] = 1;
        int damage = swords_men_damage[i];
        while (damage >= 10){
            damage = damage / 10;
            final_spaces_printed_damage_hero[i]++;
        }
    }
    
    for (int i = 0; i < 3; i++){
        final_spaces_printed_MN_hero[i] = 1;
        int mana = swords_men_MN[i];
        while (mana >= 10){
            mana = mana / 10;
            final_spaces_printed_MN_hero[i]++;
        }
    }
    
    
    //now i will take the max of each of the four arrays
    int max_spaces_damage_wizard = 0;
    int max_spaces_MN_wizard = 0;
    int max_spaces_damage_hero = 0;
    int max_spaces_MN_hero = 0;
    
    for (int i = 0; i < 4; i++){
        if (final_spaces_printed_damage_wizard[i] > max_spaces_damage_wizard){
            max_spaces_damage_wizard = final_spaces_printed_damage_wizard[i];
        }
    }
    
    for (int i = 0; i < 4; i++){
        if (final_spaces_printed_MN_wizard[i] > max_spaces_MN_wizard){
            max_spaces_MN_wizard = final_spaces_printed_MN_wizard[i];
        }
    }
    
    for (int i = 0; i < 3; i++){
        if (final_spaces_printed_damage_hero[i] > max_spaces_damage_hero){
            max_spaces_damage_hero = final_spaces_printed_damage_hero[i];
        }
    }
    
    for (int i = 0; i < 3; i++){
        if (final_spaces_printed_MN_hero[i] > max_spaces_MN_hero){
            max_spaces_MN_hero = final_spaces_printed_MN_hero[i];
        }
    }
    
    // Set the global variables with the overall maximum widths
    if (max_spaces_damage_wizard > max_spaces_damage_hero) {
        max_damage_width = max_spaces_damage_wizard;
    } else {
        max_damage_width = max_spaces_damage_hero;
    }

    if (max_spaces_MN_wizard > max_spaces_MN_hero) {
        max_mana_width = max_spaces_MN_wizard;
    } else {
        max_mana_width = max_spaces_MN_hero;
    }
    
    return 0;
}


int battle_user_choice(int c){// reminder you need to do (c-1) cause the index starts from 0 in c
	// (c-1) would be the user's character (c) would be the enemy's
	int const wizard_MN_max = 250;
	int const swordsmen_MN_max = 100;
	int player_MN_max;
	int d = c;
	int a = 1;
	
	
	//first know the user character to know how many moves are allowed to choose from
	if (c == 1){// wizard (4 moves)
		do{
			printf("Move: ");
			scanf("%d", &choice);
		} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
		player_MN_max = wizard_MN_max;
		enemy = 1;// swordsmen index
	} else if (c == 2){// swordsmen (3 moves)
		do{
			printf("Moves: ");
			scanf("%d", &choice);
		} while (choice != 1 && choice != 2 && choice != 3);
		player_MN_max = swordsmen_MN_max;
		enemy = 0;// wizard index
	}
	printf("\n\n");
		
		
	// mana cost section
		//user's character			//user's character
		do{
			if (game_character[c - 1].MN < game_character[c - 1].known_spells[choice - 1].MN || mental_strength_player(c, choice)){
				if (d == 1){// wizard
					do{
						printf("You can't choose: %d choose something else\n", choice);
						printf("Move: ");
						scanf("%d", &choice);
					} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
				}else if (d == 2){// swordsmen
					do{
						printf("You can't choose: %d choose something else\n", choice);
						printf("Move: ");
						scanf("%d", &choice);
					} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
				}
			}else if (game_character[c - 1].MN >= game_character[c - 1].known_spells[choice - 1].MN){
					game_character[c - 1].MN -= game_character[c - 1].known_spells[choice - 1].MN;
					a = 0;
			}
		} while(a == 1);
		
		
	//enemy's character			//user's character------------don't follow the left comments
	if (c == 2){// swordsmen
		// for swordsmen attacks
		game_character[enemy].health -= game_character[c - 1].known_spells[choice - 1].damage;
		// all other else_if's are for WIZARD special side affects
	} else if (strcmp(game_character[c - 1].known_spells[choice - 1].name, "LAZER") == 0){
		random_damage_WIZARD = rand() % 6;
		if (random_damage_WIZARD == 3 || random_damage_WIZARD == 4){
			game_character[enemy].health -= lazer[random_damage_WIZARD];
			game_character[c - 1].health += lazer_sideaffect;// it's a draw back from the LAZER move
			// i used  + cause + * - is -
			wizard_sideaffect = lazer_sideaffect;
			wizard_affect_message[0] = "33% chance of getting 70_dm as a side_affect";
		} else{
			game_character[enemy].health -= lazer[random_damage_WIZARD];
			wizard_sideaffect = 0;
			wizard_affect_message[0] = "33% chance of getting 70_dm as a side_affect";
		}
	} else if (strcmp(game_character[c - 1].known_spells[choice - 1].name, "Lightning") == 0){
		random_damage_WIZARD = rand() % 2;
		if (random_damage_WIZARD == 0){//if it's 0 you won't get hurt if it's 1 you get hurt draw back
			game_character[enemy].health -= game_character[c - 1].known_spells[choice - 1].damage;
			wizard_sideaffect = 0;
			wizard_affect_message[0] = "50% chance of geting 50_dm as a side_affect";
		} else{
			game_character[enemy].health -= game_character[c - 1].known_spells[choice - 1].damage;
			game_character[c - 1].health += lightning_sideaffect;// it's a draw back from the LAZER move
			// i used  + cause + * - is -
			wizard_sideaffect = lightning_sideaffect;
			wizard_affect_message[0] = "50% chance of geting 50_dm as a side_affect";
		}
	} else if (strcmp(game_character[c - 1].known_spells[choice - 1].name, "Ice") == 0){
		game_character[enemy].health -= game_character[c - 1].known_spells[choice - 1].damage;
		ice = 15;
		// type cast to float then round it up to the nearest integer
		ice_math = round((float)game_character[enemy].known_spells[random_index].damage * (float)ice / 100.0);
		//reverse math to make it look as ice -15% decrease damage is working
		game_character[c - 1].health += ice_math;
		wizard_sideaffect = ice_math;
		wizard_affect_message[0] = "-15% decrease the damage you get from the opponenets attack";
		
		ice_move_indecater++;
	} else if (strcmp(game_character[c - 1].known_spells[choice - 1].name, "Fireball") == 0){
		game_character[enemy].health -= game_character[c - 1].known_spells[choice - 1].damage;
		user_fireball = 1;
		wizard_sideaffect = fireball_sideaffect;
		wizard_affect_message[0] = "in the next round the opponent well get 30_dm cause of fire";
	}
		
		
	// mana generation section
		//user's character
		game_character[c - 1].MN += game_character[c - 1].regeneration_MN_per_round;
		if (game_character[c - 1].MN >= player_MN_max){
			game_character[c - 1].MN = player_MN_max;
		}
		

	
	
	
	return 0;
}


int battle_enemy_choice(int c){
	int enemy_MN_max;
	int const wizard_MN_max = 250;
	int const swordsmen_MN_max = 100;

	if (c == 1){// wizard for player (4 moves)
		enemy_MN_max = swordsmen_MN_max;
		enemy = 1;
	} else if (c == 2){// swordsmen for player (3 moves)
		enemy_MN_max = wizard_MN_max;
		enemy = 0;
	}
	

	//user's character				//enemy's character------------don't follow the left comments
	if (c == 1){// which means swordsmen for enemy
		// for swordsmen attacks
		game_character[c - 1].health -= game_character[enemy].known_spells[random_index].damage;
	} else if (strcmp(game_character[enemy].known_spells[random_index].name, "LAZER") == 0){
		random_damage_WIZARD = rand() % 6;
		if (random_damage_WIZARD == 3 || random_damage_WIZARD == 4){
			game_character[c - 1].health -= lazer[random_damage_WIZARD];
			game_character[enemy].health += lazer_sideaffect;// it's a draw back from the LAZER move
			// i used  + cause + * - is -
			wizard_sideaffect = lazer_sideaffect;
			wizard_affect_message[0] = "33% chance of getting 70_dm as a side_affect";
		} else{
			game_character[c - 1].health -= lazer[random_damage_WIZARD];
			wizard_sideaffect = 0;
			wizard_affect_message[0] = "33% chance of getting 70_dm as a side_affect";
		}
	} else if (strcmp(game_character[enemy].known_spells[random_index].name, "Lightning") == 0){
		random_damage_WIZARD = rand() % 2;
		if (random_damage_WIZARD == 0){//if it's 0 you won't get hurt if it's 1 you get hurt draw back
			game_character[c - 1].health -= game_character[enemy].known_spells[random_index].damage;
			wizard_sideaffect = 0;
			wizard_affect_message[0] = "50% chance of geting 50_dm as a side_affect";
		} else{
			game_character[c - 1].health -= game_character[enemy].known_spells[random_index].damage;
			game_character[enemy].health += lightning_sideaffect;
			// i used  + cause + * - is -
			wizard_sideaffect = lightning_sideaffect;
			wizard_affect_message[0] = "50% chance of geting 50_dm as a side_affect";
		}
	} else if (strcmp(game_character[enemy].known_spells[random_index].name, "Ice") == 0){
		game_character[c - 1].health -= game_character[enemy].known_spells[random_index].damage;
		ice = 15;
		ice_math = round((float)game_character[c - 1].known_spells[choice - 1].damage * (float)ice / 100.0);
		//reverse math to make it look as ice -15% decrease damage is working
		game_character[enemy].health += ice_math;
		wizard_sideaffect = ice_math;
		wizard_affect_message[0] = "-15% decrease the damage you get from the opponenets attack";
		
		ice_move_indecater++;
	} else if (strcmp(game_character[enemy].known_spells[random_index].name, "Fireball") == 0){
		game_character[c - 1].health -= game_character[enemy].known_spells[random_index].damage;
		enemy_fireball = 1;
		wizard_sideaffect = fireball_sideaffect;
		wizard_affect_message[0] = "in the next round the opponent well get 30_dm cause of fire";
	}
	
	
	// mana generation section
		//enemy's character
		game_character[enemy].MN += game_character[enemy].regeneration_MN_per_round;
		if (game_character[enemy].MN >= enemy_MN_max){
			game_character[enemy].MN = enemy_MN_max;
		}
	
	return 0;
}

// this function is for to fix the ice special move cause it needs to be called before the user move
int enemy_choice(int c){	
	int const num_wizard = 4;
	int const num_swordsmen = 3;
	
	if (c == 1){// wizard (4 moves)
		enemy = 1;// swordsmen index
		do{
			random_index = rand() % num_swordsmen;// enemy's choice
			mental_strength_enemy(enemy, random_index);
		}while (game_character[enemy].MN < game_character[enemy].known_spells[random_index].MN || ms_checker == 0);
	} else if (c == 2){// swordsmen (3 moves)
		enemy = 0;// wizard index
		do{
			random_index = rand() % num_wizard;// enemy's choice
			mental_strength_enemy(enemy, random_index);
		}while (game_character[enemy].MN < game_character[enemy].known_spells[random_index].MN || ms_checker == 0);
	}
	
	game_character[enemy].mental_strength -= game_character[enemy].known_spells[random_index].per_round;
	game_character[enemy].MN -= game_character[enemy].known_spells[random_index].MN;
	
	return 0;
}


//image
int winning_screen(){
	printf("%s"
           "⠀⠀⠀⣀⡤⣄⡀⠀⠀⠀⡔⣾⠭⠽⡲⣄⠀⠀⠀⠀\n"
           "⠀⠀⢰⡱⠉⠉⠺⣷⢎⣴⠏⠀⠀⠀⣿⢠⡇⠀⠀⠀\n"
           "⠀⠀⡞⣇⠀⠀⠀⠉⡾⠃⠀⠀⠀⢰⡹⡍⠀⠀⠀⠀\n"
           "⠀⠀⠘⣞⢆⠀⣴⡟⠁⠀⠀⠀⢀⡯⠃⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⢱⢓⠏⠁⠀⠀⠀⣔⣟⣳⣆⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⡴⡷⠃⠀⠀⠀⢀⡞⠁⠀⢸⣿⡻⣧⠀⠀⠀\n"
           "⠀⠀⢠⡟⠁⠀⠀⠀⣠⠇⠀⠀⣠⠋⠀⠀⣿⣒⡲⡄\n"
           "⠀⣰⡟⠁⠀⠀⠀⡜⠁⠀⢀⡎⠁⠀⢠⠎⠀⠀⣼⡇\n"
           "⢠⣿⠃⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⢠⠏⠀⠀⡴⣽⠁\n"
           "⣯⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⡏⠀\n"
           "⢹⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⠏⠀⠀\n"
           "⠀⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣮⠛⠀⠀⠀⠀\n"
           "⠀⠈⠂⠇⠀⠀⠀⠀⠀⠀⠀⢠⣮⠋⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠐⠁⠀⠀⠀⠀⠀⠀⠀\n"
           "%s",
           Bright_Green,
           bright_reset
    );
    return 0;
}

//image
int losing_screen(){
    printf("%s"
           "███    ███\n"
           " ███  ███ \n"
           "  ███ ███ \n"
           "   █████  \n"
           "  ███ ███ \n"
           " ███  ███ \n"
           "███    ███\n"
           "%s",
           Bright_Red,
           bright_reset
    );
    return 0;
}

//image
int tying_screen(){
    printf(" _____       _     _____\n"
           "|_  _|     |_|   |  ___|\n"
           "  | |        _    | |__  \n"
           "  | |      | |    |  __| \n"
           "  | |      | |    | |___ \n"
           "  |_|      \\_/    \\____/ \n"
	);
    return 0;
}

//calculates ms(aka mental_strength) for player
int mental_strength_player(int c, int choice){
	if (game_character[c - 1].mental_strength >= game_character[c - 1].known_spells[choice - 1].per_round){
		game_character[c - 1].mental_strength -= game_character[c - 1].known_spells[choice - 1].per_round;
	}else {
		return 1;
	}
	
	return 0;
}

int mental_strength_player_max(int c){
	if (game_character[c - 1].mental_strength > max_ms_player){
		game_character[c - 1].mental_strength = max_ms_player;
	}
	
	return 0;
}

//calculates ms(aka mental_strength) for enemy
int mental_strength_enemy(int enemy, int random_index){
	if (game_character[enemy].mental_strength >= game_character[enemy].known_spells[random_index].per_round){
		ms_checker = 1;
	}else{
		ms_checker = 0;
	}
	
	return 0;
}

int fireball_affect_wizard(int c){
	if (c == 1){//user_wizard
		if (user_fireball == 1){//user_used_fireball
			game_character[enemy].health -= fireball_sideaffect;
			// i used  + cause + * - is -
			// that's false for some reason
		}
	} else {//enemy_wizard
		if (enemy_fireball == 1){//enemy_used_fireball
			game_character[c - 1].health -= fireball_sideaffect;
			// i used  + cause + * - is -
			// that's false for some reason
		}
	}
	
	return 0;
}


int UI_shop(int c){
	int upgrade_choice;
	
	int refill;
	
	int quit;
	int keeploop = 0;
	
	
	
	do{
		//for design
		printf("\n\n%s--+++--------------------------------------------------------------------------------------------------+++--%s\n",
				Bright_Magenta, bright_reset);
		// display status to be aware
		printf("%sHealth:%-4d      %sMN:%-4d      %smental_strength:%-4d      %sCoins: %-4d%s\n",
						Bright_Red,
						game_character[c - 1].health,
						Bright_Blue,
						game_character[c - 1].MN,
						Bright_Green,
						game_character[c - 1].mental_strength,
						Bright_Yellow,
						coins,
						bright_reset);
		printf("\n\n");
		
		//upgrades
		do{
			printf("[UPGRADES-COST]: %s100%s\n1.Upgrade_Health, 2.Upgrade_mana, 3.Upgrade_ms, 4.Skip\n",
					Bright_Yellow,
					bright_reset);
			scanf("%d", &upgrade_choice);		
		} while (upgrade_choice < 1 || upgrade_choice > 4);// when choosing for it'll skip it
		
		upgrade_shop(c, upgrade_choice);
		
		
		
		printf("\n");
		//refills
		do{
			printf("[REFILL-COST]: %s50%s\n1.Refill_Health, 2.Refill_mana, 3.Refill_ms, 4.Skip\n",
					Bright_Yellow,
					bright_reset);
			scanf("%d", &refill);		
		} while (refill < 1 || refill > 4);// when choosing for it'll skip it
		
		refill_shop(c, refill);


		
		printf("\n");
		//chests
		do{
			printf("[CHESTS]:\n1.Upgrades_Chest: %s70%s, 2.Refill_Chest: %s35%s, 3.Coins_Chest: %s70%s, 4.Skip\n",
					Bright_Yellow,
					bright_reset,
					Bright_Yellow,
					bright_reset,
					Bright_Yellow,
					bright_reset);
			scanf("%d", &chest_choice);
		} while (chest_choice < 1 || chest_choice > 4);
		chests_shop(c);
		printf("%d\n\n\n", coins);
		
		
		//to show the updates
		printf("%sHealth:%-4d      %sMN:%-4d      %smental_strength:%-4d      %sCoins: %-4d%s\n",
						Bright_Red,
						game_character[c - 1].health,
						Bright_Blue,
						game_character[c - 1].MN,
						Bright_Green,
						game_character[c - 1].mental_strength,
						Bright_Yellow,
						coins,
						bright_reset);
		
		
		printf("0.don't quit\n1.quit\n");
		scanf("%d", &quit);
		if (quit == 1){
			keeploop = 1;
		}
		
		//for design
		printf("\n%s--+++--------------------------------------------------------------------------------------------------+++--%s",
			Bright_Magenta, bright_reset);// no need for \n at the end cause somewhere in this project it's being used after this
	} while (keeploop != 1);
	
	return 0;
}

int enter_shop(){
	int enter;
	
	do{
		shoper = 0;// or do else{ shoper = 0;} 
		printf("1.Shop!\n2.No_Shop\n");
		scanf("%d", &enter);
	} while (enter < 1 || enter > 2);
	
	if (enter == 1){
		shoper = 1;
	}
	
	return 0;
}

int max_status_setter(int c){
	max_health_swordsmen = game_character[1].health;
	max_mana_swordsmen = game_character[1].MN;
	max_ms_swordsmen = game_character[1].mental_strength;

	max_health_wizard = game_character[0].health;
	max_mana_wizard = game_character[0].MN;
	max_ms_wizard = game_character[0].mental_strength;
	
	if (c == 1){//player wizard
		max_ms_player = max_ms_wizard;
	}else if (c == 2){//player swordsmen
		max_ms_player = max_ms_swordsmen;
	}
	
	return 0;
}

int upgrade_shop(int c, int upgrade_choice){
	int upgrade_value;
	
	if (coins >= 100 && upgrade_choice != 4){
		if (c == 1){//wizard
			if (upgrade_choice == 1){
				if (upgrade_health_max < 9){
					upgrade_value = max_health_wizard * 13 / 100;
					max_health_wizard += upgrade_value;
					upgrade_health_max++;
				}else if (upgrade_health_max >= 9){
					printf("%sYou've reached the max level in [Health]%s\n", Bright_Magenta, bright_reset);
				}
			}else if (upgrade_choice == 2){
				if (upgrade_mana_max < 9){
					upgrade_value = max_mana_wizard * 13 / 100;
					max_mana_wizard += upgrade_value;
					upgrade_mana_max++;
				}else if(upgrade_mana_max >= 9){
					printf("%sYou've reached the max level in [Mana]%s\n", Bright_Magenta, bright_reset);
				}
			}else if (upgrade_choice == 3){
				if (upgrade_ms_max < 9){
					upgrade_value = max_ms_wizard * 13 / 100;
					max_ms_wizard += upgrade_value;
				}else if(upgrade_ms_max >= 9){
					printf("%sYou've reached the max level in [ms]%s\n", Bright_Magenta, bright_reset);
				}
			}
		} else{//swordsmen
			if (upgrade_choice == 1){
				if (upgrade_health_max < 9){
					upgrade_value = max_health_swordsmen * 13 / 100;
					max_health_swordsmen += upgrade_value;
					upgrade_health_max++;
				}else if(upgrade_health_max >= 9){
					printf("%sYou've reached the max level in [Health]%s\n", Bright_Magenta, bright_reset);
				}
			}else if (upgrade_choice == 2){
				if (upgrade_mana_max < 9){
					upgrade_value = max_mana_swordsmen * 13 / 100;
					max_mana_swordsmen += upgrade_value;
					upgrade_mana_max++;
				}else if(upgrade_mana_max >= 9){
					printf("%sYou've reached the max level in [Mana]%s\n", Bright_Magenta, bright_reset);
				}
			}else if (upgrade_choice == 3){
				if (upgrade_ms_max < 9){
					upgrade_value = max_ms_swordsmen * 13 / 100;
					max_ms_swordsmen += upgrade_value;
					upgrade_ms_max++;
				}else if(upgrade_ms_max >= 9){
					printf("%sYou've reached the max level in [ms]%s\n", Bright_Magenta, bright_reset);
				}
			}
		}
		coins -= 100;
	}
	
	return 0;
}

int refill_shop(int c, int refill){
	int new_value;
	
	if (coins >= 50 && refill != 4){
		if (c == 1){// wizard
			if (refill == 1){
				new_value = max_health_wizard - game_character[c - 1].health;
				game_character[c - 1].health += new_value;
			} else if (refill == 2){
				new_value = max_mana_wizard - game_character[c - 1].MN;
				game_character[c - 1].MN += new_value;
			} else if (refill == 3){
				new_value = max_ms_wizard - game_character[c - 1].mental_strength;
				game_character[c - 1].mental_strength += new_value;
			}
		} else if (c == 2){// swordsmen
			if (refill == 1){
				new_value = max_health_swordsmen - game_character[c - 1].health;
				game_character[c - 1].health += new_value;
			} else if (refill == 2){
				new_value = max_mana_swordsmen - game_character[c - 1].MN;
				game_character[c - 1].MN += new_value;
			} else if (refill == 3){
				new_value = max_ms_swordsmen - game_character[c - 1].mental_strength;
				game_character[c - 1].mental_strength += new_value;
			}
		}
		coins -= 50;
	}
	
	return 0;
}

int chests_shop(int c){
int new_value;
int upgrade_value;
int surprise = rand() % 4;
	surprise += 1;
	
	if (c == 1){//wizard
		if (chest_choice == 1){//random upgrade
			if (coins >= 70){
				if (surprise == 1){
					if (upgrade_health_max < 9){
						upgrade_value = max_health_wizard * 13 / 100;
						max_health_wizard += upgrade_value;
						upgrade_health_max++;
					}else if(upgrade_health_max >= 9){
						printf("%sYou've reached the max level in [Health]%s\n", Bright_Magenta, bright_reset);
					}
				}else if (surprise == 2){
					if (upgrade_mana_max < 9){
						upgrade_value = max_mana_wizard * 13 / 100;
						max_mana_wizard += upgrade_value;
						upgrade_mana_max++;
					}else if(upgrade_mana_max >= 9){
						printf("%sYou've reached the max level in [Mana]%s\n", Bright_Magenta, bright_reset);
					}
				}else if (surprise == 3){
					if (upgrade_ms_max < 9){
						upgrade_value = max_ms_wizard * 13 / 100;
						max_ms_wizard += upgrade_value;
						upgrade_ms_max++;
					}else if(upgrade_ms_max >= 9){
						printf("%sYou've reached the max level in [ms]%s\n", Bright_Magenta, bright_reset);
					}
				}
				coins -= 70;
			}
		}else if (chest_choice == 2){//random refill
			if (coins >= 35){
				if (surprise == 1){
					new_value = max_health_wizard - game_character[c - 1].health;
					game_character[c - 1].health += new_value;
				}else if (surprise == 2){
					new_value = max_mana_wizard - game_character[c - 1].MN;
					game_character[c - 1].MN += new_value;
				}else if (surprise == 3){
					new_value = max_ms_wizard - game_character[c - 1].mental_strength;
					game_character[c - 1].mental_strength += new_value;
				}
				coins -= 35;
			}
		}else if (chest_choice == 3){//random coins
			if (coins >= 70){
				if (surprise == 1){
					coins += 20;
				}else if (surprise == 2){
					coins += 50;
				}else if (surprise == 3){
					coins += 100;
				}else{
					coins += 300;
				}
				coins -= 70;
			}
		}
	}else if (c == 2){//swordsmen
		if (chest_choice == 1){//random upgrade
			if (coins >= 70){
				if (surprise == 1){
					if (upgrade_health_max < 9){
						upgrade_value = max_health_swordsmen * 13 / 100;
						max_health_swordsmen += upgrade_value;
						upgrade_health_max++;
					}else if(upgrade_health_max >= 9){
						printf("%sYou've reached the max level in [Health]%s\n", Bright_Magenta, bright_reset);
					}
				}else if (surprise == 2){
					if (upgrade_mana_max < 9){
						upgrade_value = max_mana_swordsmen * 13 / 100;
						max_mana_swordsmen += upgrade_value;
						upgrade_mana_max++;
					}else if(upgrade_mana_max >= 9){
						printf("%sYou've reached the max level in [Mana]%s\n", Bright_Magenta, bright_reset);
					}
				}else if (surprise == 3){
					if (upgrade_ms_max < 9){
						upgrade_value = max_ms_swordsmen * 13 / 100;
						max_ms_swordsmen += upgrade_value;
						upgrade_ms_max++;
					}else if(upgrade_ms_max >= 9){
						printf("%sYou've reached the max level in [ms]%s\n", Bright_Magenta, bright_reset);
					}
				}
				coins -= 70;
			}
		}else if (chest_choice == 2){//random refill
			if (coins >= 35){
				if (surprise == 1){
					new_value = max_health_swordsmen - game_character[c - 1].health;
					game_character[c - 1].health += new_value;
				}else if (surprise == 2){
					new_value = max_mana_swordsmen - game_character[c - 1].MN;
					game_character[c - 1].MN += new_value;
				}else if (surprise == 3){
					new_value = max_ms_swordsmen - game_character[c - 1].mental_strength;
					game_character[c - 1].mental_strength += new_value;
				}
				coins -= 35;
			}
		}else if (chest_choice == 3){//random coins
			if (coins >= 70){
				if (surprise == 1){
					coins += 20;
				}else if (surprise == 2){
					coins += 50;
				}else if (surprise == 3){
					coins += 100;
				}else{
					coins += 300;
				}
				coins -= 70;
			}
		}
	}
	
	return 0;
}

int guide_information_game_book(){
	int guide;
	int exit = 0;
	
	do{
		printf("1.[guide_book]\n2.[i know what i'm doing]\n");
		scanf("%d", &guide);
	} while (guide < 1 || guide > 2);
	
	if (guide == 1){
		printf("%s--+++--------------------------------------------------------------------------------------------------+++--%s\n",
				STANDARD_GREEN, bright_reset);
		printf("%s{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{Guide Book}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}%s\n",
				STANDARD_GREEN, bright_reset);
		printf("%sCHARACTERS\n", STANDARD_GREEN);
		printf("	.[swordsmen]\n  		moves: %sattack, sword, SAMURAI_SLICE%s\n",
				BRIGHT_GREEN, bright_reset);
		printf("		%ssideaffects: %sNone%s\n", STANDARD_GREEN, BRIGHT_GREEN, bright_reset);
		printf("	%s.[wizard]\n 		moves: %sfireball, ice, lightning, LAZER%s\n",
				STANDARD_GREEN, BRIGHT_GREEN, bright_reset);
		printf("		%ssideaffects:%s\n", STANDARD_GREEN, bright_reset);
		printf("			%s(fireball): causes 30 damage the next round\n			(ice): decrease 15%% of the enemies attack\n", BRIGHT_GREEN);
		printf("			(lightning): 50%% of getting electricuted by your on light\n			(LAZER): 33%% of gettning 70 damage to your self only happens when you hit the enemy\n			         with 200 or 270 damage%s\n",
				bright_reset);
		printf("%sSHOP\n	.upgrades\n 		%sincrease 10%% of the current value%s\n",
				STANDARD_GREEN, BRIGHT_GREEN, bright_reset);
		printf("	%s.refills%s\n", STANDARD_GREEN, bright_reset);
		printf("		%sfull refill no matter the size%s\n",
				BRIGHT_GREEN, bright_reset);
		printf("	%s.chests\n		.[upgrades]%s\n", STANDARD_GREEN, bright_reset);
		printf("			%s30%% cheaper but it's random and there is 25%% of not getting anything%s\n",
				BRIGHT_GREEN, bright_reset);
		printf("		%s.[refills]\n			%s30%% cheaper but it's random and there is 25%% of not getting anything%s\n",
				STANDARD_GREEN, BRIGHT_GREEN, bright_reset);
		printf("		%s.[coins]\n			%sit costs 70 gold, and the prizes consest of these coins {20, 50, 100, 300}%s\n",
				STANDARD_GREEN, BRIGHT_GREEN, bright_reset);
					
		printf("%s--+++--------------------------------------------------------------------------------------------------+++--%s\n",
				STANDARD_GREEN, bright_reset);
					
		printf("\n\n");	
		do{
			printf("[1].exit\n");
			scanf("%d", &exit);
		} while (exit != 1);
	}
	return 0;
}

int coins_reward(){
	reward_index_coins = rand() % 3;
	
	return 0;
}

int ms_reward(){
	reward_index_ms = rand() % 4;
	
	return 0;
}

int story(){
	int story;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("%sYou just got smacked across the face, and because of that, you lost hundreds of thousands of aura.\nWhat a generational debt to go into.%s\n",
			Bright_Magenta, bright_reset);

	printf("%sNow, in retaliation for that, you gotta avenge your dignity.%s\n", Bright_Magenta, bright_reset);
	do{
		printf("[1].Next\n");
		scanf("%d", &story);
	}while (story != 1);
	return 0;
}

int killing_screen(){
	printf("%s", Bright_Yellow);
	printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⣸⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣧⡘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢃⣾⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣦⡙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⡿⢿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⠛⢿⣿⣿⣿⣿⡻⠛⠃⢉⣥⠤⠤⠀⠀⠀⣤⣤⡭⢭⣀⠉⠛⠻⣿⡿⠃⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠻⢟⠇⣋⣴⡲⠟⣋⣴⣦⣶⣶⣿⣿⣿⣾⣷⣶⣮⡛⠆⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠗⡀⠺⢙⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣷⠀⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⢪⣑⣦⡈⢎⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢡⢞⣿⣷⣬⢢⣈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢡⡔⣿⣿⣞⣷⣄⠑⢽⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⡿⠃⣠⣷⣿⣿⣿⣿⣿⣽⣦⣹⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠁⡜⣸⣿⣿⣿⣿⣝⠶⡌⠺⣿⣿⣿⣿⣿⣿⣿⣿⠜⢁⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⢸⢀⣿⣿⣿⣿⣿⣿⣷⣬⢦⡘⢾⣿⣿⣿⣿⣿⠏⡰⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⠻⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡄⢰⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣦⡘⠿⡿⠏⠁⣦⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⡏⣇⠈⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠙⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣷⡷⠀⠃⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢀⣌⠊⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⡹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢗⣼⣾⣿⣿⣥⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢸⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣷⢦⠈⣿⣿⣻⣿⣿⣿⣿⣿⣿⢿⢃⣾⣿⣿⣿⣿⣿⣿⡬⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⣾⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠘⠿⢷⡿⣿⣿⣿⣿⡻⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⢿⣿⣿⣿⣿⣿⣿⣿⠋⣼⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⢆⠀⠙⢿⡺⠿⠿⣫⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣝⣿⣿⣿⣿⠟⢡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣵⠄⠀⠙⢆⣤⢝⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣝⠻⠟⢣⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡷⢠⡀⠈⠑⠻⢿⣿⣿⣽⣟⣿⣿⣿⣿⣿⣿⣿⡿⠿⠋⢁⣔⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⣽⣿⣯⣟⡢⢤⣀⣀⡈⠙⡛⠛⠛⠛⠛⠙⠋⣁⣤⣶⣿⣿⣿⣷⡹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣷⣾⣯⣭⣍⣓⣲⣶⣲⣭⣽⣿⣿⣾⣿⣿⣿⣿⣿⣿⣮⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
    );
    printf("\n\nYou've killed the enemy\n");
    printf("%s", bright_reset);
    
    return 0;
}




