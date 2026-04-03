//---------------------------------------------------------------------------
//comment out for build on trixie and higher
#define TDE_UP_TO_14_1_5

#ifdef TDE_UP_TO_14_1_5
  #define DQ_SIGNAL SIGNAL
  #define DQ_SLOT SLOT
#else
  #define DQ_SIGNAL TQ_SIGNAL
  #define DQ_SLOT TQ_SLOT
#endif
//---------------------------------------------------------------------------
