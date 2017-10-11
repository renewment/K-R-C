/*
 * Example code of header file of dirent.h in Section 8.6
 */

#define NAME_MAX  14  /* longest filename components; */
                              /* system-dependent */

typedef struct {     /* portable directory entry: */
   long ino;                  /* inode number */
   char name[NAME_MAX+1];     /* name + '\0' terminator */
} Dirent;

typedef struct {     /* minimal DIR: no buffering, etc. */
   int fd;              /* file descriptor for directory */
   Dirent d;            /* the directory entry */
} _DIR;

_DIR *openDir(char *dirname);
Dirent *readDir(_DIR *dfd);
void closeDir(_DIR *dfd);
