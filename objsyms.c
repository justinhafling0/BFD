#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <bfd.h>

#define inputSize 512
#define BFD_INIT_MAGIC (sizeof (struct bfd_section))

#define MAX_CHAR 100




int getIntSize(int input, int base);
char* intToString(int input, int base, int size, char* index);


void bfd_print_symbols(asection *bfd_section);

int bfd_nm(char* file){


  bfd_init();


  bfd* my_bfd = bfd_openr(file, NULL);
  if(!my_bfd){
    printf("Open my_bfd failed!\n");
    return 1;
  }




  if (!bfd_check_format (my_bfd, bfd_object))
  {
    bfd_close (my_bfd);
    return 0;
  }





  long storage_needed;
  asymbol **symbol_table;
  long number_of_symbols;
  long i;

  storage_needed = bfd_get_symtab_upper_bound (my_bfd);
  if (storage_needed < 0)
    return -1;

  if (storage_needed == 0)
    return -1;

  symbol_table =  xmalloc (storage_needed);
  number_of_symbols = bfd_canonicalize_symtab (my_bfd, symbol_table);

  if (number_of_symbols < 0)
    return -1;


  int vma_buffer = 16;

  for (i = 0; i < number_of_symbols; i++){
    char* printString = (char*) malloc(MAX_CHAR);

    int vma = symbol_table[i]->section->vma;
    int offset = symbol_table[i]->value;

    char* name = (char*) symbol_table[i]->name;

    int vmaMod = vma + offset;
    int vmaSize = getIntSize(vmaMod, 16);

    char* vmaString = malloc(sizeof(char) * vmaSize);
    intToString(vmaMod, 16, vmaSize, vmaString);

    int j;
    for(j = vmaSize; j < vma_buffer; j++){
      strcat(printString, "0");
    }

    strcat(printString, vmaString);

    strcat(printString, " X ");
    strcat(printString, name);

    strcat(printString, "\n");
    if(i > 0){
      write(STDOUT_FILENO, printString, strlen(printString));
    }

    free(printString);
    free(vmaString);

    //process_symbol (symbol_table[i]);
  }


  return 0;
}

int getIntSize(int string, int base){
  int count = 1;
  while(string >= base){
      string /= base;
      count++;
  }
  return count;
}

char* intToString(int input, int base, int size, char* string){

  //printf("Size: %d\n", size);
  int i = size - 1;

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
