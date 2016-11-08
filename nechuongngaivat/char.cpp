#include <stdio.h>
#include "console.h"

void main1()
{
	for (int i = 0; i < 256; i++) {
		TextColor(i);
		printf("%d     %c", i, i);
		putchar('\n');
	}

}