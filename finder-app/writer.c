#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // error checking for arguments
    if (argc != 3) {
        fprintf(stderr, "Error: Missing arguments. Usage: <file_path> <text_to_write>\n");
        exit(1);
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    openlog(NULL, LOG_PID | LOG_CONS, LOG_USER);

    FILE *file = fopen(writefile, "w");
    if(!file) {
        syslog(LOG_ERR, "Error Opening file %s for writing", writefile);
        perror("Error opening file for writing!");
        exit(1);
    }

    fprintf(file, "%s", writestr);

    syslog(LOG_DEBUG, "Writing \"%s\" to %s", writestr, writefile);

    fclose(file);

    closelog();
    
    return 0;
}
