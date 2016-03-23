#include <stdlib.h>
#include <math.h>
#define AVG_SERVICE 2.0
#include <stdio.h>
#define MIN_PER_DAY 480
#include "queue.h"
#include <time.h>
#include "stats.h"

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
	
	for(int i = 0; i < numOfTellers; i++)
		tellers[i] = 0;
	
	srand((unsigned int)time(NULL));
	
	while(currentTime < MIN_PER_DAY){
		//Determines how many customers will arrive at this minute
		int newCustRand = (rand() % 100) + 1;
		int newCust = 0;
		
		if(newCustRand < 16)
			newCust = 0;	
		else if(newCustRand < 35)
			newCust = 1;
		else if(newCustRand < 60)
			newCustRand = 2;	
		else if(newCustRand < 70)
			newCust = 3;
		else
			newCust = 4;
	
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

