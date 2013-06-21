#include "OptimalCommentCounter.h"

void CommentParser::initial(int) {
   myCommentCounter = 0;
   TRAN(&CommentParser::code);
}

void CommentParser::code(int signal) {
   switch (signal) 
   {
   case SLASH_SIG:
      TRAN(&CommentParser::slash);
      break;
   case CHAR_SIG:
   case STAR_SIG:
   case NEWLINE_SIG:
      break;
   };
};

void CommentParser::slash(int signal) {
   switch (signal) 
   {
   case STAR_SIG:
      myCommentCounter += 2;
      TRAN(&CommentParser::comment);
      break;
   case CHAR_SIG:
   case NEWLINE_SIG:
      TRAN(&CommentParser::code);
      break;
   case SLASH_SIG:
      myCommentCounter += 2;
      TRAN(&CommentParser::quick_comment);
      break;
   }
}

void CommentParser::comment(int signal) {
   switch (signal)
   {
   case STAR_SIG:
      TRAN(&CommentParser::star);
      break;
   case CHAR_SIG:
   case SLASH_SIG:
   case NEWLINE_SIG:
      myCommentCounter += 1;
      break;
   }
}

void CommentParser::star(int signal) {
   switch (signal)
   {
   case SLASH_SIG:
      myCommentCounter += 2;
      TRAN(&CommentParser::code);
      break;
   case CHAR_SIG:
   case NEWLINE_SIG:
      myCommentCounter += 2;
      TRAN(&CommentParser::comment);
      break;
   case STAR_SIG:
      myCommentCounter += 1;
      break;
   }
}

void CommentParser::quick_comment(int signal) {
   switch (signal)
   {
   case SLASH_SIG:
   case CHAR_SIG:
   case STAR_SIG:
      myCommentCounter += 1;
      break;
   case NEWLINE_SIG:
      myCommentCounter += 1;
      TRAN(&CommentParser::code);
      break;
   }
}

#if defined(UNIT_TEST)
unsigned CommentParser::getCurrentState(void)
{
   if (myState == (State)&CommentParser::code)          return CODE;
   if (myState == (State)&CommentParser::slash)         return SLASH;
   if (myState == (State)&CommentParser::comment)       return COMMENT;
   if (myState == (State)&CommentParser::star)          return STAR;
   if (myState == (State)&CommentParser::quick_comment) return QUICK_COMMENT;

   return MAX_STATE;
}
#endif
