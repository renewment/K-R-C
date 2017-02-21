/*
 * Exercise 4-1: Write the function strrindex(s,t), which returns the position
 * of the rightmost occurrence of t in s, of -1 if there is none.
 */

#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

main()
{
	char line[MAXLINE];
	int found = 0;
	int position;
	while (getLine(line, MAXLINE) > 0) 
		if ((position=strrindex(line, pattern)) >= 0) {
			printf("string: %s, position: %d\n", line, position);
			found++;
		}
	return found;
}

int getLine(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strrindex(char s[], char t[])
{
	int i, j, k;
	int position = -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			position = i;
	}
	return position;
}
