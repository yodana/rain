#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    if (num != 423) {
        fwrite("Wrong number", 12, 1, stderr);
        return 0;
    }
    
    char *cmd = strdup("/bin/sh");
    char *args[] = {cmd, NULL};
    gid_t egid = getegid();
    uid_t euid = geteuid();
    
    setresgid(egid, egid, egid);
    setresuid(euid, euid, euid);
    execv(cmd, args);
    return 0;
}