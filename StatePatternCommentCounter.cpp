#include "StatePatternCommentCounter.h"

CodeState         CommentParser::myCodeState;
SlashState        CommentParser::mySlashState;
CommentState      CommentParser::myCommentState;
StarState         CommentParser::myStarState;
QuickCommentState CommentParser::myQuickCommentState;

void CommentParserState::dispatch(CommentParser *context, Signal signal)
{
   switch (signal) {
      case CHAR_SIG:    onCHAR(context);    break;
      case SLASH_SIG:   onSLASH(context);   break;
      case STAR_SIG:    onSTAR(context);    break;
      case NEWLINE_SIG: onNEWLINE(context); break;
   }
};

/*******************************************************************************
 * Code state operations
 ******************************************************************************/
void CodeState::onSLASH(CommentParser *context) {
   context->transition(&CommentParser::mySlashState);
};

/*******************************************************************************
 * Slash state operations
 ******************************************************************************/
void SlashState::onCHAR(CommentParser *context) {
   context->transition(&CommentParser::myCodeState);
}

void SlashState::onSTAR(CommentParser *context) {
   context->myCommentCounter += 2;
   context->transition(&CommentParser::myCommentState);
}

void SlashState::onSLASH(CommentParser *context) {
   context->myCommentCounter += 2;
   context->transition(&CommentParser::myQuickCommentState);
}

void SlashState::onNEWLINE(CommentParser *context) {
   context->transition(&CommentParser::myCodeState);
}

/*******************************************************************************
 * Comment state operations
 ******************************************************************************/
void CommentState::onCHAR(CommentParser *context) {
   context->myCommentCounter += 1;
}

void CommentState::onSTAR(CommentParser *context) {
   context->transition(&CommentParser::myStarState);
}

void CommentState::onSLASH(CommentParser *context) {
   context->myCommentCounter += 1;
}

void CommentState::onNEWLINE(CommentParser *context) {
   context->myCommentCounter += 1;
}

/*******************************************************************************
 * Star state operations
 ******************************************************************************/
void StarState::onCHAR(CommentParser *context) {
   context->myCommentCounter += 2;
   context->transition(&CommentParser::myCommentState);
}

void StarState::onSTAR(CommentParser *context) {
   context->myCommentCounter += 1;
   context->transition(&CommentParser::myStarState);
}

void StarState::onSLASH(CommentParser *context) {
   context->myCommentCounter += 2;
   context->transition(&CommentParser::myCodeState);
}

void StarState::onNEWLINE(CommentParser *context) {
   context->myCommentCounter += 2;
   context->transition(&CommentParser::myCommentState);
}

/*******************************************************************************
 * Quick Comment state operations
 ******************************************************************************/
void QuickCommentState::onCHAR(CommentParser *context) {
   context->myCommentCounter += 1;
}

void QuickCommentState::onSTAR(CommentParser *context) {
   context->myCommentCounter += 1;
}
void QuickCommentState::onSLASH(CommentParser *context) {
   context->myCommentCounter += 1;
}

void QuickCommentState::onNEWLINE(CommentParser *context) {
   context->myCommentCounter += 1;
   context->transition(&CommentParser::myCodeState);
}

/*******************************************************************************
 * Unit Test operations
 ******************************************************************************/
#if defined(UNIT_TEST)
unsigned CommentParser::getCurrentState(void)
{
   if (myState == &myCodeState)         return CODE;
   if (myState == &mySlashState)        return SLASH;
   if (myState == &myCommentState)      return COMMENT;
   if (myState == &myStarState)         return STAR;
   if (myState == &myQuickCommentState) return QUICK_COMMENT;

   return MAX_STATE;
}
#endif
