#include "CommentParserCommon.h"

class FiniteStateMachine {
public:
   typedef void (FiniteStateMachine::*State)(int signal);
   FiniteStateMachine(State initial) : myState(initial) {}
   virtual ~FiniteStateMachine() {}
   void initialize() { dispatch(0); }
   void dispatch(int signal) { (this->*myState)(signal); }

protected:
   void transition(State target) { myState = target; }
   #define TRAN(target_) transition(static_cast<State>(target_))
   State myState;

#if defined(UNIT_TEST)
public:
   virtual unsigned getCurrentState(void) = 0;
   virtual bool isInitialized(void) { return false; }
#endif
};

class CommentParser : public FiniteStateMachine {
public:
   CommentParser() : FiniteStateMachine((State)&CommentParser::initial) {}
   long getCommentCounter() { return myCommentCounter; }

private:
   void initial(int);
   void code(int signal);
   void slash(int signal);
   void comment(int signal);
   void star(int signal);
   void quick_comment(int signal);

private:
   long myCommentCounter;

#if defined(UNIT_TEST)
public:
   virtual bool isInitialized(void) 
   { 
      return ((myState == (State)&CommentParser::initial) && (myCommentCounter == 0)); 
   }

   virtual unsigned getCurrentState(void);
#endif
};

