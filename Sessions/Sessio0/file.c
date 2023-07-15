#include "file.h"
#include <fcntl.h>

void show_error_open(char *file_name) {
  char buffer[FILENAME_MAX + sizeof(ERR_MSG_OPEN)];

  int bytes = sprintf(buffer, ERR_MSG_OPEN, file_name);

  write(1, buffer, bytes);
}

char* read_string(int fd, char end) {
    char *buffer = (char *) malloc(1);
    int i = 0;

    while ((read(fd, &buffer[i], 1)) > 0 && buffer[i++] != end)
        buffer = (char *) realloc(buffer, i + 1);

    buffer[i - 1] = '\0';

    return buffer;
}


Header FILE_read_header(char *file_name){
  Header header;
  char aux;

  header.id = -1;
  strcpy(header.date, "\0");
  //printf("file_name: %s\n", file_name);
  
  int fd = open("SERVER2.dat", O_RDONLY);
  //printf("fd: %d\n", fd);
  if (fd > 0){
    lseek(fd, 0, SEEK_CUR);
    read(fd, &header.id, sizeof(int));
    read(fd, &aux, 1);

    strcpy(header.date, read_string(fd, '\n'));
    lseek(fd, 0, SEEK_CUR);
  }else{
    show_error_open(file_name);
  }
  close (fd);
  return header;
}
