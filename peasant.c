#include <stdio.h>
#include <string.h>
#include <unistd.h>

//global variable for spacing issue
int wizard_damage[4];
int wizard_MN[4];

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
} character;

character game_character[2];

int choose_character();
int wizard();
int swords_men();
int fight_enemy();
int hero_info();
int wizard_picture();
int swords_men_picture();
int start_picture();
int fight();

int main(void){
	// c=choice
	int c;
	c = choose_character();
	if (c == 1){
		wizard();
		hero_info(c);
		sleep(12);
		fight_enemy(c);
	} else if (c == 2){
		swords_men();
		hero_info(c);
		sleep(12);
		fight_enemy(c);
	} else{
		printf("Invalid character choice!\n");
	}
	
	
	fight(c);
}

int choose_character(){
	int choice;
	
	start_picture();
	
	printf("hello hero which hero would you like to be:\nNOTE: use numbers to choose\n");
	printf("1.Wizard\n2.Swords_men\n");
	scanf("%d", &choice);
	
	return choice;
}

int wizard(){
	/*[150_HL, 100_MN, regeneration_MN 15_MN_per_round]
	 * attack 	 5_DM  0_MN
	 * fireball  10_DM 20_MN time_2rounds 
	 * ice 		 3_DM  25_MN time_3rounds
	 * lightning 35_DM 40_MN time_1rounds */
	 // special move LAZER 100_DM 60_MN
	 strcpy(game_character[0].name, "Wizard");
	 game_character[0].health = 150;
	 game_character[0].MN = 100;
	 game_character[0].regeneration_MN_per_round = 15;
	 
	 strcpy(game_character[0].known_spells[0].name, "Fireball");
	 wizard_damage[0] = game_character[0].known_spells[0].damage = 10;
	 wizard_MN[0] = game_character[0].known_spells[0].MN = 20;
	 game_character[0].known_spells[0].per_round = 2;
	 strcpy(game_character[0].known_spells[1].name, "Ice");
	 wizard_damage[1] = game_character[0].known_spells[1].damage = 3;
	 wizard_MN[1] = game_character[0].known_spells[1].MN = 25;
	 game_character[0].known_spells[1].per_round = 3;
	 strcpy(game_character[0].known_spells[2].name, "Lightning");
	 wizard_damage[2] = game_character[0].known_spells[2].damage = 35;
	 wizard_MN[2] = game_character[0].known_spells[2].MN = 40;
	 game_character[0].known_spells[2].per_round = 1;//1 means only during this round which is instant
	 
	 strcpy(game_character[0].known_spells[3].name, "LAZER");
	 wizard_damage[3] = game_character[0].known_spells[3].damage = 100;
	 wizard_MN[3] = game_character[0].known_spells[3].MN = 60;
	 game_character[0].known_spells[3].per_round = 1;//1 means only during this round which is instant
	 
	 game_character[0].num_known_spells = 4;



	return 0;
}
 
 int swords_men(){
	 /*[250_HL, 50_MN, regeneration_MN 4_MN_per_round]
	  * attack   15_DM 0_MN
	  * sword   20_DM 10_MN */
	  // special move samurai_slice 150_DM 35_MN (((((((+ increase damage 15% every_round))))))
	 strcpy(game_character[1].name, "Swords_men");
	 game_character[1].health = 250;
	 game_character[1].MN = 50;
	 game_character[1].regeneration_MN_per_round = 4;
	 
	 strcpy(game_character[1].known_spells[0].name, "Attack");
	 swords_men_damage[0] = game_character[1].known_spells[0].damage = 15;
	 swords_men_MN[0] = game_character[1].known_spells[0].MN = 0;
	 game_character[1].known_spells[0].per_round = 1;
	 strcpy(game_character[1].known_spells[1].name, "Sword");
	 swords_men_damage[1] = game_character[1].known_spells[1].damage = 20;
	 swords_men_MN[1] = game_character[1].known_spells[1].MN = 10;
	 game_character[1].known_spells[1].per_round = 1;
	 
	 strcpy(game_character[1].known_spells[2].name, "SAMURAI_SLICE");
	 swords_men_damage[2] = game_character[1].known_spells[2].damage = 150;
	 swords_men_MN[2] = game_character[1].known_spells[2].MN = 35;
	 game_character[1].known_spells[2].per_round = 1;//1 means only during this round which is instant
	 
	 game_character[0].num_known_spells = 3;
	 
	 

	 return 0;
}

int fight_enemy(int c){
	int enemy;
	int n_moves_enemy;
	
	if (c == 1){
		enemy = 1;
		swords_men();
		swords_men_picture();
		n_moves_enemy = 3;
	} else if (c == 2){
		enemy = 0;
		wizard();
		wizard_picture();
		n_moves_enemy = 4;
	}
	
	printf("Enemy: %s\n",game_character[enemy].name);
	
	printf("Moves:");
	for (int i = 0; i < n_moves_enemy; i++){
		printf("     %d.%s", i + 1, game_character[enemy].known_spells[i].name);
}
	printf("\n");
			
	return 0;
}

int hero_info(int c){
	int n_moves_hero;
		
	if (c == 1){
		n_moves_hero = 4;
		wizard_picture();
	} else if (c == 2){
		n_moves_hero = 3;
		swords_men_picture();
	}
	
	c--;
	printf("\nHero: %s\n",game_character[c].name);
	
	printf("Moves:");
	for (int i = 0; i < n_moves_hero; i++){
		printf("     %d.%s", i + 1, game_character[c].known_spells[i].name);
	}
	printf("\n\n");
	
	return 0;
}

int wizard_picture(){
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣶⠟⠛⠉⠉⠉⠛⠻⢿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⣍⠻⢿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⣄⠛⢿⣶⣄⣠⡾⣧⡀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣷⣦⡉⠻⣫⣾⡽⣷⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⣀⣀⡀⠀⠀⠀⠀⣀⣀⡀⠀⠸⣿⠻⣿⣾⡿⠃⠹⣿⣷⡀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠟⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⣿⣇⠀⠉⠀⠀⠀⠈⠛⠛⠒⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠃⢀⣀⣠⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣀⡀⠘⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⡿⠿⠟⠋⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠙⠛⠿⢿⣶⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢀⣠⣴⣾⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⣷⣦⣄⡀⠀⠀⠀⠀\n");
    printf("⠀⣀⣴⣾⣿⣛⣁⣤⣤⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣠⣤⣌⣛⣿⣷⣦⣀⠀\n");
    printf("⣼⡿⣿⣿⣿⣿⣿⣿⠋⠉⢹⡿⠻⣿⣿⡶⠒⠒⠲⣶⣶⣶⣶⣶⣶⡶⠖⠒⠲⢾⣿⣿⠟⢿⡏⠉⠙⣿⣿⣿⣿⣿⣿⢿⣷\n");
    printf("⢹⣷⡙⢿⣿⣿⠾⠍⠁⠀⣾⠇⠀⢻⠀⢈⣻⣷⣶⣤⣤⡽⠟⢯⣤⣤⣴⣾⣿⡁⠀⡟⠀⠘⣷⠀⠈⠩⠷⣿⣿⡿⢋⣾⡟\n");
    printf("⠀⠙⢿⣶⣭⣛⡿⠷⠤⣼⠏⢠⢶⣾⠀⠀⠙⠓⢦⣼⣿⡇⠀⢸⣿⣧⣴⠟⠋⠀⠀⣿⡄⡄⠹⣧⠤⠾⠿⣛⣭⣴⡿⠋⠀\n");
    printf("⠀⠀⠀⠈⠛⠻⠿⣷⣶⠟⢰⡏⢸⣇⠀⠀⠀⠈⠉⢉⣹⠇⠀⠘⣏⡉⠉⠁⠀⠀⠀⢸⡇⢹⡆⠻⣶⣾⠿⠟⠛⠉⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⢠⡏⢠⡟⠀⣼⣿⣄⠀⠀⠀⡼⠋⠻⠀⠀⠀⠾⠉⢳⡀⠀⠀⣠⣿⣷⠀⢹⡄⢹⣆⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⣟⣠⡿⢀⣼⡇⢹⣝⡷⣤⣼⣳⠴⠛⠳⠤⠔⠛⠦⣞⣷⣤⢴⣫⡟⠸⣷⡀⢿⣄⣻⡀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠸⢋⣿⠁⣼⢹⣆⠀⠉⠛⠛⠉⠁⠀⠀⣀⣿⣄⠀⠀⠀⠉⠛⠛⠉⠀⢠⡏⢧⠀⢿⡝⠇⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⣼⡇⣰⠃⠈⢿⣦⣄⣀⣀⣀⣤⡴⠞⠋⠉⠉⠳⢦⣤⣀⣀⣀⣠⣴⡿⠁⠘⣦⢸⣷⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⢿⣿⡏⢠⠄⢸⣧⠉⠉⢻⣀⣠⡶⠞⠛⠉⠛⠳⢶⣤⣀⡟⠉⠉⢸⡇⠀⡄⢹⡿⠟⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢸⣡⡏⠀⡄⢿⡀⠀⠀⠛⠉⠀⠀⠀⠀⠀⠀⠀⠉⠛⠁⠀⢀⡿⢡⡀⢹⣬⡇⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠸⡿⣇⢸⣿⢸⣷⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⣾⡇⣼⣧⣸⢻⡇⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⠹⣿⡏⡿⣧⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣾⣿⠻⣿⠏⢿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠁⠀⠻⣿⣦⣾⠀⠀⠀⠀⠀⣶⣤⡟⠟⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⢻⣧⡀⠀⠀⣼⡿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣦⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    
    return 0;
}

int swords_men_picture(){
	printf("⠀⠀⣀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⣠⣤⡀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⢸⣧⠞⠁⡷⢿⣦⡀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣆⠀⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣼⢪⡇⠀⠀⣷⣶⢹⡇⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠛⠛⠉⠉⠉⢩⠉⠙⠛⣿⠛\n");
    printf("⣿⣿⣿⣿⣿⣿⣷⡄⠘⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⢹⠘⣷⣄⢳⣿⣿⣾⣗⡿⠀⠀⠀⠀⢀⣟⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⡍⠉⠀⠘⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠿⡄⠀⠀⠀⢸⠆⣿⣿⡏⣿⣿⣿⡗⣧⠀⠀⠀⠀⢸⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣄⢧⡀⣀⡴⠋⢀⣿⣿⣷⣿⣿⣿⡇⢩⡳⢤⣀⢠⣿⣟⣿⣿⠀⢀⣠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⢫⠿⠟⢳⡇⠀⣼⣿⣿⣿⣿⣿⣿⣷⡀⢸⣷⡿⠟⠛⠛⢿⣿⣦⠓⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠑⠉⠀⠀⣾⡴⣾⡿⢹⠙⢿⡭⠭⠽⢿⣿⣿⡿⣅⣀⣀⣀⣰⣿⡟⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀⢹⠋⠙⠛⢻⡿⣡⣿⠃⣸⡇⠈⠓⢤⣀⠈⠁⣿⡤⢤⣤⣬⠟⢻⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⡼⢀⣠⣴⣿⡟⠛⠁⠀⡏⠀⠀⠀⠂⢹⣷⣤⣾⣧⣶⣾⡍⢛⣿⣿⣿⢿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⣼⡵⠋⢹⣿⣿⣧⠀⠀⠀⡷⠀⠸⡷⣤⣴⡿⣿⣿⣿⣿⣵⣿⣶⣿⣿⡛⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠂⠀⠀⠀⠀⠀\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠃⠀⠀⠀⠀⠀⠀⡼⠛⢻⣿⡀⠀⠀⣇⣀⡆⣀⣼⣟⡂⣹⣿⣿⠻⣧⠀⠈⠉⣻⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠊⠀⢀⡌⠀⠀⠀⠀\n");
    printf("⡟⠛⠛⠛⠛⠛⠛⠛⠛⠛⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⢀⣼⣧⣤⣼⣿⡇⠀⠀⣿⢿⣼⠟⠋⠹⣿⣿⣿⡏⠀⠹⣦⣤⣾⡿⣻⣟⣛⣦⡄⠀⠀⠀⠀⢠⠞⠁⠀⢠⠞⠀⠀⠀⠀⠀\n");
    printf("⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⢹⣿⣿⣿⣿⡟⠳⡄⣿⣾⣿⠾⠿⠿⣿⡿⢿⠁⠀⠀⠹⣿⡿⠾⣿⣿⡅⢸⠃⠀⠀⢀⡴⠋⠀⠀⡴⠋⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠃⠀⠙⣿⣿⣿⡇⢄⠈⢿⡿⢁⣴⡾⢿⢿⣿⣿⣇⠀⠀⠘⣿⡁⠠⣿⣿⠳⡾⠀⢀⡴⠋⠀⠀⣠⠎⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀⢀⣼⠟⣿⣟⡀⠈⠑⣿⣿⣿⣭⣷⢾⣿⣿⣿⠿⣦⠀⠀⠹⣷⠈⢹⣿⣦⣵⡴⠋⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠡⠀⣴⢿⡾⠛⠀⣹⣆⠀⣸⣿⣿⣭⣾⡟⠻⣥⣐⣦⠈⡇⠀⠀⢹⡄⢸⣿⡇⡏⠀⠀⢀⠜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣧⢟⣿⣿⠟⢠⢃⡼⣿⡟⢷⣸⣿⣿⣿⣿⣿⣦⡈⠻⠛⠉⢳⠀⢐⣿⣧⠈⣿⡋⠁⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⢛⣾⣿⠋⢀⡼⠋⠀⣿⡇⠈⢻⢟⡟⣿⣿⣿⠙⣿⣦⣶⡖⠒⣷⣾⣿⡟⢳⣿⡗⢶⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⣼⣿⣧⣤⡾⠁⠀⣀⣿⡇⠇⢀⡾⡇⣿⣧⣿⠀⠸⣿⣿⣿⠲⣼⠻⢿⣇⣺⣿⣧⣼⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⠃⢠⡾⠁⢹⡇⠀⠚⠁⣷⣿⠷⠘⢷⡄⠀⠀⢹⡆⢸⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⣀⣤⣿⣿⣿⡿⢸⣿⠁⠀⢸⣷⠀⠀⢸⢹⣿⣗⠂⠀⠹⣆⠀⠈⣿⢸⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢬⣹⣿⢿⣿⣿⡿⠋⠀⣾⡇⣠⣴⣿⣿⢦⡀⣼⣸⣿⣿⣦⡀⠀⢹⡆⠂⣿⣿⣿⣿⣿⣿⠛⢦⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⠟⣻⢿⣿⣯⣀⡀⣼⣿⠋⠁⣈⣿⣿⣷⣻⣿⣿⣿⣿⣿⣁⣀⢸⣿⣶⣿⣿⣿⣿⣿⣿⣷⡈⢧⡘⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣯⠞⠁⣠⠿⠛⠻⢱⣿⡇⠠⠾⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠻⣿⡻⣿⣿⣿⣆⠙⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢞⣿⠏⠀⣰⠋⠀⠀⠀⢀⣿⡟⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣬⣭⣿⣿⣿⣦⣝⢷⣄⠙⢿⣿⣷⣌⠃⢀⠀⠀⠀⠏⠉⠛⠳⠄⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⣀⡴⢫⠞⠁⢀⡾⠁⠀⠀⠀⠀⣼⣿⣠⡶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡟⢿⣿⣿⣯⡳⣝⠷⣿⣿⣟⠿⠻⢦⣄⡀⢠⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⣰⠋⡴⠃⢀⡴⠋⠀⠀⠀⠀⣠⢰⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣥⢸⣿⣿⣿⣿⣾⣿⣿⠿⡟⠶⣤⣄⡙⠙⢦⣝⠷⣄⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⡴⠃⠈⢀⣴⠋⠀⠀⠀⠀⠀⢠⢧⣿⣿⣿⢣⡿⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣤⣍⠙⠳⢶⣌⠁⠈⢳⡄⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⣸⠁⣀⡴⠛⠁⠀⠀⠀⠀⠀⢠⢏⣿⣿⣿⠹⡟⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣙⠓⠈⠀⠁⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠻⠚⠁⠀⠀⠀⠀⠀⠀⠀⢠⣟⣾⣿⣿⣿⠀⡴⠋⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣃⡃⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡠⢤⠴⠒⢋⣾⣿⣿⣿⠇⡀⠂⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣙⡇⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⠠⣄\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠉⣶⣎⣁⣀⣀⣼⣿⣿⣿⣿⡮⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡌⢻⡇⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    
    return 0;
}

int start_picture(){
	printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣫⣶⣾⣿⣿⣶⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⣿⣷⣶⣾⣽⡻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠉⠀⠀⠈⠙⣷⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣱⠟⠉⠀⠀⠀⠉⠿⣟⢿⡿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⡏⣼⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⠇⠁⠀⠀⠀⠀⠀⠀⠀⠹⣟⣷⢹⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⡇⣿⢸⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⢸⣿⢻⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⢠⢿⡏⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣹⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣾⣿⣾⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣯⣷⣻⣿⣦⣀⠀⠀⠀⠀⣠⣴⢯⣾⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡽⣧⡠⣤⡀⠀⠀⠀⠀⣠⣾⠟⢩⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣿⢟⣹⡿⣳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣌⠻⣮⣙⣿⣶⣶⣟⣋⣵⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣯⣛⡷⠬⢭⣉⣩⣴⣿⣫⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣝⣛⣻⣿⣟⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⡟⠉⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣷⡞⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣦⣈⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣇⣠⡿⠉⠙⣿⡿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠉⢻⡇⠈⢿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⡇⢠⡾⠋⢠⡏⠀⠀⣹⣿⢟⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠹⣿⣧⠙⢿⣧⠀⢸⣷⣤⣼⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⢸⡀⢀⣴⠟⠁⢸⡏⠀⠀⣸⣿⣿⣿⠉⠀⠀⢻⣿⣿⣿⠁⠀⠈⣿⣿⣿⣟⠁⠀⢸⣿⠃⠹⣧⠀⠀⣹⣿⠀⠀⢻⣦⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣷⣿⣟⠀⠀⢸⡇⠀⢰⡿⠁⢸⣿⠀⠀⠀⣾⡏⠻⣿⡀⠀⠀⣿⡇⠹⣿⡀⠀⢸⣿⠀⠀⠸⣦⢠⣿⡿⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⣸⣷⡀⣿⠇⠀⠈⢿⣇⠀⣸⡿⠀⠀⢻⣧⠀⣾⡿⠀⠀⢹⣧⠀⣼⣿⡄⠀⢀⣿⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⢀⣾⣿⣶⣿⣧⠀⠀⢠⣿⣷⣿⠁⠀⠀⣸⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣴⣿⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
    
    return 0;
}

int fight(int c){
	int enemy;
	int n_enemy_moves;
	int n_hero_moves;
	int d;
	
	if (c == 1){
		enemy = 1;
		n_enemy_moves = 3;
		n_hero_moves = 4;
	} else if (c == 2){
		enemy = 0;
		n_enemy_moves = 4;
		n_hero_moves = 3;
	}
	d = c - 1;
	printf("You're going to fight the enemy: %s\n\n", game_character[enemy].name);
	
	
	// ENEMY + needs to be in a loop [[or do it in the main function brah]] to keep the fight running
	for (int j = 0; j < 2; j++){
		if (j == 0){
			printf("> CRITICAL!\n");
			printf("Health:%d		MN:%d		regeneration_MN_per_round:%d\n",
					game_character[enemy].health,
					game_character[enemy].MN,
					game_character[enemy].regeneration_MN_per_round);
					
			printf("+---------------------------------------------------------------------------+\n");
					
			printf("[Spells]\n");
			printf("Debug: n_enemy_moves = %d\n", n_enemy_moves);
			printf("Debug: enemy = %d\n", enemy);
			for (int i = 0; i < n_enemy_moves; i++){
				if (enemy == 1){//swords_men
					printf("Debug: final_spaces_printed_damage_hero[%d] = %d\n", i, final_spaces_printed_damage_hero[i]);
					printf("Debug: final_spaces_printed_MN_hero[%d] = %d\n", i, final_spaces_printed_MN_hero[i]);
					
					
					
					printf("    [%d]        <Damage=%d,%*sMana_Cost=%d%*s,Per_Round=%d>\n",
							i + 1,
							game_character[enemy].known_spells[i].damage,
							final_spaces_printed_damage_hero[i], "",
							game_character[enemy].known_spells[i].MN,
							final_spaces_printed_MN_hero[i], "",
							game_character[enemy].known_spells[i].per_round);
				} else if (enemy == 0){//wizard
					printf("    [%d]        <Damage=%d,%*sMana_Cost=%d,%*sPer_Round=%d>\n",
							i + 1,
							game_character[enemy].known_spells[i].damage,
							final_spaces_printed_damage_wizard[i], "",
							game_character[enemy].known_spells[i].MN,
							final_spaces_printed_MN_wizard[i], "",
							game_character[enemy].known_spells[i].per_round);
				}
			}
		} else if (j == 1){
			printf("\n\n\n> CRITICAL!\n");
			printf("Health:%d		MN:%d		regeneration_MN_per_round:%d\n",
					game_character[d].health,
					game_character[d].MN,
					game_character[d].regeneration_MN_per_round);
					
			printf("+---------------------------------------------------------------------------+\n");
					
			printf("[Spells]\n");
			printf("Debug: n_hero_moves = %d\n", n_hero_moves);
			for (int i = 0; i < n_hero_moves; i++){
				printf("    [%d]        <Damage=%d,%*sMana_Cost=%d,%*sPer_Round=%d>\n",
						i + 1,
						game_character[d].known_spells[i].damage,
						final_spaces_printed_damage_hero[i], "",
						game_character[d].known_spells[i].MN,
						final_spaces_printed_MN_hero[i], "",
						game_character[d].known_spells[i].per_round);
			}
		}
	}
	return 0;
}

int spacing(){
	int wizard = 4;
	int hero = 3;
	int damage = 12;
	int MN = 14;
	
	//fixing the spacing issue when showing the info for a spell	
	for (int x = 0; x < wizard; x++){
		int count_digits_damage = 0;
		while (wizard_damage[x] > 0){
			wizard_damage[x] /= 10;
			count_digits_damage++;
		}
		
		int count_digits_MN = 0;
		while (wizard_MN[x] > 0){
			wizard_MN[x] /= 10;
			count_digits_MN++;
		}
		final_spaces_printed_damage_wizard[x] = damage - (7 + count_digits_damage);
		final_spaces_printed_MN_wizard[x] = MN - (7 + count_digits_MN);
		if (wizard < hero){
			final_spaces_printed_damage_hero[x] = damage - (7 + count_digits_damage);
			final_spaces_printed_MN_hero[x] = MN - (7 + count_digits_MN);
		}
	}


	return 0;
}



