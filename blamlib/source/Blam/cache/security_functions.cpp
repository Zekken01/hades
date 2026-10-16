/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

extern bool (*const security_incremental_hash_begin)(void *, long, bool); // 0x1124B978
extern void (*const security_incremental_hash_update)(void *, long, void const *, unsigned long); // 0x1124B97C
extern void (*const security_incremental_hash_finish)(void *, long, void *); // 0x1124B980
extern bool (*const security_calculate_hash)(void *, long, bool, void *); // 0x1124B984
extern bool (*const security_rsa_compute_and_verify_signature)(void const *, void *); // 0x1124B988
extern void (*const security_get_working_memory)(long, void **, long *); // 0x1124B98C

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
bool (*const security_incremental_hash_begin)(void *, long, bool) = reinterpret_cast<decltype(security_incremental_hash_begin)>(0x508E50);
void (*const security_incremental_hash_update)(void *, long, void const *, unsigned long) = reinterpret_cast<decltype(security_incremental_hash_update)>(0x508EA0);
void (*const security_incremental_hash_finish)(void *, long, void *) = reinterpret_cast<decltype(security_incremental_hash_finish)>(0x508E80);
bool (*const security_calculate_hash)(void *, long, bool, void *) = reinterpret_cast<decltype(security_calculate_hash)>(0x508D30);
bool (*const security_rsa_compute_and_verify_signature)(void const *, void *) = reinterpret_cast<decltype(security_rsa_compute_and_verify_signature)>(0x508F80);
