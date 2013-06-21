/**
 * Signals Recognized by the Comment Parser Code
 */
enum Signal { 
   CHAR_SIG,
   SLASH_SIG,
   STAR_SIG,
   NEWLINE_SIG,

   MAX_SIG
};

/**
 * States supported by the Comment Parser Code
 */
enum State  { 
   CODE,
   SLASH,
   COMMENT,
   STAR,
   QUICK_COMMENT,

   MAX_STATE
};
