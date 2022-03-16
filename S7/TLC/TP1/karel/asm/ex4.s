@
@ Question 5.2
@
@ Ecrivez un programme qui fait un parcours vertical depuis
@ sa position courante jusqu’à ce qu’il trouve un beeper.
@ Il partira vers le nord puis, quand il trouvera un mur,
@ il tournera à gauche et avancera avant de repartir vers
@ le sud et ainsi de suite.
@
_start:
	seti r0,#1

loop:
	invoke 11,1,1				// on test s'il y a un beeper à la position courante
	goto_eq end,r0,r1
	
	invoke 6,1,1 				// on test s'il y a un mur
	goto_eq leftright,r0,r1

	invoke 1,0,0 				// on fait un move

	goto loop

leftright:
	invoke 7,1,1 				// on identifie la direction
	goto_eq left,r0,r1
	goto right

left:
	invoke 2,0,0
	invoke 1,0,0
	invoke 2,0,0
	goto loop

right:
	invoke 2,0,0
	invoke 2,0,0	
	invoke 2,0,0
	invoke 1,0,0
	invoke 2,0,0
	invoke 2,0,0
	invoke 2,0,0
	goto loop

end:	
	stop
