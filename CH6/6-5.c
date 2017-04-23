/*
 * Exercise 6-5: Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct nlist {       /* table entry: */
   struct nlist *next;  /* next entry in chain */
   char *name;          /* defined name */
   char *defn;          /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *Strdup(char *);
int undef(char *);

/* hash:  form hash value for string s */
unsigned hash(char *s)
{
   unsigned hashval;
   
   for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
   return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
   struct nlist *np;
   
   for (np = hashtab[hash(s)]; np != NULL; np = np->next)
      if (strcmp(s, np->name) == 0)
         return np;  /* found */
   return NULL;      /* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
   struct nlist *np;
   unsigned hashval;
   
   if ((np = lookup(name)) == NULL) {  /* not found */
      np = (struct nlist *) malloc(sizeof(*np));
      if (np == NULL || (np->name = Strdup(name)) == NULL)
         return NULL;
      hashval = hash(name);
      np->next = hashtab[hashval];
      hashtab[hashval] = np;
   } else      /* already there */
      free((void *) np->defn);   /* free previous defn */
   if ((np->defn = Strdup(defn)) == NULL)
      return NULL;
   return np;
}

char *Strdup(char *s)   /* make a duplicate of s */
{
   char *p;
   p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
   if (p != NULL)
      strcpy(p, s);
   return p;
}

int undef(char *name)
{
   struct nlist *np, *previous;
   unsigned hashval = hash(name);
   if (hashtab[hashval]) {
      np = hashtab[hashval];
      previous = NULL;
      while (np) {
         if (strcmp(name, np->name)) {
            previous = np;
            np = np->next;
         } else
            break;
      }
      if (np) {            // in linked list
         if (!previous) {  // remove the first entry of linked list
            hashtab[hashval] = np->next;
            // how to free a list node has not been mentioned, so work is done
         } else {
            previous->next = np->next;
         }
         return 0;
      }
   }
   printf("there is no entry \"%s\" in lookup table\n", name);
   return -1;
}
