#include "CommentParserCommon.h"

/**
 * Generic Event Parser
 */
class StateTable {
public:
   typedef void (StateTable::*Action) ();

   struct Transition {
      Action action;
      unsigned nextState;
   };

   StateTable (Transition const *table, unsigned nStates, unsigned nSignals)
      : myTable(table), myMaxSignals(nSignals), myMaxStates(nStates) { };

   virtual ~StateTable() {}

   void dispatch(unsigned const signal) {
      Transition const *t = myTable + myState * myMaxSignals + signal;
      (this->*(t->action))();
      myState = t->nextState;
   }

   void doNothing() {}

protected:
   unsigned myState;

private:
   Transition const * myTable;
   unsigned myMaxSignals;
   unsigned myMaxStates;

#if defined(UNIT_TEST)
public:
   unsigned getCurrentState(void)   { return myState; }
   virtual bool isInitialized(void) { return false; }
#endif
};

/**
 * CommentParser
 */
class CommentParser : public StateTable {
public:
   CommentParser() : StateTable(&myTable[0][0], MAX_STATE, MAX_SIG) {}
   void initialize() {myCommentCounter = 0; myState = CODE; }
   long getCommentCounter() { return myCommentCounter; }

protected:
   void add_one() { myCommentCounter += 1; }
   void add_two() { myCommentCounter += 2; }

private:
   static StateTable::Transition const myTable[MAX_STATE][MAX_SIG];

   long myCommentCounter;

#if defined(UNIT_TEST)
public:
   virtual bool isInitialized(void) { return ((myCommentCounter == 0) && (myState == CODE)); }
#endif
};

