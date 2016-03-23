#include "stats.h"

void initStats(stats *s, int tellerCount)
{
	s -> totalCustomers = 0;
	s -> maximumWait = 0;
	s -> lengthSum = 0;
	s -> maximumLength = 0;
	s -> tellerCount = tellerCount;
	s -> waitSum = 0;
}

void printStats(stats *s)
{
	printf("For %d tellers:\nCustomers Served: %d\nAverage Wait: %lf minutes\n"
		"Maximum Wait: %d minutes\nAverage Line Length: %lf\nMaximum Line Length: %d\n\n",
		s -> tellerCount,
		s -> totalCustomers,
		getAvgWait(s),
		s -> maximumWait,
		getAvgLength(s),
		s -> maximumLength);
}

double getAvgWait(stats *s)
{

	return (double)(s -> waitSum) / (double)(s -> totalCustomers); 

}

double getAvgLength(stats *s)
{

	return (double)(s -> lengthSum) / 480;	

}


void processMinute(stats *s, int lineLength)
{

	s -> lengthSum = s -> lengthSum + lineLength;
	if(s -> maximumLength < lineLength)
		s -> maximumLength = lineLength;

}

void processPerson(stats *s, int waitTime)
{

	(s -> totalCustomers)++;
	s -> waitSum = s -> waitSum + waitTime;
	if(s -> maximumWait < waitTime)
		s -> maximumWait = waitTime;

}



