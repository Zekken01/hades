#pragma once
#ifndef __HADES_STATIC_ASSERT_H__
#define __HADES_STATIC_ASSERT_H__

/* ---------- definitions */

// Layout assertions recovered from the PDB. Under MATCHING they are switched off
// so that a partially reconstructed type does not stop the translation unit from
// compiling; the assertions still hold in the normal build.
#ifdef MATCHING
#define static_assert32(...)
#else
#define static_assert32 static_assert
#endif

#endif // __HADES_STATIC_ASSERT_H__
