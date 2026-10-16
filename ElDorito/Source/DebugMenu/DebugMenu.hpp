#pragma once

// The debug menu: ManagedDonkey's port of the Halo 3 debug menu, driven by
// debug_menu_init.txt in the game directory. Insert (or Back+Start on a controller)
// opens and closes it; arrows/D-pad move, Enter/A selects, End/B goes back.

namespace DebugMenu
{
	// Registers the input handler that opens the menu. Called once from Patches::Debug::ApplyAll.
	void Initialize();

	// Draws the open menu. Called from render_debug_frame_render.
	void Render();
}
