/* ---------- headers */

#include "Blam/multithreading/synchronization/critical_section.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

extern void (*const critical_section_enter)(e_critical_section); // 0x11249FEC
extern void (*const critical_section_leave)(e_critical_section); // 0x11249FF0

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
void (*const critical_section_leave)(e_critical_section) = reinterpret_cast<decltype(critical_section_leave)>(0x52C4E0);
void (*const critical_section_enter)(e_critical_section) = reinterpret_cast<decltype(critical_section_enter)>(0x52C4A0);
