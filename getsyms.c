#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include "objsyms.h"


void bfd_nm(char* file);

int main(int argc, char** argv){

  if(argc > 1){
    bfd_nm(argv[1]);
  }else{
    char* errorMessage = "ERROR: Please specify an object file to get nm of.\n";
    write(STDOUT_FILENO, errorMessage, strlen(errorMessage));
  }


}
