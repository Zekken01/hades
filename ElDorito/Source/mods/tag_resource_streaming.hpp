#ifndef __MODS_TAG_RESOURCE_STREAMING_HPP__
#define __MODS_TAG_RESOURCE_STREAMING_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/async/async.hpp"

/* ---------- forward declarations */

struct c_async_completion_flag;

/* ---------- constants */

enum e_tag_resource_stream_abort_reason
{
	_tag_resource_stream_abort_none = 0,
	_tag_resource_stream_abort_decompression_error,
	_tag_resource_stream_abort_file_read_error,
	_tag_resource_stream_abort_unknown,
};

/* ---------- definitions */

/* ---------- prototypes */

extern long tag_resource_stream_async(long resource_handle, void *buffer, long buffer_size, c_async_completion_flag *completed);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __MODS_TAG_RESOURCE_STREAMING_HPP__
