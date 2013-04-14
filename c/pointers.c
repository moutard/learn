#include <stdio.h>
#include <string.h>

// pointer are passed by copy to the function.
void change_int(int*); // good in fact.

void change_string_bad(char*);

// pass a pointer to a pointer.
void change_string_good(char**);

// works fine
void change_int(int *i){
	*i=10+*i;
};

// does not works!
void change_string_bad(char* c){
  // (char *c) is a string so you passed a string by copy !
  // so it won't be changed.
	c="newString";
};

void change_string_bad3(char c[]){
  // (char *c) is a string so you passed a string by copy !
  // so it won't be changed.
	c="newString";
};

void change_string_good(char** c){
  // as (char *) is a string you passed a pointer to a string it works.
	*c="newString";
};

/*
1)  ++i will increment the value of i, and then return the incremented value.

 i = 1;
 j = ++i;
 (i is 2, j is 2)
2) i++ will increment the value of i, but return the pre-incremented value.

 i = 1;
 j = i++;
 (i is 2, j is 1)
 */
char *my_strcpy(char *destination, char *source){
  char *p = destination;
  while (*source != '\0') {
    // it works because we use p++ so (*p) value is changed then incremented.
    *p++ = *source++;
  }
  *p = '\0';
  return destination;
};

int main(void){

	int i=6;
	// Two ways to initialize strings.
  char *string1 ="oldString1";
  char *string2 = "oldString2";

  char string3[] = "oldString3";
  char *string3Ptr = string3;

  // printf %s expect a pointer to a char
  printf("string1 before %s\n", string1);
  printf("string2 before %s\n", string2);
  printf("string3 before %s\n", string3);

  change_string_bad(string1);
	change_string_good(&string2);
	change_string_bad3(string3);
	change_string_good(&string3Ptr);

  printf("string1 after %s\n", string1);
  printf("string2 after %s\n", string2);
  printf("string3 after %s\n", string3);
  printf("string3Ptr after %s\n", string3Ptr);

  change_int(&i);
	printf("%i", i);

  int* arr1[8]; // An array of int pointers.
  int (*arr2)[8]; // A pointer to an array of integers
  return 0;
}

//http://www.cs.bu.edu/teaching/cpp/string/array-vs-ptr/
