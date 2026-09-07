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
