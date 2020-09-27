#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <bfd.h>
#include <stdint.h>

#define inputSize 512
#define BFD_INIT_MAGIC (sizeof (struct bfd_section))

void bfd_text(char* file){
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

  int fd = open("text-output", O_WRONLY | O_CREAT, 0644);


  //printf("Printing Sections: \n");
  int count = 0;;
  asection *b;

  b = bfd_get_section_by_name(my_bfd, ".text");

  unsigned char* p[2];
  int maxCount = b->size;
  int i = 0;
  for(i; i < b->size; i++){
    if(bfd_get_section_contents(my_bfd, b, p, i, 1)){
      //printf("Got File\n");
      //printf("%c", p[0]);
      write(fd, p, 1);

      p[1] = '\0';
    }else{
      printf("OH NO\n");
    }
  }

  bfd_close(my_bfd);

  close(fd);

  return;
}
