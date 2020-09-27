#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <bfd.h>

#define inputSize 512
#define BFD_INIT_MAGIC (sizeof (struct bfd_section))

#define MAX_CHAR 100
typedef char string[MAX_CHAR+1];


int getIntSizeA(int input, int base);
char* intToStringA(int input, int base, int size, char* index);
void bfd_print(asection *bfd_section);

void bfd_dump(char* file){
  bfd_init();

  bfd* my_bfd = bfd_openr(file, NULL);
  if(!my_bfd){
    printf("Open my_bfd failed!\n");
    return;
  }

  if (!bfd_check_format (my_bfd, bfd_object))
  {
    bfd_close (my_bfd);
    return;
  }


  char* header_line = " Idx   Name                Size      VMA               LMA               File off  Algn\n";
  write(STDOUT_FILENO, header_line, strlen(header_line));



  //printf("Printing Sections: \n");
  int count = 0;;
  asection* p;
  for(p = my_bfd->sections; p!= NULL && count < 5; p = p->next){
    //count++;
    bfd_print(p);

  }
  //printf("Terminating\n");
  bfd_close(my_bfd);

  return;
}


void bfd_print(asection *p){
  int id_buffer = 3;
  int name_buffer = 20;
  int size_buffer = 2;
  int VMA_buffer = 2;

  int size_size = 8;
  int vma_size = 16;
  int lma_size = 16;
  int off_size = 8;

  int LMA_buffer = 2;

  char* printString = (char*) malloc(MAX_CHAR);


  //Getting name
  char* name;
  name =  (char*)(p->name);


  //Getting and formatting for index/
  int idx = p->index;
  int indexSize = getIntSizeA(idx, 10);

  char* index = malloc(sizeof(char) * (indexSize));
  intToStringA(idx, 10, indexSize, index);


  //Getting information for Size
  int size = p->size;
  int sizeSize = getIntSizeA(size, 16);

  char* sizeString = malloc(sizeof(char) * sizeSize);
  intToStringA(size, 16, sizeSize, sizeString);

  //Getting and formatting VMA.
  //printf("%s\n", vmaString);
  int vma = p->vma;
  int vmaSize = getIntSizeA(vma, 16);

  char* vmaString = malloc(sizeof(char) * vmaSize);
  intToStringA(vma, 16, vmaSize, vmaString);


  int lma = p->lma;
  int lmaSize = getIntSizeA(lma, 16);

  char* lmaString = malloc(sizeof(char) * lmaSize);
  intToStringA(lma, 16, lmaSize, lmaString);

  int off = p->filepos;
  int offSize = getIntSizeA(off, 16);

  char* offString = malloc(sizeof(char) * offSize);
  intToStringA(off, 16, offSize, offString);

  int align = p->alignment_power;
  int alignSize = getIntSizeA(align, 16);

  char* alignString = malloc(sizeof(char) * alignSize);
  intToStringA(align, 16, alignSize, alignString);


  strcpy(printString, " ");
  int i = 0;
  for(i = indexSize; i < id_buffer; i++){
    strcat(printString, " ");
  }

  if(idx == 0){
    strcat(printString, "0");
  }else{
    strcat(printString, index);
  }


  strcat(printString, "   ");
  strcat(printString, (char* ) name);
  for(i = strlen(name); i < name_buffer; i++){
    strcat(printString, " ");
  }


  // All information for formatting the Size part.
  for(i = sizeSize; i < size_size; i++){
    strcat(printString, "0");
  }
  strcat(printString, sizeString);
  for(i = 0; i < VMA_buffer; i++){
    strcat(printString, " ");
  }




  //All formatting for the VMA string part.
  for(i = vmaSize; i < vma_size; i++){
    strcat(printString, "0");
  }
  strcat(printString, vmaString);
  for(i = 0; i < VMA_buffer; i++){
    strcat(printString, " ");
  }



  //All formatting for the LMA string part.
  for(i = lmaSize; i < lma_size; i++){
    strcat(printString, "0");
  }
  strcat(printString, lmaString);
  for(i = 0; i < VMA_buffer; i++){
    strcat(printString, " ");
  }


  for(i = offSize; i < off_size; i++){
    strcat(printString, "0");
  }
  strcat(printString, offString);
  for(i = 0; i < VMA_buffer; i++){
    strcat(printString, " ");
  }

  strcat(printString, "2**");
  strcat(printString, alignString);











  strcat(printString, "\n");

  write(STDOUT_FILENO, printString, strlen(printString));
  //free(printString);
  //free(index);
  //free(sizeString);
}

int getIntSizeA(int string, int base){
  int count = 1;
  while(string >= base){
      string /= base;
      count++;
  }
  return count;
}

char* intToStringA(int input, int base, int size, char* string){

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
