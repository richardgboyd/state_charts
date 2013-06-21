#include "StateTableCommentCounter.h"

StateTable::Transition const CommentParser::myTable[MAX_STATE][MAX_SIG] = 
{
   // State CODE
   {
      {&StateTable::doNothing, CODE},     // CHAR_SIG
      {&StateTable::doNothing, SLASH},    // SLASH_SIG
      {&StateTable::doNothing, CODE},     // STAR_SIG
      {&StateTable::doNothing, CODE},     // NEWLINE_SIG
   },
   // State SLASH
   {
      {&StateTable::doNothing, CODE},                                            // CHAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_two), QUICK_COMMENT}, // SLASH_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_two), COMMENT},       // STAR_SIG
      {&StateTable::doNothing, CODE},                                            // NEWLINE_SIG
   },
   // State COMMENT
   {
      {static_cast<StateTable::Action>(&CommentParser::add_one), COMMENT}, // CHAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_one), COMMENT}, // SLASH_SIG
      {&StateTable::doNothing, STAR},                                      // STAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_one), COMMENT}, // NEWLINE_SIG
   },
   // State STAR
   {
      {static_cast<StateTable::Action>(&CommentParser::add_two), COMMENT}, // CHAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_two), CODE},    // SLASH_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_one), STAR},    // STAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_two), COMMENT}, // NEWLINE_SIG
   },
   // State QUICK_COMMENT
   {
      {static_cast<StateTable::Action>(&CommentParser::add_one), QUICK_COMMENT}, // CHAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_one), QUICK_COMMENT}, // SLASH_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_one), QUICK_COMMENT}, // STAR_SIG
      {static_cast<StateTable::Action>(&CommentParser::add_one), CODE},          // NEWLINE_SIG
   }
};

