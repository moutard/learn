#include <stdio.h>

void show_bytes(int * start, int len) {
     int i;
     for (i = 0; i < len; i++)
           printf(" %.2x", start[i]);
     printf("\n");
}

int main(){
	int i = 320;
	char * ptr = (char *) &i;
	show_bytes(&i, sizeof(int));
	printf("%d", *ptr);
	return 0;
}
