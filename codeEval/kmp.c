#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_gap_array(char * request_string, int * gap_array){
  int request_length = strlen(request_string);
  gap_array[0] = -1;
  gap_array[1] = 0; 
  int i, current_length=0;
  for(i=1; i <request_length; i++){
    // si le motif terminal est egal au motif de début (avec le décalage)
    if(request_string[i] == request_string[current_length]){
      current_length+=1;
    } else {
      current_length = 0;
    }
    gap_array[i+1] = current_length;
  }
};

int main(char * argc[], int argv){
  char * request_string = "ABABAB";
  int request_length = strlen(request_string);
  int gap_array[request_length + 1];
  
  compute_gap_array(request_string, gap_array);
  int i;
  for(i=0; i <= request_length; i++ ){
    printf("%d ",gap_array[i]); 
  }
}