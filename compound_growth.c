/* this project is to check what is the final value of upgrades in (1projects.c) */
#include <stdio.h>
#include <math.h>

struct HealthData{
	float health;
	int iterations;
	float percentage;
};

struct HealthData recursive(struct HealthData data);

int main(void){
	struct HealthData initial_data;
	
	initial_data.health = 1150.0;
	initial_data.iterations = 9;
	initial_data.percentage = pow(3.0, 1.0/9.0) - 1.0;// pow same as 3^	
	
	struct HealthData final_data = recursive(initial_data);
	
	printf("the percentage for times 3 the upgrade in 9 iterations: (%.2f).\n and the percentage is used is (%.3f).\n", final_data.health, final_data.percentage);
	
	return 0;
}

struct HealthData recursive(struct HealthData data){
	if (data.iterations == 0){
		return data;
	}
	data.health = data.health + (data.health * data.percentage);
	data.iterations--;
	
	return recursive(data);
}
