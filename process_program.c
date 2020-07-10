#include <stdio.h>
#include <utmp.h>
#include <sys/utsname.h>
#include <dirent.h>
//#include <pwd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>

int main(){
//        struct passwd *password = calloc(1, sizeof(struct passwd));
        struct utmp *name;
        DIR* proc = opendir("/proc");
        struct dirent* ent;
        long id;
        int i = 0;
        setutent();
        name = getutent();

        if(proc == NULL){
                perror("opendir(/proc)");
                return 1;
        }

        while(name){
                if(name->ut_type == USER_PROCESS){
                        printf("user:%9s tty:%12s host:(%s) uid:(%d)\n", name->ut_user, name->ut_line, name->ut_host, name->ut_id);
                }
                        name = getutent();
        }

        printf("\n");
        while(NULL != (ent = readdir(proc)) ){
                i++;
                id = strtol(ent->d_name, NULL, 10);

                if (0 == id) continue;
                struct stat sb;
                char path[1001];
                memset(path, '\0', 1001);
                snprintf(path, 1000, "/proc/%s", ent->d_name);
                if (lstat(path, &sb) == -1) {
	             continue;
		}

		printf("pid: %ld, uid: %lld\n", id, (unsigned long long)sb.st_uid);
	}
}
