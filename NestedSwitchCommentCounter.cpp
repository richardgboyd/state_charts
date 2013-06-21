/**
 * State Machine Implemented with Nested Switch
 */
#include "NestedSwitchCommentCounter.h"

void CommentParser::dispatch(unsigned const signal)
{
   switch (myState)
   {
   case CODE:
      switch (signal)
      {
      case SLASH_SIG:
         transition(SLASH);
         break;
      }
      break;
   case SLASH:
      switch (signal)
      {
      case STAR_SIG:
         myCommentCounter += 2;
         transition(COMMENT);
         break;
      case CHAR_SIG:
      case NEWLINE_SIG:
         transition(CODE);
         break;
      case SLASH_SIG:
         myCommentCounter += 2;
         transition(QUICK_COMMENT);
         break;
      }
      break;
   case COMMENT:
      switch (signal)
      {
      case CHAR_SIG:
      case SLASH_SIG:
      case NEWLINE_SIG:
         myCommentCounter += 1;
         break;
      case STAR_SIG:
         transition(STAR);
         break;
      }
      break;
   case STAR:
      switch (signal)
      {
      case SLASH_SIG:
         myCommentCounter += 2;
         transition(CODE);
         break;
      case STAR_SIG:
         myCommentCounter += 1;
         break;
      case CHAR_SIG:
      case NEWLINE_SIG:
         myCommentCounter += 2;
         transition(COMMENT);
         break;
      }
      break;
   case QUICK_COMMENT:
      switch (signal)
      {
      case NEWLINE_SIG:
         myCommentCounter += 1;
         transition(CODE);
         break;
      case CHAR_SIG:
      case SLASH_SIG:
      case STAR_SIG:
         myCommentCounter +=1;
         break;
      }
   }
}

