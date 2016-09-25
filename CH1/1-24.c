/*
 * Write a program to check a C program for redimentary
 * syntax errors like unbalanced parantheses, brackets
 * and braces. Don't forget about quotes, both single
 * and double, escape sequences, and comments. (this
 * program is hard if you do it in full generality.)
 */

#include "stdio.h"
#include <stdio.h>

void error(int line, int word, char c, char lastC);
main()
{
   int inSingleQuote, inDoubleQuote, lineComment, blockComment, inComment, inGuillemet, inParentheses, inBracket, inBrace, inContext, isEscape, isEnd;
   char bracket[1000];
   int line[1000], word[1000];
   int currentLine, currentWord, index;
   char c;
   
   inSingleQuote = inDoubleQuote = lineComment = blockComment = inComment = inGuillemet = inParentheses = inBracket = inBrace = isEscape = isEnd = 0;
   inContext = 1;
   currentLine = 1;
   currentWord = 1;
   index = 0;
   while ((c = getchar()) != EOF) {
      if (c == '<') {
         if (inBrace == 0 && inGuillemet == 0) {                        // include header
            inGuillemet = 1;
            inContext = 0;
         } else                                                         // conditional comparison
            ;
      }
      else if (c == '>') {                                              // include header
         if (inGuillemet == 1) {
            inGuillemet = 0;
            inContext = 1;
         } else                                                         // conditional comparison
            ;
      }
      else if (c == '{') {
         if (inContext == 1) {
            ++inBrace;                                                  // a new code block
            word[index] = currentWord;                                  // add brace to stack and record location
            line[index] = currentLine;
            bracket[index] = c;
            ++index;
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == '}') {
         if (inContext == 1) {
            if (bracket[index-1] != '{')                                   // mismatch
               error(currentLine, currentWord, c, word[index-1]);
            else {                                                      // match
               --index;
               --inBrace;
            }
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == '[') {
         if (inContext == 1) {
            ++inBracket;                                                // used for array
            word[index] = currentWord;                                  // add bracket to stack and record location
            line[index] = currentLine;
            bracket[index] = c;
            ++index;
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == ']') {
         if (inContext == 1) {
            if (bracket[index-1] != '[')                                   // mismatch
               error(currentLine, currentWord, c, word[index-1]);
            else {                                                      // used for array
               --index;
               --inBracket;
            }
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == '(') {
         if (inContext == 1) {                                          // add parentheses to stack and record location
            ++inParentheses;
            word[index] = currentWord;
            line[index] = currentLine;
            bracket[index] = c;
            ++index;
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == ')') {
         if (inContext == 1) {
            if (bracket[index-1] != '(') {
               error(currentLine, currentWord, c, word[index-1]);
            }
            else {
               --index;
               --inParentheses;
            }
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == '\'') {
         if (inContext == 1) {                                          // first quote for character constant
            inContext = 0;
            inSingleQuote = 1;
         } else if (inSingleQuote == 1 && isEscape == 0) {              // last quote for character constant
            inContext = 1;
            inSingleQuote = 0;
         } else if (isEscape == 1) {                                    // escape
            isEscape = 0;
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == '\"') {
         if (inContext == 1) {                                          // first quote for string constant
            inContext = 0;
            inDoubleQuote = 1;
         } else if (inDoubleQuote == 1 && isEscape == 0) {              // last quote for string constant
            inContext = 1;
            inDoubleQuote = 0;
         } else if (isEscape == 1) {
            isEscape = 0;
         } else                                                         // in comment, single quote or double quote
            ;
      }
      else if (c == '\\') {
         if (isEscape == 0)
            isEscape = 1;                                               // time to escape
         else
            isEscape = 0;
      }
      else if (c == '/') {
         if (inContext == 1) {
            if (lineComment == 0 && blockComment == 0) {                // may be the start of comment
               lineComment = 1;
               blockComment = 1;
            } else if (lineComment == 1) {                              // line comment
               inContext = 0;
               inComment = 1;
               blockComment = 0;
            }
         } else if (isEnd == 1) {                                       // end of block comment
            inContext = 1;
            inComment = 0;
            blockComment = 0;
            isEnd = 0;
         } else
            ;
      }
      else if (c == '*') {
         if (blockComment == 1 && inComment == 0) {                     // block comment
            inContext = 0;
            inComment = 1;
            lineComment = 0;
         } else if (blockComment == 1 && inComment == 1) {              // may be the end of block comment
            isEnd = 1;
         } else
            ;
      }
      else if (c == '\n') {
         if (lineComment == 1 && inComment == 1) {
            inContext = 1;
            inComment = 0;
            lineComment = 0;
         } else if (inSingleQuote == 1) {
            error(currentLine, currentWord, '\0', '\'');
         } else if (inDoubleQuote == 1) {
            error(currentLine, currentWord, '\0', '\"');
         } else
            ;
         ++currentLine;
         currentWord = 1;
      }
      else if (c == 'n' || c == 't' || c == 'b' || c == 'r' || c == '0') {
         if (isEscape == 1)
            isEscape = 0;
         else
            ;
      }
      else {
         if (lineComment == 1 && blockComment == 1 && inContext == 1) {
            lineComment = 0;
            blockComment = 0;
            putchar('/');
         } else
            ;
      }
      ++currentWord;
   }
   return 0;
}

void error(int line, int word, char c, char lastC)
{
   printf("at line %d, word %d, ", line , word);
   if (lastC == '<') {
      putchar('>');
   } else if (c == '(') {
      putchar(')');
   } else if (lastC == '[') {
      putchar(']');
   } else if (c == '{') {
      putchar('}');
   } else if (c == '\'') {
      putchar('\'');
   } else if (c == '\"') {
      putchar('\"');
   } else
      putchar(c);
   printf(" is expected rather than %c\n", c);
}
