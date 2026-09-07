/* ---------- headers */

#include "Blam/game/campaign/campaign_metagame.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/tag_files/tag_groups.hpp"

/* ---------- forward declarations */

struct s_campaign_metagame_runtime_globals;
struct s_tag_block_definition;
struct s_tag_enum_definition;
struct s_tag_enum_option;
struct s_tag_field_definition;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

extern bool (*game_is_campaign)(); // 0x113597D0
extern s_campaign_metagame_runtime_globals **g_campaign_metagame; // 0x124C2C18
extern long (*campaign_metagame_globals_initialize_for_new_map)(); // 0x113597C4
extern long *(*survival_mode_get_scoreboard)(); // 0x113597C8
extern long (*game_get_current_engine)(); // 0x113597CC
extern s_tag_block_definition *g_campaign_metagame_bucket_block; // 0x113597C0
extern s_tag_enum_option _campaign_metagame_bucket_flags_enum_options[1]; // 0x113597D4
extern s_tag_enum_definition campaign_metagame_bucket_flags_enum; // 0x113597DC
extern s_tag_enum_option _campaign_metagame_unit_type_enum_options[30]; // 0x113597E8
extern s_tag_enum_definition campaign_metagame_unit_type_enum; // 0x113598D8
extern s_tag_enum_option _campaign_metagame_unit_class_enum_options[8]; // 0x113598F0
extern s_tag_enum_definition campaign_metagame_unit_class_enum; // 0x113598E4
extern s_tag_field_definition _campaign_metagame_bucket_block_fields[7]; // 0x124C2C20
extern s_tag_block_definition campaign_metagame_bucket_block; // 0x11359930

/* ---------- private variables */

/* ---------- public code */

/* ---------- private code */
