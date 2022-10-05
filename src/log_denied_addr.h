#ifndef LOG_DENIED_ADDR_H
#define LOG_DENIED_ADDR_H

#include <sqlite3.h>

#define EPORT_MAX_SIZE 7
#define ADDRESS_NAME_MAX_SIZE 40
#define IPORT_MAX_SIZE 7
#define PROTOCOL_NAME_MAX_SIZE 10
#define DATE_MAX_SIZE 20

extern const char failed_wr_err_log_msg[];

enum {

        PORT_IN_USE,
        PERMISSION_DENIED,
        ALREADY_IN_USE
};

int open_denied_addr_file();

void close_denied_addr_file();

int wr_denied_addr(unsigned short eport, const char * iaddr, unsigned short iport, const char * protocol, int error_flag);

#endif