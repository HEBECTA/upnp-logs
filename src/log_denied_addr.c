#include "log_denied_addr.h"

#include <syslog.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

const char failed_wr_err_log_msg[] = "failed to write denied address to log file";

static const char denied_addr_file[] = "/log/upnp_denied_addr";

static const char *sql_init = "CREATE TABLE if not exists DENIED_ACCESS_ADDRS ("
        "ID                     INTEGER PRIMARY KEY,"
        "Eport                  INT,"
        "Address                TEXT,"
        "Iport                  INT,"
        "Protocol               TEXT,"
        "Err_flag               INT,"
        "Date                   TEXT);";

static sqlite3 *db;
static int file_opened = 0;

int open_denied_addr_file()
{
        file_opened = 0;

        int rc = sqlite3_open(denied_addr_file, &db);

        if (rc != SQLITE_OK) {

                syslog(LOG_ERR, "UPNP LOGGER: Failed to open file\n");

                return rc;
        }

        file_opened = 1;

        return rc;
}

void close_denied_addr_file()
{
        if (!file_opened)
                return;

        sqlite3_close(db);

        file_opened = 0;
}


int wr_denied_addr(unsigned short eport, const char * iaddr, unsigned short iport, const char * protocol, int error_flag)
{
        if (!file_opened)
                return ENOENT;

        int rc = sqlite3_exec(db, sql_init, 0, 0, NULL);

        if (rc != SQLITE_OK)
                return rc;

        char sql[EPORT_MAX_SIZE+ADDRESS_NAME_MAX_SIZE+IPORT_MAX_SIZE+PROTOCOL_NAME_MAX_SIZE+DATE_MAX_SIZE+100];

        time_t date = time(0); 
        sprintf(sql, "INSERT INTO DENIED_ACCESS_ADDRS (Eport, Address, Iport, Protocol, Err_flag, Date) "  \
        "VALUES (\"%hu\", \"%s\", \"%hu\", \"%s\", \"%d\", \"%s\");", eport, iaddr, iport, protocol,\
        error_flag, ctime(&date));

        rc = sqlite3_exec(db, sql, 0, 0, NULL);

        return rc;
}