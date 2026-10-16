/* ---------- headers */

#include "Blam/game/player_medals.hpp"
#include "hades/hades.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

extern char const *g_player_medal_names[58]; // 0x1135A618

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
char const *g_player_medal_names[58] = { "extermination", "perfection", "double_kill", "triple_kill", "overkill", "killtacular", "killtrocity", "killimanjaro", "killtastrophe", "killpocalypse", "killionaire", "killing_spree", "killing_frenzy", "running_riot", "rampage", "untouchable", "invincible", "sniper_spree", "sharpshooter", "shotgun_spree", "open_season", "splatter_spree", "vehicular_manslaughter", "sword_spree", "slice_n_dice", "juggernaut_spree", "unstoppable", "infection_spree", "mmm_brains", "zombie_killing_spree", "hells_janitor", "unknown1", "hail_to_the_king", "bulltrue", "splatter", "hijacker", "skyjacker", "from_the_grave", "killjoy", "laser_kill", "grenade_stick", "sniper_kill", "assassin", "beat_down", "incineration", "wheelman", "bomb_planted", "bomb_carrier_kill", "vip_kill", "juggernaut_kill", "oddball_kill", "flag_captured", "flag_carrier_kill", "flag_carrier_kill_player", "infection_survive", "unused_1", "unused_2", "unused_3" };
