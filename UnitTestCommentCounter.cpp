#include "UnitTestCommentCounter.h"

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

bool verbose_unit_testing = true;
bool stop_on_failure      = false;
int  failed_tests;
int  passed_tests;

/**
 * testEqual operations
 */
void UnitTest_testEqual(const char * test_name, bool value1, bool value2)
{
   if (value1 == value2)
   {
      passed_tests++;

      if (verbose_unit_testing)
         printf("PASSED - %s\n", test_name);
   }
   else
   {
      failed_tests++;
      printf("FAILED - %s (%d != %d)\n", test_name, value1, value2);

      if (stop_on_failure) exit(1);
   }
}

void UnitTest_testEqual(const char * test_name, int value1, int value2)
{
   if (value1 == value2)
   {
      passed_tests++;

      if (verbose_unit_testing)
         printf("PASSED - %s\n", test_name);
   }
   else
   {
      failed_tests++;
      printf("FAILED - %s (%d != %d)\n", test_name, value1, value2);

      if (stop_on_failure) exit(1);
   }
}

/**
 * Unit test operations.
 */
void UnitTestCommentParser_initialized(CommentParser * commentParser)
{
   commentParser->initialize();

   UnitTest_testEqual(
      "UnitTestCommentParser_initialized", commentParser->getCurrentState(), CODE);
}

CommentParser * UnitTestCommentParser_TransitionFromStateToState(
   const char *    test_name,
   CommentParser * commentParser, 
   enum State      fromState, 
   enum State      toState,
   enum Signal     signal,
   int             commentCounterDifference
)
{
   int currentCommentCounter = commentParser->getCommentCounter();

   // Make sure we are in the correct starting state
   UnitTest_testEqual(test_name, commentParser->getCurrentState(), fromState);

   commentParser->dispatch(signal);

   // Make sure we are in the correct ending state
   UnitTest_testEqual(test_name, commentParser->getCurrentState(), toState);

   UnitTest_testEqual(
      test_name, 
      commentParser->getCommentCounter(), 
      currentCommentCounter + commentCounterDifference
   );
}

// Helpful macro to make the string comment easier to build
#define TEST_STATE_TRANSITION(a, b, c, d) \
   UnitTestCommentParser_TransitionFromStateToState( \
      "Transition from " #a " to " #b " with " #c, &commentParser, a, b, c, d \
   )

int main(int argc, char **argv)
{
   CommentParser commentParser;

   // Initialize the tests count
   failed_tests = 0;
   passed_tests = 0;

   // Add each test here
   UnitTestCommentParser_initialized(&commentParser);

   TEST_STATE_TRANSITION(CODE,          CODE,          CHAR_SIG,    0);
   TEST_STATE_TRANSITION(CODE,          CODE,          STAR_SIG,    0);
   TEST_STATE_TRANSITION(CODE,          CODE,          NEWLINE_SIG, 0);
   TEST_STATE_TRANSITION(CODE,          SLASH,         SLASH_SIG,   0);   // All CODE transitions tested
   TEST_STATE_TRANSITION(SLASH,         CODE,          CHAR_SIG,    0);   // <-- Return to code state
   TEST_STATE_TRANSITION(CODE,          SLASH,         SLASH_SIG,   0);   
   TEST_STATE_TRANSITION(SLASH,         CODE,          NEWLINE_SIG, 0);
   TEST_STATE_TRANSITION(CODE,          SLASH,         SLASH_SIG,   0);   
   TEST_STATE_TRANSITION(SLASH,         QUICK_COMMENT, SLASH_SIG,   2);
   TEST_STATE_TRANSITION(QUICK_COMMENT, QUICK_COMMENT, CHAR_SIG,    1);
   TEST_STATE_TRANSITION(QUICK_COMMENT, QUICK_COMMENT, STAR_SIG,    1);
   TEST_STATE_TRANSITION(QUICK_COMMENT, QUICK_COMMENT, SLASH_SIG,   1);   // All QUICK_COMMENT transitions tested
   TEST_STATE_TRANSITION(QUICK_COMMENT, CODE,          NEWLINE_SIG, 1);   
   TEST_STATE_TRANSITION(CODE,          SLASH,         SLASH_SIG,   0);   
   TEST_STATE_TRANSITION(SLASH,         COMMENT,       STAR_SIG,    2);   // All SLASH transitions tested
   TEST_STATE_TRANSITION(COMMENT,       COMMENT,       CHAR_SIG,    1);
   TEST_STATE_TRANSITION(COMMENT,       COMMENT,       NEWLINE_SIG, 1);
   TEST_STATE_TRANSITION(COMMENT,       COMMENT,       SLASH_SIG,   1);
   TEST_STATE_TRANSITION(COMMENT,       STAR,          STAR_SIG,    0);   // All COMMENT transitions tested
   TEST_STATE_TRANSITION(STAR,          STAR,          STAR_SIG,    1);
   TEST_STATE_TRANSITION(STAR,          COMMENT,       CHAR_SIG,    2);
   TEST_STATE_TRANSITION(COMMENT,       STAR,          STAR_SIG,    0);
   TEST_STATE_TRANSITION(STAR,          COMMENT,       NEWLINE_SIG, 2);
   TEST_STATE_TRANSITION(COMMENT,       STAR,          STAR_SIG,    0);
   TEST_STATE_TRANSITION(STAR,          CODE,          SLASH_SIG,   2);   // ALL STAR transitions tested

   // Display the resuts of the testing
   printf(
      "Unit Tests total %d, passed %d, failed %d\n", 
      passed_tests + failed_tests, passed_tests, failed_tests
   );
}

