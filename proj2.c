#include <stdlib.h>
#include <math.h>
#define AVG_SERVICE 2.0
#include <stdio.h>
#define MIN_PER_DAY 480
#include "queue.h"

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
	printf("Added %d customers to the line\n", custCount);
}




void simulation(int numOfTellers){

	int tellers[numOfTellers];
	int time = 0;
	int count = 0;
	queue line;

	initialize(&line);
		
	for(int i = 0; i < numOfTellers; i++)
		tellers[i] = 0;
	
	while(time < MIN_PER_DAY){
		int newCust = (rand() % 100) + 1;
		
		if(newCust < 16)
			addToLine(0, count, time, &line);
		else if(newCust < 35)
			addToLine(1, count, time, &line);
		else if(newCust < 60)
			addToLine(2, count, time, &line);
		else if(newCust < 70)
			addToLine(3, count, time, &line);
		else
			addToLine(4, count, time, &line);	

		if(!empty(&line)){
			data temp = dequeue(&line);

			printf("Next in Line: ID: %d, Arrival %d\n", temp.id, temp.arriveTime); 		
		}

		time++;
	}
	




}

int main(){
	double t;
	t = expdist(AVG_SERVICE);
	simulation(4);
}


