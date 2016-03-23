#include <stdio.h>

struct stats{
	int	totalCustomers;
	int	maximumWait;
	int	lengthSum;
	int	maximumLength;
	int	tellerCount;
	int	waitSum;
};

typedef	struct stats 	stats;
void	initStats(stats *s, int tellerCount);
void	printStats(stats *s);
double	getAvgWait(stats *s);
double	getAvgLength(stats *s);
void	processMinute(stats *s, int lineLength);
void	processPerson(stats *s, int waitTime);
