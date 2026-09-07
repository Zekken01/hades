#pragma once
#ifndef __HADES_REVERSE_ENGINEERING_H__
#define __HADES_REVERSE_ENGINEERING_H__

/* ---------- headers */

#include "hades/mangled_assert.h"
#include "hades/static_assert.h"
#include "hades/unused.h"

/* ---------- definitions */

// Linkage tags. A `_sub_<address>` declaration names the original routine inside
// mtndew.dll, so an unported stub still has the right shape and argument list even
// though only the compile-only build ever sees it.
#ifndef _extern
#define _extern extern "C"
#endif // _extern

#ifndef _static
#define _static extern "C"
#endif // _static

// Recovered from the PDB, where the original was emitted inline into its callers as
// well as standalone. Left empty: `/Od /Ob0` means nothing is actually inlined, and
// forcing `inline` here would change linkage.
#ifndef _inline
#define _inline
#endif // _inline

// Marks a function whose body is still the original call rather than a port.
#ifndef todo
#define todo(message)
#endif // todo

// Stands in for the result of a template stub. A non-template stub calls the
// thunk at its own address, but a template has one address per instantiation and
// its body cannot name a particular one - 159 separate functions answer to
// c_tag_block::try_get_element. Declared and never defined on purpose: the tree
// compiles, and a link says exactly which template is still a stub.
template<typename t_result>
t_result todo_result();

// Notes the generator emits about a function it could not fully describe.
#ifndef _message
#define _message(...)
#endif // _message

// The PDB records no line information for this function, i.e. the compiler
// synthesised it (implicit constructors, thunks, initialisers).
#ifndef compiler_generated
#define compiler_generated()
#endif // compiler_generated

// A `this`-adjusting thunk: the entry point shifts `this` by the given amount before
// dispatching to the real implementation.
#ifndef __shifted
#define __shifted(class_type, adjustment)
#endif // __shifted

// A declaration pdb-decompiler could not render - in practice the thread-local
// statics, whose storage the PDB describes but whose declaration it cannot
// reconstruct. Kept as a marker so the site is findable rather than silently lost.
#ifndef static_warning
#define static_warning(message)
#endif // static_warning

#endif // __HADES_REVERSE_ENGINEERING_H__
