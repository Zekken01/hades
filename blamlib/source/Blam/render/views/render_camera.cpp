/* ---------- headers */

#include "Blam/render/views/render_camera.hpp"
#include "hades/hades.h"

#include "Blam/math/integer_math_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <limits>
#include <type_traits>

/* ---------- forward declarations */

struct real_point2d;
struct real_point3d;
struct s_render_camera;
struct s_render_projection;
struct short_rectangle2d;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *out_point);  // hades: added for 0X10F1D8F0
bool render_camera_view_to_screen(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *view_point, real_point2d *screen_point);  // hades: added for 0X10F1D8F0

extern bool render_camera_view_to_screen(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *view_point, real_point2d *screen_point);
extern bool render_camera_world_to_window(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *world_point, real_point2d *screen_point);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

bool render_camera_view_to_screen(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *view_point, real_point2d *screen_point) // 0x10F1D640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_camera_view_to_screen@@YA_NPBUs_render_camera@@PBUs_render_projection@@PBUshort_rectangle2d@@PBUreal_point3d@@PAUreal_point2d@@@Z");
	// real_point2d *screen_point;
	// bool result;
		// float w;
		// float h;
		// float cx;
		// float cy;
		// float m;

	bool result = false;
	if (isfinite(view_point->z) && view_point->z < 0.0)
	{
		float w = (float)(window_display_bounds->x1 - window_display_bounds->x0);
		float h = (float)(window_display_bounds->y1 - window_display_bounds->y0);
		float m = -1.0f / view_point->z;
		float cx = view_point->x * projection->projection_matrix[0][0] * m + view_point->z * projection->projection_matrix[2][0];
		float cy = -m * (view_point->y * projection->projection_matrix[1][1]) + view_point->z * projection->projection_matrix[2][1];
		if (cx >= -1.0f && cx <= 1.0f && cy >= -1.0f && cy <= 1.0f)
			result = true;
		screen_point->x = (cx * 0.5f + 0.5f) * w + window_display_bounds->x0;
		screen_point->y = (cy * 0.5f + 0.5f) * h + window_display_bounds->y0;
	}
	else
	{
		screen_point->x = 0.0f;
		screen_point->y = 0.0f;
	}
	return result;
}

bool render_camera_world_to_window(s_render_camera const *camera, s_render_projection const *projection, short_rectangle2d const *window_display_bounds, real_point3d const *world_point, real_point2d *screen_point) // 0x10F1D8F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_camera_world_to_window@@YA_NPBUs_render_camera@@PBUs_render_projection@@PBUshort_rectangle2d@@PBUreal_point3d@@PAUreal_point2d@@@Z");
	// s_render_projection const *projection;
	// short_rectangle2d const *window_display_bounds;
	// real_point3d const *world_point;
	// real_point2d *screen_point;
	// real_point3d view_point;

	real_point3d view_point;

	matrix4x3_transform_point(&projection->world_to_view, world_point, &view_point);
	return render_camera_view_to_screen(camera, projection, window_display_bounds, &view_point, screen_point);
}

/* ---------- private code */
