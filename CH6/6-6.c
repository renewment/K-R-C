/*
 * Exercise 6-5: Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of thist
 * section. You may also find getch and ungetch helpful.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nlist {       /* table entry: */
   struct nlist *next;  /* next entry in chain */
   char *name;          /* defined name */
   char *defn;          /* replacement text */
};

#define HASHSIZE 101
#define WORDLENGTH 1000
int getword(char *, int);
char keyword[] = "define";
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *Strdup(char *);
int getch(void);
void ungetch(int);

main()
{
   int c, cont = 1;
   char word[WORDLENGTH], name[WORDLENGTH], defn[WORDLENGTH];
   struct nlist *np;
   while ((c=getword(word, WORDLENGTH)) != EOF) {
      if (c == '#') {
         getword(word, WORDLENGTH);
         if (!strcmp(word, keyword)) {       // #define
            printf("%s", word);              // printf "define"
            
            // process symbolic constant name
            getword(word , WORDLENGTH);
            printf("%s", word);
            strcpy(name, word);
            
            // process symbolic constant value
            getword(word , WORDLENGTH);
            printf("%s", word);
            strcpy(defn, word);
            
            // add symbolic constant to hash table
            install(name, defn);
         } else
            printf("%s", word);
      } else if (c == '_' || isalnum(c)) {   // variable or numeric constant
         if ((np = lookup(word)))
            printf("%s", np->defn);
         else
            printf("%s", word);
      }
   }
   return 0;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
   int c, nextC, escape, asterisk;
   char *w = word;
   escape = asterisk = 0;
   
   while (isspace(c = getch()))
      printf("%c", c);
   *w++ = c;
   if (!isalnum(c) && // check alpha
       c != '_' &&    // check underscore
       c != '\'' &&   // check char
       c != '\"' &&   // check string constant
       c != '/' &&    // check start of line or block comment
       c != '#') {    // check preprocessor control
      *w = '\0';
      printf("%c", c);
      return c;
   }
   if (c == '\'') {              // parse single character
      if ((c=getch()) == '\\') {
         *w++ = c;
         *w++ = getch();
      }
      *w++ = getch();
      *w = '\0';
      printf("%s", w);
      return '\'';
   }
   if (c == '\"') {       // parse string
      while ((c=getch()) != EOF) {
         *w++ = c;
         if (c == '\\' && !escape)
            escape = 1;
         else if (escape)
            escape = 0;
         else if (c == '\"')
            break;
      }
      *w = '\0';
      printf("%s", w);
      return '\"';
   }
   if (c == '/') {
      if ((nextC=getch()) == '/') {         // line comment
         *w++ = nextC;
         while ((c=getch()) != EOF) {
            *w++ = c;
            if (c == '\n') {
               ungetch(c);
               break;
            }
         }
      } else if (nextC == '*') {            // block comment
         *w++ = nextC;
         while ((c=getch()) != EOF) {
            *w++ = c;
            if (c == '*')
               asterisk = 1;
            else if (c == '/' && asterisk)
               break;
            else
               asterisk = 0;
         }
      } else                                // slash for division
         ungetch(nextC);
      *w = '\0';
      return '/';
   }
   if (c == '#') {
      printf("%c", c);
      *w = '\0';
      return '#';
   }
   for ( ; --lim > 0; w++)
      if (!isalnum(*w = getch()) &&       // check alpha or number
          *w != '_') {                     // check underscore
         ungetch(*w);
         break;
      }
   
   //TODO: check if there is any defined symbolic constant
   *w = '\0';
   return word[0];
}

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

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
   return (bufp > 0) ? buf[--bufp] :  getchar();
}

void ungetch(int c) /* push character back on input */
{
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}
