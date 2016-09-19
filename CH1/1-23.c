/*
 * Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character
 * constants properly. C comments do not nest.
 */

#include <stdio.h>

main()
{
   int lineComment, blockComment, inComment, inSingleQuote, inDoubleQuote, inContext, isEnd, isEscape;
   char c;
   
   int counter;
   char code[1000];
   
   lineComment = blockComment = inComment = inSingleQuote = inDoubleQuote = isEnd = 0;
   counter = 0;
   inContext = 1;
   while ((c = getchar()) != EOF) {
      if (c == '/') {
         if (inContext == 1 && lineComment == 0 && blockComment == 0 && inSingleQuote == 0 && inDoubleQuote == 0)// 出現第一個斜線時
            lineComment = blockComment = 1;
         else if (inContext == 1 && lineComment == 1) {              // 出現單行註解的第二個斜線
            inComment = 1;
            inContext = blockComment = 0;
         } else if (isEnd == 1) {                                    // 出現區塊註解的結束斜線
            blockComment = inComment = 0;
            inContext = 1;
         } else if (inComment != 1) {                                                    // 斜線出現註解以外的地方
            code[counter] = c;
            ++counter;
         }
      } else if (c == '*') {
         if (inContext == 1 && blockComment == 1) {                  // 區塊註解的開始
            inComment = 1;
            inContext = lineComment = 0;
         } else if (inComment == 1 && blockComment == 1)             // 可能是區塊註解的結束
            isEnd = 1;
         else {
            code[counter] = c;
            ++counter;
         }
      } else if (c == '\'') {                                        //字元常數的起頭單引號
         if (inContext == 1) {
            inContext = 0;
            inSingleQuote = 1;
            code[counter] = c;
            ++counter;
         } else if (inSingleQuote == 1 && isEscape == 1) {           //字元常數中的'字元
            isEscape = 0;
            code[counter] = c;
            ++counter;
         } else if (inSingleQuote == 1 && isEscape == 0) {           //字元常數的結尾單引號
            inSingleQuote = 0;
            inContext = 1;
            code[counter] = c;
            ++counter;
         } else if (inDoubleQuote == 1 && isEscape == 1) {
            isEscape = 0;
            code[counter] = c;
            ++counter;
         }
      } else if (c == '\"') {
         if (inContext == 1) {                                       //字串常數的起頭雙引號
            inContext = 0;
            inDoubleQuote = 1;
            code[counter] = c;
            ++counter;
         } else if (isEscape == 1) {                                 //字串常數中的"字元
            isEscape = 0;
            code[counter] = c;
            ++counter;
         } else if (inDoubleQuote == 1 && isEscape == 0) {           //字串常數的結尾雙引號
            inDoubleQuote = 0;
            inContext = 1;
            code[counter] = c;
            ++counter;
         }
      } else if (c == '\\') {
         if (isEscape == 0 && (inSingleQuote == 1 || inDoubleQuote == 1)) {
            isEscape = 1;
            code[counter] = c;
            ++counter;
         } else if (isEscape == 1) {
            isEscape = 0;
            code[counter] = c;
            ++counter;
         }
      } else if (c == '\n') {
         if (inComment == 1 && lineComment == 1) {
            inComment = lineComment = 0;
            inContext = 1;
         } else if (inContext == 1) {
            code[counter] = c;
            ++counter;
         }
      } else {
         if (inContext == 1) {
            if (lineComment == 1) {
               lineComment = blockComment = 0;
               code[counter] = '/';
               ++counter;
            }
            code[counter] = c;
            ++counter;
         } else if (inSingleQuote == 1 || inDoubleQuote == 1) {
            code[counter] = c;
            ++counter;
         }
         if (isEscape == 1)
            isEscape = 0;
      }
   }
   code[counter] = '\0';
   printf("%s" , code);
   return 0;
}
