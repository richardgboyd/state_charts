#include "CommentParserCommon.h"

class CommentParser
{
public:
   void initialize() { myCommentCounter = 0; transition(CODE); }
   void dispatch(unsigned const signal);
   unsigned long getCommentCounter(void) const { return myCommentCounter; }

protected:
   void transition(State target) { myState = target; }

private:
   State myState;
   unsigned long myCommentCounter;

#if defined(UNIT_TEST)
public:
   unsigned getCurrentState(void) { return myState; }
   bool     isInitialized(void)   { return ((myCommentCounter == 0) && (myState == CODE)); }
#endif
};

