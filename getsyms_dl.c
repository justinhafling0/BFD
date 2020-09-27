#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdint.h>
//#include "objsects.h"

int getIntSizeB(int string, int base);
char* intToStringB(int input, int base, int size, char* string);

long bfd_dl(char* bfdFile, int option);

#define RDTSC(var)                                              \
  {                                                             \
    uint32_t var##_lo, var##_hi;                                \
    asm volatile("lfence\n\trdtsc" : "=a"(var##_lo), "=d"(var##_hi));     \
    var = var##_hi;                                             \
    var <<= 32;                                                 \
    var |= var##_lo;                                            \
  }

int main(int argc, char** argv){
  int option = 0;

  double clockSpeed = (2600);
  long trials[50];
  char* bfdFile;

  if(argc > 1){
    bfdFile = argv[1];
    if(argc > 2){
      if(strcmp(argv[2], "RTLD_LAZY") == 0){
        option = 0;
      }else if(strcmp(argv[2], "RTLD_NOW") == 0){
        option = 1;
      }else{
        char* errorMessage = "ERROR: Please specify RTLD_NOW or RTLD_LAZY.\n";
        write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
        return 0;
      }
    }else{
      char* errorMessage = "ERROR: Please specify RTLD_NOW or RTLD_LAZY.\n";
      write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
      return 0;
    }
  }else{
    char* errorMessage = "ERROR: Please specify an object file to get objdump of.\n";
    write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
    return 0;
  }
  int i;
  for(i = 0; i < 50; i++){
    trials[i] = bfd_dl(bfdFile, option);
  }

  int fd;
  if(option){
    fd = open("Stats_Syms_Now.txt", O_WRONLY | O_CREAT, 0644);
  }else{
    fd = open("Stats_Syms_Lazy.txt", O_WRONLY | O_CREAT, 0644);
  }


  long sum = 0;
  for(i = 0; i < 50; i++){

    char* printString = malloc(sizeof(char) * 100);

    strcpy(printString, "Trial ");

    int trialSize = getIntSizeB(i+1, 10);
    //printf("Size: %d\n", trialSize);
    char* trialString = malloc(sizeof(char) * (trialSize + 1));
    memset(trialString, 0, trialSize);
    intToStringB(i+1, 10, trialSize, trialString);

    strcat(printString, trialString);
    strcat(printString, ": ");


    int result =  trials[i] / clockSpeed;
    int indexSize = getIntSizeB(result, 10);

    char* resultString = malloc(sizeof(char) * (indexSize + 1));
    intToStringB(result, 10, indexSize, resultString);


    strcat(printString, resultString);
    strcat(printString, "\n");

    //printf("%s", printString);

    sum+= trials[i];
    write(fd, printString, strlen(printString));

    free(printString);
    free(resultString);
    free(trialString);

  }

  char* aveString = malloc(sizeof(char) * 100);

  strcpy(aveString, "\nAverage: ");

  sum /= 50;
  sum /= 2600;
  int sumSize = getIntSizeB(sum, 10);
  char* sumString = malloc(sizeof(char) * (sumSize + 1));
  intToStringB(sum, 10, sumSize, sumString);

  strcat(aveString, sumString);
  strcat(aveString, "\n");
  write(fd, aveString, strlen(aveString));

  free(aveString);
  free(sumString);

  close(fd);
  //bfd_dl(bfdFile);

}

long bfd_dl(char* bfdFile, int option){
  unsigned long long start, finish;
  RDTSC(start);
  if(option){
    dlopen("./libobjdata.so", RTLD_NOW);
  }else{
    dlopen("./libobjdata.so", RTLD_LAZY);
  }
  bfd_nm(bfdFile);
  RDTSC(finish);
  return (finish - start);
}

int getIntSizeB(int string, int base){
  int count = 1;
  while(string >= base){
      string /= base;
      count++;
  }
  return count;
}

char* intToStringB(int input, int base, int size, char* string){

  //printf("Size: %d\n", size);
  int i = size - 1;
  string[size] = '\0';
  for(i; i >=0; i--){
    if(base > 10){
      if(input % base >= 10){
        string[i] = (input % base) % 10 + 'A';
      }else{
        string[i] = (input % base) + '0';
      }
    }else{
      string[i] = (char) (input % base + '0');
    }
    input /= base;
  }
  //return string;
}
