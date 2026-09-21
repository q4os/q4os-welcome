//---------------------------------------------------------------------------
//TDE renamed SIGNAL/SLOT to TQ_SIGNAL/TQ_SLOT in 14.1.5 and dropped the old spelling, so which pair
//is right depends on the TDE this is compiled against - 14.1.1 on bookworm, 14.1.5+ on trixie and
//forky. ntqobjectdefs.h is where they are defined, so include it and let the compiler decide rather
//than keeping a #define that had to be commented out by hand for every build on trixie and higher.
#include <ntqobjectdefs.h>

#ifdef TQ_SLOT
  #define DQ_SIGNAL TQ_SIGNAL
  #define DQ_SLOT TQ_SLOT
#else
  #define DQ_SIGNAL SIGNAL
  #define DQ_SLOT SLOT
#endif
//---------------------------------------------------------------------------
