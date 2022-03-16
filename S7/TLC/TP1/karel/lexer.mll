{
open Parser
}

let comment = '{' [^ '}']* '}'
let space = [' ' '\t' '\n']+
let intnumber = ['0' - '9']+

rule scan =
parse	"BEGINNING-OF-PROGRAM"		{ BEGIN_PROG }
|		"BEGINNING-OF-EXECUTION"	{ BEGIN_EXEC }
|		"END-OF-EXECUTION"			{ END_EXEC }
|		"END-OF-PROGRAM"			{ END_PROG }
|		"move"						{ MOVE }
|		"turnleft"					{ TURN_LEFT }
|		"turnoff"					{ TURN_OFF }
|		"BEGIN"						{ BEGIN }
|		"END"						{ END }
		
|		";"							{ SEMI }

|		"pickbeeper"				{ PICK_BEEPER }
|		"putbeeper"					{ PUT_BEEPER }
|		"next-to-a-beeper"			{ NEXT_TO_A_BEEPER }
|		space						{ scan lexbuf }
|		comment						{ scan lexbuf }
|		intnumber as i				{ INT (int_of_string i) }
|		_ as c						{ raise (Common.LexerError (Printf.sprintf "unknown character '%c'" c)) }

|		"front_is_clear"			{ FRONT_IS_CLEAR }
|		"front_is_blocked"			{ FRONT_IS_BLOCKED }
|		"left_is_clear"				{ LEFT_IS_CLEAR }
|		"left_is_blocked"			{ LEFT_IS_BLOCKED }
|		"right_is_clear"			{ RIGHT_IS_CLEAR }
|		"right_is_blocked"			{ RIGHT_IS_BLOCKED }
|		"next_to_a_beeper"			{ NEXT_TO_A_BEEPER }
|		"not_next_to_a_beeper"		{ NOT_NEXT_TO_A_BEEPER }
|		"facing_north"				{ FACING_NORTH }
|		"not_facing_north"			{ NOT_FACING_NORTH }
|		"facing_east"				{ FACING_EAST }
|		"not_facing_east"			{ NOT_FACING_EAST }
|		"facing_south"				{ FACING_SOUTH }
|		"not_facing_south"			{ NOT_FACING_SOUTH }
|		"facing_west"				{ FACING_WEST }
|		"not_facing_west"			{ NOT_FACING_WEST }
|		"any_beepers_in_beeper_bag"	{ ANY_BEEPERS_IN_BEEPER_BAG }
|		"no_beepers_in_beeper_bag"	{ NO_BEEPERS_IN_BEEPER_BAG }

