#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

char *userNameFromId(uid_t uid) {
    struct passwd *pwd;
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t userIdFromName(const char *name) {
    struct passwd *pwd;
    uid_t u;
    char *endptr;
    if(name == NULL || *name == '\0')
        return -1;
    u = strtol(name, &endptr, 10);
    if(*endptr == '\0')
        return u;
    pwd = getpwnam(name);
    if(pwd == NULL)
        return -1;
    return pwd->pw_uid;
}

char *groupNameFromId(gid_t gid) {
    struct group *grp;
    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char *name) {
    struct group *grp;
    gid_t g;
    char *endptr;
    if(name == NULL || *name == '\0')
        return -1;
    g = strtol(name, &endptr, 10);
    if(*endptr == '\0')
        return g;
    grp = getgrnam(name);
    if(grp == NULL)
        return -1;
    return grp->gr_gid;
}

int main(int argc, char const *argv[])
{
    uid_t uid = userIdFromName("lyz-ubuntu");
    printf("uid of lyz-ubuntu: %d\n", uid);
    char *userName = userNameFromId(uid);
    printf("user name: %s\n", userName);
    gid_t gid = groupIdFromName("lyz-ubuntu");
    printf("gid of lyz-ubuntu: %d\n", gid);
    char *groupName = groupNameFromId(gid);
    printf("group name: %s\n", groupName);
    return 0;
}
