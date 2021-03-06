%{

open Quad
open Common
open Comp
open Karel


%}

%token BEGIN_PROG
%token BEGIN_EXEC
%token END_EXEC
%token END_PROG

%token MOVE
%token TURN_LEFT
%token TURN_OFF

%token SEMI
%token BEGIN
%token END

%token PICK_BEEPER
%token PUT_BEEPER
%token NEXT_TO_A_BEEPER

%token FRONT_IS_CLEAR
%token FRONT_IS_BLOCKED
%token LEFT_IS_CLEAR
%token LEFT_IS_BLOCKED
%token RIGHT_IS_CLEAR
%token RIGHT_IS_BLOCKED
%token NEXT_TO_A_BEEPER
%token NOT_NEXT_TO_A_BEEPER
%token FACING_NORTH
%token NOT_FACING_NORTH
%token FACING_EAST
%token NOT_FACING_EAST
%token FACING_SOUTH
%token NOT_FACING_SOUTH
%token FACING_WEST
%token NOT_FACING_WEST
%token ANY_BEEPERS_IN_BEEPER_BAG
%token NO_BEEPERS_IN_BEEPER_BAG

%token <int> INT

%type <unit> prog
%start prog

%%

prog:	BEGIN_PROG BEGIN_EXEC stmts_opt END_EXEC END_PROG
			{ () }
;



stmts_opt:	/* empty */		{ () }
|			stmts			{ () }
;

stmts:		stmt			{ () }
|			stmts SEMI stmt	{ () }
|			stmts SEMI		{ () }
;

stmt:		simple_stmt
				{ () }
;




simple_stmt: TURN_LEFT
				{ gen (INVOKE (turn_left, 0, 0)) }
|			TURN_OFF
				{ gen STOP  }
|			MOVE
				{ gen (INVOKE (move, 0, 0)) }
|			PICK_BEEPER
				{ print_string "PICK_BEEPER" }
|			PUT_BEEPER
				{ print_string "PUT_BEEPER" }
;

test: 		FRONT_IS_CLEAR
				{ print_string "FRONT_IS_CLEAR" }
|			FRONT_IS_BLOCKED
				{ print_string "FRONT_IS_BLOCKED" }
|			LEFT_IS_CLEAR
				{ print_string "LEFT_IS_CLEAR" }
|			LEFT_IS_BLOCKED
				{ print_string "LEFT_IS_BLOCKED" }
|			RIGHT_IS_CLEAR
				{ print_string "RIGHT_IS_CLEAR" }
|			RIGHT_IS_BLOCKED
				{ print_string "RIGHT_IS_BLOCKED" }
|			NEXT_TO_A_BEEPER
				{ print_string "NEXT_TO_A_BEEPER" }
|			NOT_NEXT_TO_A_BEEPER
				{ print_string "NOT_NEXT_TO_A_BEEPER" }
|			FACING_NORTH
				{ print_string "FACING_NORTH" }
|			NOT_FACING_NORTH
				{ print_string "NOT_FACING_NORTH" }
|			FACING_EAST
				{ print_string "FACING_EAST" }
|			NOT_FACING_EAST
				{ print_string "NOT_FACING_EAST" }
|			FACING_SOUTH
				{ print_string "FACING_SOUTH" }
|			NOT_FACING_SOUTH
				{ print_string "NOT_FACING_SOUTH" }
|			FACING_WEST
				{ print_string "FACING_WEST" }
|			NOT_FACING_WEST
				{ print_string "NOT_FACING_WEST" }
|			ANY_BEEPERS_IN_BEEPER_BAG
				{ print_string "ANY_BEEPERS_IN_BEEPER_BAG" }
|			NO_BEEPERS_IN_BEEPER_BAG
				{ print_string "NO_BEEPERS_IN_BEEPER_BAG" }
;






