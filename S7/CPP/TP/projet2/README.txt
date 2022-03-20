DOUBRE Maxime - M1 SIAME - Compte Rendu Phase 2 TP CPP


Pour compiler le programme :
	- "make" à partir du dossier build
	- "./calc2" pour lancer le programme
	

Dans cette phase 2 nous devions implémenter des fonctions hors avec la phase 1 de mon code il y avait trop de cas dans lesquels le programme ne marchait pas.
Tout cela parce que dans ma phase 1 je faisais l'analyse des expressions avant de tokeniser donc tant que je n'avais que des valeurs et des chaines de caractères ca fonctionnait mais dès qu'on rajoute des fonctions avec des arguments cela ne marche plus toujours.
J'aurai été obligé d'appeler d'abord les fonctions avec leur argument avant de tokeniser le résultat seulement, ce qui est plus un contournement de problème qu'une résolution.

J'ai donc totalement changé mon implémentation de la phase 1 afin que je passe en argument l'expression à ma classe Tokenstring qui met toute l'expression en token.
Avec cette implémentation je suis à même de tokeniser les fonctions ainsi que leurs arguments.
Ceci est vérifiable en décommantant la ligne 'tok.print()' dans le fichier 'program.cpp'.

De plus dans la phase 1 je n'aurai pas été capable de gérer les cas ou une fonction donne un résultat négatif.
Dans cette phase 2 la gestion des résultats négatifs de fonctions est présente et fonctionne.
Pour le faire j'ai dans mes objets 'Token' ajouté un Type 'typeSigne' dans lequel on trouve soit 'pos' soit 'neg' selon si la valeur est positive ou négative.
Je me sers de ce type dans l'évaluation pour être sûr d'obtenir la bonne valeur.

Concernant les fonctions j'ai un problème dans la string qui est dans mon Token car je n'arrive pas à lui assigner de nouvelle valeur.
Du coup je n'ai pas pu me servir de la str dans le Token pour savoir quelle fonction on doit appeler.
J'ai donc dans l'énumération de la classe 'Token' ajouté un type pour chaque fonction.
A causse de cela pour appeler les fonctions je dois faire des 'if 'else if', etc...pour obtenir le bon appel de fonction.
Ce n'est pas très optimisé et je devrais avant le rendu de la phase 3 me pencher sur cette str qui ne veut pas fonctinoner afin de réduire au maximum mon code pour ces appels de fonctions sans avoir besoin d'un type par fonction.

Concernant l'appel aux fonctions je les fais au moment de faire la liste RPN.
J'ai fais ce choix afin de ne pas trop modifier mon algorithme de RPN.
J'obtiens donc à la place des Token fonction et de ceux des '(', ')' et des arguments un seul Token dans lequel j'ai le résultat de la fonction avec ses arguments.

Pour l'évaluation rien n'a changé hormis l'utilisation des Type de signe des objets Token.

Comme dit précédemment il y a encore la str dans les Token à améliorer.
Il y a de plus la gestion des fonctions à l'intérieur des fonctions à gérer, ce qui n'est pas le cas dans ce code.
J'ai cependant des idées à mettre en oeuvre afin de peut être pouvoir gérer les fonctions imbriqués.
Je pense quand je trouve un token fonction l'envoyer lui ainsi que ses arguments, donc une suite de tokens '(', ..., ')', dans une fonction récursive qui calculera le résultat de la fonction avec ses arguments.
Si toute fois il y a dans les arguments une fonction alors je rappelerai cette même fonction sur cette fonction avec ses arguments aussi, etc.
Cette fonction devrait je pense renvoyer un token simple avec le résultat de la fonction et de ses arguments.
La récusrsivité permettrait je pense de le gérer parfaitement et de ne pas avoir de limitation du nombre d'imbriquement de fonctions.

De plus je pense que dans la troisième phase je devrais réimplémenter la classe Token afin de faire de l'héritage car je ne suis pas sûr d'avoir le polymorphisme avec l'énumération.

Enfin ceratines fonctions ne sont pas primordiales et sont même inutils pour certaines qui je pense font doublons.
Par exemple 'ParseNorm()' qui je pense n'est pas util car les expressions sans parathèses doivent être possiblement gérées par le 'ParsePar()'
J'aurai donc un gros travail d'opitmisation à faire pour la phase 3, et donc le rendu final.

Ces quatres points négatifs seront je l'espère et j'y compte bien, corrigés au rendu de la phase 3.


Pour tester cette deuxième phase j'ai effectué un gros test comprenant une suite des 20 expressions suivantes avec leur résultats tous bons :

3+2*4																		==> 11
17-24/4*3+2																	==>	1
4*5;																		==>	
(17-((24/4)*3))+2															==>	1
(4*2+3*6)																	==>	26
(4*2+3*6)/13																==>	2
8*9-1																		==>	71
pi=3.14;																	==>	
circonference=2*pi;															==>	
(pi+circonference)*3														==> 28.26
cos(5)+cos(3)																==>	-0.70633
sin(3)																		==>	0.14112
tan(5)																		==>	-3.38052
sqrt(8)																		==>	2.82843
pow(2,3)																	==>	8
hypot(1,1)																	==>	1.41421
log(3)																		==>	1.09861
exp(0)																		==>	1
polynome(2,1,1,1,2)															==>	7
(17-((24/4)*3))+2+2*polynome(2,1,1,1,2)+pi-cos(3)*circonference				==>	24.3572
$

																				----- MEMORY -----

																				circonference = 6.28
																				pi = 3.14

																				------------------

	
DOUBRE Maxime
M1 SIAME						
