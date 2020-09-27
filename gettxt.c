#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include "objsects.h"


void bfd_text(char* file);

int main(int argc, char** argv){

  if(argc > 1){
    bfd_text(argv[1]);
  }else{
    char* errorMessage = "ERROR: Please specify an object file to get TEXT of.\n";
    write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
  }


}
