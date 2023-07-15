#ifndef _FILE_H_
#define _FILE_H_

#include "types.h"


#define FILE_SERVER_1  "SERVER1.dat"
#define FILE_SERVER_2  "SERVER2.dat"
#define FILE_SERVER_3  "SERVER3.dat"
#define FILE_SERVER_4  "SERVER4.dat"

#define ERR_MSG_OPEN    "Error opening the file %s.\n"


Header FILE_read_header(char *file_name);


Log FILE_read_log(char *file_name);



#endif
