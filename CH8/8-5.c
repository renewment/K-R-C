/*
 * Exercise 8-5: Modify the fsize program to print the other information
 * contained in the inode entry.
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      /* flags for read and write */
#include <sys/types.h>  /* typedefs */
#include <sys/stat.h>   /* structure returned by stat */
#include "dirent.h"
#include <stdlib.h>
#include <time.h>

void fsize(char *);

/* print file sized */
main(int argc, char **argv)
{
   printf("%6s  %8s %25s\n", "file name", "file size", "last change");
   if (argc == 1)       /* default: current directory */
      fsize(".");
   else
      while (--argc > 0)
         fsize(*++argv);
   return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize:  print size of file "name" */
void fsize(char *name)
{
   struct stat stbuf;
   
   if (stat(name, &stbuf) == -1) {
      fprintf(stderr, "fsize: can't access %s\n", name);
      return;
   }
   if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
      dirwalk(name, fsize);
   printf("%9s  %9ld  %25s", name, stbuf.st_size, ctime(&stbuf.st_ctime));
   
}

#define MAX_PATH 1024

/* dirwalk:  apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
   char name[MAX_PATH];
   Dirent *dp;
   _DIR *dfd;
   
   if ((dfd = openDir(dir)) == NULL) {
      fprintf(stderr, "dirwalk: can't open %s\n", dir);
      return;
   }
   while ((dp = readDir(dfd)) != NULL) {
      if (strcmp(dp->name, ".") == 0
       || strcmp(dp->name, "..") == 0)
         continue;   /* skip self and parent */
      if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
         fprintf(stderr, "dirwalk: name %s%s too long\n", dir, dp->name);
      else {
         sprintf(name, "%s%s", dir, dp->name);
         (*fcn)(name);
      }
   }
   closeDir(dfd);
}

int fstat(int fd, struct stat *);

/* opendir:  open a directory for readdir calls */
_DIR *openDir(char *dirname)
{
   int fd;
   struct stat stbuf;
   _DIR *dp;
   
   if ((fd = open(dirname, O_RDONLY, 0)) == -1
     || fstat(fd, &stbuf) == -1
     || (stbuf.st_mode & S_IFMT) != S_IFDIR
     || (dp = (_DIR *) malloc(sizeof(_DIR))) == NULL)
      return NULL;
   dp->fd = fd;
   return dp;
}

/* closedir:  close directory opened by opendir */
void closeDir(_DIR *dp)
{
   if (dp) {
      close(dp->fd);
      free(dp);
   }
}

#include <sys/dir.h>    /* local directory structure */
#define DIRSIZE  14

/* readdir:  read directory entries in sequence */
Dirent *readDir(_DIR *dp)
{
   struct direct dirbuf; /* local directory structure */
   static Dirent d;      /* return: potble structure */
   while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
      if (dirbuf.d_ino == 0)     /* slot not in use */
         continue;
      d.ino = dirbuf.d_ino;
      strncpy(d.name, dirbuf.d_name, DIRSIZE);
      d.name[DIRSIZE] = '\0';  /* ensure termination */
      return &d;
   }
   return NULL;
}
