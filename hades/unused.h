#pragma once
#ifndef __HADES_UNUSED_H__
#define __HADES_UNUSED_H__

/* ---------- definitions */

#ifndef unused
#ifdef MATCHING
#define unused(expression)
#else
#define unused(expression) (void)(expression)
#endif
#endif // unused

#endif // __HADES_UNUSED_H__
