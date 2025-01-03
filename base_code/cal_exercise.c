//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


#define HEALTHFILEPATH "health_data.txt"

// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file,"%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute ) != -1) {
    	exercise_list_size++;
    	// saving data from "exercises.txt"
    	
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");
    for(i=0;i<exercise_list_size;i++)
    {
    	printf("%d. %s - (%dkcal burned per min.)\n",i+1,exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}
	printf("7. Exit\n");
	
    // ToCode: to enter the exercise to be chosen with exit option
	printf("Choose exercise (1-7): \n");
 	do{
		scanf("%d",&choice);
 		if(choice>7||choice<1)
 		{
 			printf("[Error] Invalid option.\n");
 			printf("Please choose number between 1 to 7.\n");
 			//asking to select valid number
		}
		else if(choice==7)
		{
			return;//exit option
		}
		else break;//when valid number is selected
	}while(1);
	
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    health_data->exercises[health_data->exercise_count]=exercise_list[--choice];
    health_data->exercises[health_data->exercise_count].calories_burned_per_minute*=duration;
    health_data->exercise_count++;
    health_data->total_calories_burned+=exercise_list[choice].calories_burned_per_minute*duration;
   
}
