#include "CommentParserCommon.h"

class CommentParser;

/**
 * CommentParserState
 */
class CommentParserState {
public:
   void dispatch(CommentParser *context, Signal signal);

   virtual void onCHAR   (CommentParser *context) {}
   virtual void onSTAR   (CommentParser *context) {}
   virtual void onSLASH  (CommentParser *context) {}
   virtual void onNEWLINE(CommentParser *context) {}
};

/**
 * CodeState
 */
class CodeState : public CommentParserState {
public:
   virtual void onSLASH(CommentParser *context);
};

/**
 * SlashState
 */
class SlashState : public CommentParserState {
public:
   virtual void onCHAR   (CommentParser *context);
   virtual void onSTAR   (CommentParser *context);
   virtual void onSLASH  (CommentParser *context);
   virtual void onNEWLINE(CommentParser *context);
};

/**
 * CommentState
 */
class CommentState :  public CommentParserState {
public:
   virtual void onCHAR   (CommentParser *context);
   virtual void onSTAR   (CommentParser *context);
   virtual void onSLASH  (CommentParser *context);
   virtual void onNEWLINE(CommentParser *context);
};

/**
 * StarState
 */
class StarState :  public CommentParserState {
public:
   virtual void onCHAR   (CommentParser *context);
   virtual void onSTAR   (CommentParser *context);
   virtual void onSLASH  (CommentParser *context);
   virtual void onNEWLINE(CommentParser *context);
};

/**
 * QuickCommentState
 */
class QuickCommentState : public CommentParserState {
public:
   virtual void onCHAR   (CommentParser *context);
   virtual void onSTAR   (CommentParser *context);
   virtual void onSLASH  (CommentParser *context);
   virtual void onNEWLINE(CommentParser *context);
};

/**
 * CommentParser
 */
class CommentParser {
   friend class CodeState;
   friend class SlashState;
   friend class CommentState;
   friend class StarState;
   friend class QuickCommentState;

   static CodeState         myCodeState;
   static SlashState        mySlashState;
   static CommentState      myCommentState;
   static StarState         myStarState;
   static QuickCommentState myQuickCommentState;

public:
   CommentParser() : myState(&myCodeState) {}
   void initialize() { myCommentCounter = 0; transition(&myCodeState); }
   long getCommentCounter() { return myCommentCounter; }
   void dispatch(Signal signal) { myState->dispatch(this, signal); }

protected:
   void transition(CommentParserState *target) { myState = target; }

private:
   CommentParserState *myState;
   long myCommentCounter;

#if defined(UNIT_TEST)
public:
   unsigned getCurrentState(void);
   bool     isInitialized(void) { return ((myCommentCounter == 0) && (myState == &myCodeState)); }
#endif
};
