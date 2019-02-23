#include "stdio.h"
#include "stdlib.h"

#define MAX_USER_INPUT 30

typedef struct {
	int begin;
	int end;
}RANGE_T;

int getIntFromStdio(void)
{
	char *end;
	char buf[MAX_USER_INPUT];
	int ret;
	
	while (fgets(buf, sizeof buf, stdin)) {
		ret = strtol(buf, &end, 10);
		if (*end == '\n') {
			break;
		}
	}
	return ret;
}

RANGE_T calculateRangeIntersection(RANGE_T * first, RANGE_T * second)
{
	RANGE_T result = {.begin = 0, .end = 0};
	
	if ((first->end) >= (second-> begin)) {
		result.begin = second->begin;
		if ((second->end) >= (first->end)) {
			result.end = first->end;
		}
		else {
			result.end = second->end;
		}
	}
	
	return result;
}

int calculateRangeLength(RANGE_T * range)
{
	if (range->end > 0) {
		return range->end - range->begin;
	}
	return (-range->begin) + range->end;
}

void normalizeRange(RANGE_T * range)
{
	if (range->begin <= range->end) {
		return;
	}
	
	int temp = range->begin;
	range->begin = range->end;
	range->end = temp;
}

void main(void)
{
	printf("Input corners coordinates for first rectange\n");
	printf("Input first rectangle first corner x: ");
	int firstfirstx = getIntFromStdio();
	printf("Input first rectangle first corner y: ");
	int firstfirsty = getIntFromStdio();
	
	printf("Input first rectangle second corner x: ");
	int firstsecondx = getIntFromStdio();
	printf("Input first rectangle second corner y: ");
	int firstsecondy = getIntFromStdio();
	
	printf("\nInput corners coordinates for second rectange\n");
	printf("Input second rectangle first corner x: ");
	int secondfirstx = getIntFromStdio();
	printf("Input second rectangle first corner y: ");
	int secondfirsty = getIntFromStdio();
	
	printf("Input second rectangle second corner x: ");
	int secondsecondx = getIntFromStdio();
	printf("Input second rectangle second corner y: ");
	int secondsecondy = getIntFromStdio();

	RANGE_T firstxaxis = { .begin = firstfirstx, .end = firstsecondx };
	RANGE_T firstyaxis = { .begin = firstfirsty, .end = firstsecondy };

	RANGE_T secondxaxis = { .begin = secondfirstx, .end = secondsecondx };
	RANGE_T secondyaxis = { .begin = secondfirsty, .end = secondsecondy };
	
	normalizeRange(&firstxaxis);
	normalizeRange(&firstyaxis);
	normalizeRange(&secondxaxis);
	normalizeRange(&secondyaxis);
	
	RANGE_T intersectionx;
	RANGE_T intersectiony;
	
	if (firstxaxis.begin <= secondxaxis.begin) {
		intersectionx = calculateRangeIntersection(&firstxaxis, &secondxaxis);
	}
	else {
		intersectionx = calculateRangeIntersection(&secondxaxis, &firstxaxis);
	}
	
	if (firstyaxis.begin <= secondyaxis.begin) {
		intersectiony = calculateRangeIntersection(&firstyaxis, &secondyaxis);
	}
	else {
		intersectiony = calculateRangeIntersection(&secondyaxis, &firstyaxis);
	}
	
	int sizex = calculateRangeLength(&intersectionx);
	int sizey = calculateRangeLength(&intersectiony);
	
	printf("Calculated intersection area size: %i", sizex*sizey);
}
