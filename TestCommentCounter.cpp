#if defined(NESTED_SWITCH)
   #include "NestedSwitchCommentCounter.h"
#elif defined(STATE_TABLE)
   #include "StateTableCommentCounter.h"
#elif defined(STATE_PATTERN)
   #include "StatePatternCommentCounter.h"
#else // defined(STATE_MACHINE="OPTIMAL")
   #include "OptimalCommentCounter.h"
#endif

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv)
{
   CommentParser commentParser;
   int c;
   FILE *handle;

   if(argc < 2)
   {
      printf("%s passed invalid argument list.\n", argv[0]);
      printf("   usage %s <file_name>");
      exit(1);
   }

   handle = fopen(argv[1], "r");

   if (handle != NULL) 
   {
      commentParser.initialize();

      c = fgetc(handle);

      while (c != EOF)
      {
         switch (c)
         {
         case '/':
            commentParser.dispatch(SLASH_SIG);
            break;
         case '*':
            commentParser.dispatch(STAR_SIG);
            break;
         default:
            commentParser.dispatch(CHAR_SIG);
            break;
         }

         c = fgetc(handle);
      }

      printf(
         "%s found %d comment characters.\n", 
         argv[0], commentParser.getCommentCounter()
      );
       
      fclose(handle);
   }
   else 
   {
      printf("%s could not open file %s\n", argv[0], argv[1]);
   }
}

