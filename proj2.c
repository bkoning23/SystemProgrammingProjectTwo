//Brendan Koning
//Project: Event-Driven Simulation


#include <stdlib.h>
#include <math.h>
#define AVG_SERVICE 2.0
#include <stdio.h>
#define MIN_PER_DAY 480
#include "queue.h"
#include <time.h>
#include "stats.h"
#include <string.h>

double expdist(double mean){
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

void addToLine(int custCount, int idStart, int time, queue *q){
	for(int i = 0; i < custCount; i++){
		data d;
		d.id = idStart + i;
		d.arriveTime = time;
		enqueue(d, q);
	}
}




void simulation(int numOfTellers){

	int tellers[numOfTellers];
	int currentTime = 0;
	int currentId = 0;
	queue line;
	stats s;

	initialize(&line);
	initStats(&s, numOfTellers);	
	

	char buf[20];
	char * value, *value2;
	for(int i = 0; i < numOfTellers; i++)
		tellers[i] = 0;
	
	srand((unsigned int)time(NULL));
	
	char* settings[5][2];
	FILE* fp;
	fp = fopen("proj2.dat", "r");
	int counter = 0;
	while(fgets(buf, sizeof(buf), fp) != NULL){
		
		char * val1 = strtok(buf, "\t ");
		char * val2 = strtok(NULL, " ");
	
		settings[counter][0] = malloc(strlen(val1)+1);
		settings[counter][1] = malloc(strlen(val2)+1);
		strcpy(settings[counter][0], val1);
		strcpy(settings[counter][1], val2);		
		counter++;
	}

	
	
	while(currentTime < MIN_PER_DAY){
		//Determines how many customers will arrive at this minute
		int newCustRand = (rand() % 100) + 1;
		int newCust = 0;
		counter = 0;
		while(newCustRand > 0){
			int temp = newCustRand - atoi(settings[counter][1]);
			if(temp <= 0){
				newCust = atoi(settings[counter][0]);
			}
			newCustRand = temp;
			counter++;
		}
		
		addToLine(newCust, currentId, currentTime, &line);
		currentId = currentId + newCust;
		for(int i = 0; i < numOfTellers; i++){
			if(tellers[i] != 0)
				tellers[i] = tellers[i] - 1;
			else{
				if(!empty(&line)){
					data temp = dequeue(&line);
					int timeInLine = currentTime - temp.arriveTime;
					processPerson(&s, timeInLine);
					int timeToServe = (int)ceil(expdist(AVG_SERVICE));
					tellers[i] = timeToServe;
				}
			}
		}

		processMinute(&s, line.cnt); 

		currentTime++;
	}
	
	printStats(&s);



}

int main(){
	simulation(4);
	simulation(5);
	simulation(6);
	simulation(7);
	simulation(8);
}

