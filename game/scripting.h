#pragma once

#define MAX_SCRIPT_VARS 16
#define MAX_SCRIPT_SIZE	255

struct GAME_SCRIPT_THREAD
{
	uint8_t Pad1[20];			// +00
	uintptr_t dwScriptIP;		// +20
	uint8_t Pad2[36];			// +24
	uint32_t dwLocalVar[32];	// +60
	uint32_t dwTimers[2];		// +188
	uint8_t Pad3[33];			// +196
	uint8_t condResult;			// +229
	uint8_t Pad4[10];			// +230
	uint16_t logicalOp;			// +240
	uint8_t notFlag;			// +242
	uint8_t Pad5[13];			// +243
	// STRUCT SIZE = 256
};

struct SCRIPT_COMMAND
{
	uint16_t OpCode;
	char Params[MAX_SCRIPT_VARS];
};

int ScriptCommand(const SCRIPT_COMMAND* pScriptCommand, ...);

const SCRIPT_COMMAND create_player						= { 0x0053, "vfffv" }; 	// 0, x, y, z, $PLAYER_CHAR

const SCRIPT_COMMAND create_actor_from_player			= { 0x01F5, "vv" };		// PLAYER_CHAR, PLAYER_ACTOR

const SCRIPT_COMMAND set_camera_behind_player			= { 0x0373, "" };

const SCRIPT_COMMAND restore_camera_jumpcut				= { 0x02EB, "" };

const SCRIPT_COMMAND request_model						= { 0x0247, "i" };		// (CAR_*|BIKE_*|BOAT_*|WEAPON_*|OBJECT_*)

const SCRIPT_COMMAND load_requested_models				= { 0x038B, "" };

const SCRIPT_COMMAND is_model_available					= { 0x0248, "i" };		// #MODEL

const SCRIPT_COMMAND set_actor_weapon_droppable 		= { 0x087e, "ii" };

const SCRIPT_COMMAND set_actor_immunities				= { 0x02ab, "iiiiii" };

const SCRIPT_COMMAND set_actor_can_be_decapitated		= { 0x0446, "ii" };

const SCRIPT_COMMAND destroy_object_with_fade			= { 0x09A2, "i" };

const SCRIPT_COMMAND disassociate_object				= { 0x0682, "ifffi" };

const SCRIPT_COMMAND remove_actor_from_car_and_put_at	= { 0x0362, "ifff" };

const SCRIPT_COMMAND set_camera_position				= { 0x015F, "ffffff" };

const SCRIPT_COMMAND point_camera						= { 0x0160, "fffi" };

const SCRIPT_COMMAND put_train_at						= { 0x07c7, "ifff" };

const SCRIPT_COMMAND set_current_time					= { 0x00C0, "ii" };		// Hours, Minutes

const SCRIPT_COMMAND toggle_player_controllable 		= { 0x01B4, "ii" };

const SCRIPT_COMMAND lock_actor							= { 0x04d7, "ii" };

const SCRIPT_COMMAND play_sound							= { 0x018c, "fffi" };

const SCRIPT_COMMAND enable_train_traffic				= { 0x06d7, "i" };

const SCRIPT_COMMAND refresh_streaming_at				= { 0x04E4, "ff" };

const SCRIPT_COMMAND restart_if_wasted_at				= { 0x016C, "ffffi" };

const SCRIPT_COMMAND set_actor_z_angle					= { 0x0173, "if" };

const SCRIPT_COMMAND enable_zone_names					= { 0x09BA, "i" };

const SCRIPT_COMMAND link_actor_to_interior				= { 0x0860, "ii" };

const SCRIPT_COMMAND select_interior					= { 0x04BB, "i" };

const SCRIPT_COMMAND restore_camera_to_user				= { 0x0925, "" };

const SCRIPT_COMMAND lock_camera_position				= { 0x0930, "i" };

const SCRIPT_COMMAND get_active_interior				= { 0x077e, "v" };

const SCRIPT_COMMAND request_animation					= { 0x04ED, "s" };

const SCRIPT_COMMAND is_animation_loaded				= { 0x04EE, "s" };

const SCRIPT_COMMAND text_clear_all						= { 0x00be, "" };

const SCRIPT_COMMAND set_actor_money					= { 0x03fe, "ii" };

const SCRIPT_COMMAND disable_marker						= { 0x0164, "i" };

const SCRIPT_COMMAND create_arrow_above_actor			= { 0x0187, "iv" };

const SCRIPT_COMMAND set_marker_color					= { 0x0165, "ii" };

const SCRIPT_COMMAND show_on_radar2						= { 0x018b, "ii" };

const SCRIPT_COMMAND set_fighting_style					= { 0x07fe, "iii" };

const SCRIPT_COMMAND apply_animation					= { 0x0812, "issfiiiii" };

const SCRIPT_COMMAND give_weapon_to_player				= { 0x01B1, "iii" };	// playerchar, weapon, ammo

const SCRIPT_COMMAND give_weapon_to_char				= { 0x01B2, "iii" };	// playerchar, weapon, ammo

const SCRIPT_COMMAND set_current_char_weapon			= { 0x01B8, "ii" };	// weapon, ammo

const SCRIPT_COMMAND set_current_player_weapon			= { 0x01B9, "ii" };	// weapon, ammo

const SCRIPT_COMMAND set_render_player_weapon			= { 0x0A38, "" };

const SCRIPT_COMMAND remove_all_char_weapons			= { 0x048F, "i" };

const SCRIPT_COMMAND get_weapontype_slot				= { 0x0782, "i" };

const SCRIPT_COMMAND get_current_char_weapon			= { 0x0470, "i" };

const SCRIPT_COMMAND get_current_player_weapon			= { 0x046F, "i" };

const SCRIPT_COMMAND get_line_of_sight					= { 0x06BD, "ffffffiiiii" }; // x1, y1, z1, x2, y2, z2, solid, vehicle, actor, obj, fx

const SCRIPT_COMMAND create_explosion_with_radius		= { 0x0948, "fffii" };

const SCRIPT_COMMAND get_ground_z						= { 0x02ce, "fffv" };	// x, y, z, var_ground_z

const SCRIPT_COMMAND create_radar_marker_icon			= { 0x0570, "fffiv" };

const SCRIPT_COMMAND create_icon_marker_sphere			= { 0x02A7, "fffiv" };

const SCRIPT_COMMAND create_radar_marker_without_sphere	= { 0x04CE, "fffiv" };

const SCRIPT_COMMAND show_on_radar						= { 0x0168, "ii" };

const SCRIPT_COMMAND create_marker_icon 				= { 0x02A8, "fffiv" };

const SCRIPT_COMMAND is_actor_near_point_3d				= { 0x00FE, "iffffffi" };

const SCRIPT_COMMAND create_racing_checkpoint			= { 0x06d5,	"ifffffffv"};

const SCRIPT_COMMAND destroy_racing_checkpoint			= { 0x06d6,	"i" };

const SCRIPT_COMMAND camera_on_actor					= { 0x0159, "iii" };

const SCRIPT_COMMAND camera_on_vehicle					= { 0x0158, "iii" };

const SCRIPT_COMMAND create_car							= { 0x00A5, "ifffv" };

const SCRIPT_COMMAND set_car_z_angle					= { 0x0175, "if" };

const SCRIPT_COMMAND car_gas_tank_explosion				= { 0x09C4, "ii" };

const SCRIPT_COMMAND set_car_hydraulics					= { 0x07FF,	"ii" };

const SCRIPT_COMMAND toggle_car_tires_vulnerable		= { 0x053f, "ii" };

const SCRIPT_COMMAND link_vehicle_to_interior			= { 0x0840, "ii" };

const SCRIPT_COMMAND destroy_car						= { 0x00A6, "i" };

const SCRIPT_COMMAND destroy_train						= { 0x07bd, "i" };

const SCRIPT_COMMAND put_actor_in_car					= { 0x036A, "ii" };

const SCRIPT_COMMAND put_actor_in_car2					= { 0x0430, "iii" };

const SCRIPT_COMMAND send_actor_to_car_passenger		= { 0x05CA, "iiii" };

const SCRIPT_COMMAND send_actor_to_car_driverseat		= { 0x05CB, "iii" };

const SCRIPT_COMMAND make_actor_leave_car				= { 0x05CD, "ii" };

const SCRIPT_COMMAND set_car_immunities					= { 0x02ac, "iiiiii" };

const SCRIPT_COMMAND add_to_player_money				= { 0x0109, "ii" };

const SCRIPT_COMMAND tie_marker_to_car					= { 0x0161, "iiiv" };

const SCRIPT_COMMAND has_car_sunk						= { 0x02bf, "i" };

const SCRIPT_COMMAND set_camera_pos_time_smooth			= { 0x0936, "ffffffii" };

const SCRIPT_COMMAND point_camera_transverse			= { 0x0920, "ffffffii" };

const SCRIPT_COMMAND create_object						= { 0x0107, "ifffv" };

const SCRIPT_COMMAND put_object_at						= { 0x01Bc, "ifff" };

const SCRIPT_COMMAND destroy_object						= { 0x0108, "i" };

const SCRIPT_COMMAND set_object_rotation				= { 0x0453, "ifff" };

const SCRIPT_COMMAND create_pickup						= { 0x0213, "iifffv" };

const SCRIPT_COMMAND destroy_pickup						= { 0x0215, "i" };

const SCRIPT_COMMAND is_pickup_picked_up				= { 0x0214, "i" };

const SCRIPT_COMMAND turn_off_car_engine				= { 0x02d4,	"i" };

const SCRIPT_COMMAND turn_on_car_engine					= { 0x0abe,	"i" };

const SCRIPT_COMMAND turn_car_engine 					= { 0x0918, "ii" };

const SCRIPT_COMMAND attach_object_to_char				= { 0x069b, "iiffffff" };

const SCRIPT_COMMAND set_object_visible					= { 0x0750, "ii" };

const SCRIPT_COMMAND set_player_drunk_visuals			= { 0x052C, "ii" }; // player, severity (0-255)

const SCRIPT_COMMAND get_player_drunkenness				= { 0x052D, "" };

const SCRIPT_COMMAND set_player_drunk_handling			= { 0x03FD, "ii" };

const SCRIPT_COMMAND shake_cam							= { 0x0003, "i" };

const SCRIPT_COMMAND set_char_proofs 					= { 0x02AB, "iiiiii" };

const SCRIPT_COMMAND set_char_collision					= { 0x0619, "ii" };

const SCRIPT_COMMAND set_car_coordinates				= { 0x00AB, "ifff" };

const SCRIPT_COMMAND get_target_blip_coordinates		= { 0x06AB, ""};

const SCRIPT_COMMAND request_collision					= { 0x04E4, "ff" };

const SCRIPT_COMMAND load_scene							= { 0x03CB, "fff"};

const SCRIPT_COMMAND get_char_weapon_in_slot			= { 0x04B8, "i" };

const SCRIPT_COMMAND is_char_holding_weapon				= { 0x02D8, "ii"};

const SCRIPT_COMMAND is_char_playing_anim				= { 0x0611, "is" };

const SCRIPT_COMMAND disembark_instantly_actor			= { 0x0792, "i"};

const SCRIPT_COMMAND set_car_health						= { 0x0224, "ii" };

const SCRIPT_COMMAND task_follow_path_nodes_to_coord	= { 0x05F5, "ii" }; // actor handle id, x, y, z, speed, time

const SCRIPT_COMMAND get_active_camera_coordinates		= { 0x068D, "" }; // x y z

const SCRIPT_COMMAND task_follow_point_route 			= { 0x05D8, "iii" }; // actor handle, speed 6, flag 0

const SCRIPT_COMMAND task_go_to_coord_any_means			= { 0x0603, "iiiiii" }; // actor handle, x, y, z, speed(7), vehicle (-1)

const SCRIPT_COMMAND set_swim_speed						= { 0x0A28, "f" };

const SCRIPT_COMMAND set_car_forward_speed				= { 0x04BA, "if" }; // vehicle handle, speed

const SCRIPT_COMMAND get_car_speed						= { 0x02E3, "i" }; // vehicle handle

const SCRIPT_COMMAND get_char_speed						= { 0x06AC, "i" }; // actor handle

const SCRIPT_COMMAND set_char_anim_speed				= { 0x0393, "isf" }; // actor handle, anim name, speed (1.0 normal)

const SCRIPT_COMMAND task_drive_point_route				= { 0x06BB, "iif" }; // actor handle, vehicle handle, speed(10.0)

const SCRIPT_COMMAND set_car_heading					= { 0x0175, "if" }; // veh handle, angle

const SCRIPT_COMMAND task_go_straight_to_coord			= { 0x05D3, "ifffii" };	// Actor handle, x, y, z, mode(walk 4, run 6, sprint 7), time

const SCRIPT_COMMAND is_car_engine_on					= { 0x0ABE, "i" }; // vehicle handle

const SCRIPT_COMMAND freeze_car_position				= { 0x0519, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND freeze_car_position_and_dont_load_collision = { 0x0574, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND switch_car_siren					= { 0x0397, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND is_car_siren_on					= { 0x0ABD, "i" }; // vehicle handle

const SCRIPT_COMMAND give_non_player_car_nitro			= { 0x09E9, "i" }; // vehicle handle

const SCRIPT_COMMAND set_darkness_effect				= { 0x0924, "ii" }; // state, level (0 normal / 255 max)

const SCRIPT_COMMAND get_ammo_in_char_weapon			= { 0x041A, "ii" }; // weapon id, actor handle [returns ammo(int)]

const SCRIPT_COMMAND set_char_accuracy					= { 0x02E2, "ii" }; // actor handle, accuracy (int) ex 75

const SCRIPT_COMMAND get_car_coordinates 				= { 0x00AA, "i" }; // vehicle handle (returns float car x,y,z)

const SCRIPT_COMMAND is_car_stuck_on_roof 				= { 0x018F, "i" }; // vehicle handle (is car down 2 seconds)

const SCRIPT_COMMAND set_car_heavy						= { 0x01EC, "i" }; // vehicle handle, state

const SCRIPT_COMMAND change_car_colour					= { 0x0229, "iii" }; // vehicle handle, color1, color2

const SCRIPT_COMMAND set_can_respray_car				= { 0x0294, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND is_car_in_water					= { 0x02BF, "i" }; // vehicle handle (returns bool)

const SCRIPT_COMMAND set_car_visible					= { 0x0338, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND set_car_status						= { 0x03A2, "ii" }; // vehicle handle, state (0 - normal / maybe using it for toggle engine?)

const SCRIPT_COMMAND set_car_strong						= { 0x03AB, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND apply_brakes_to_players_car		= { 0x0221, "ii" }; // player handle, state (maybe using for toggle car engine)

const SCRIPT_COMMAND car_goto_coordinates_accurate		= { 0x02C2, "iiii"}; // int: vehicle handle, float: x, y, z

const SCRIPT_COMMAND is_car_upsidedown					= { 0x01F4, "i" }; // vehicle handle

const SCRIPT_COMMAND is_car_in_air_proper				= { 0x01F3, "i" }; // vehicle handle

const SCRIPT_COMMAND explode_car						= { 0x020B, "i" }; // vehicle handle

const SCRIPT_COMMAND get_car_health						= { 0x0227, "i" }; // vehicle handle (returns float)

const SCRIPT_COMMAND get_char_coordinates				= { 0x00A0, "i" }; // actor handle (returns float(3))

const SCRIPT_COMMAND task_jetpack						= { 0x07A7, "i" }; // actor handle

const SCRIPT_COMMAND set_player_fast_reload				= { 0x0331, "ii" }; // actor handle, state

const SCRIPT_COMMAND set_car_temp_action				= { 0x0477, "iii"}; // vehicle handle, action id, time

// Actions
// 0 - Brake without lights
// 1 - Brake with lights
// 2 - Brake without lights
// 3 - Reverse
// 4 - Turn left wide
// 5 - Turn right wide
// 7 - Drive forward and turn left
// 8 - Drive forward and turn right
// 9 - Drive forward
// 10 - Turn left slightly
// 11 - Turn right slightly
// 13 - Reverse and turn left
// 14 - Reverse and turn right
// 19 - Turn left slightly, flash the rear lights
// 20 - Turn left slightly, switch rear lights on for 4 seconds
// 21 - Turn right slightly, switch rear lights for 4 seconds
// 22 - Drive back
// 23 - Drive forward very fast
// 24 - Switch lights on at animation time

const SCRIPT_COMMAND display_radar						= { 0x0581, "i" }; // state

const SCRIPT_COMMAND is_char_in_air						= { 0x0818, "i" }; // actor handle

const SCRIPT_COMMAND set_char_heading					= { 0x0173, "ii" }; // actor handle, rot

const SCRIPT_COMMAND get_char_heading					= { 0x0172, "i" }; // actor handle

const SCRIPT_COMMAND get_position_of_analogue_sticks	= { 0x0494, "i" }; // actor handle, return int 

// Returns the offset of the specified Left/Right, Up/Down, Look Left/Look Right and Look Up/Look Down keys.
// 
// Joystick ID is eqivalent to the player id, which can be 0 for player 1 and 1 for player 2 (as well as the relevant global varible).
// 
// Returned Values
// 
// 1. Movement. Left: 128 - Right: -128
// 2. Movement. Up: 128 - Down: -128
// 3. Special Ctrl. Left: -128 - Right: 128
// 4. Special Ctrl. Up: -128 - Down: 128

const SCRIPT_COMMAND set_car_engine_on					= { 0x0918, "ii"}; // vehicle handle, state

const SCRIPT_COMMAND swap_nearest_building_model		= { 0x03B6, "ffffii"}; // x,y,z,radius,model(from),model(to)

const SCRIPT_COMMAND add_vehicle_mod					= { 0x06E7, "ii" };

const SCRIPT_COMMAND set_visibility_of_closest_object_of_type = { 0x0363, "ffffii" }; // x,y,z,radius,model,state

const SCRIPT_COMMAND give_player_clothes				= { 0x0784, "iiii" }; // actor handle, texture, model, bodypart

const SCRIPT_COMMAND set_car_lights_on					= { 0x0919, "ii" }; // vehicle handle, state

const SCRIPT_COMMAND force_car_lights					= { 0x067F, "ii" }; // vehicle handle, state
 
const SCRIPT_COMMAND set_char_never_targetted			= { 0x0568, "ii" }; // actor handle, state

const SCRIPT_COMMAND add_ammo_to_char					= { 0x0114, "iii" }; // actor handle, weapon handle, ammo count

const SCRIPT_COMMAND set_char_ammo						= { 0x017B, "iii" }; // actor handle, weapon handle, ammo count