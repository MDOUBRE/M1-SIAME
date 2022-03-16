close 'all'


P0=[100,100];
P1=[50,150];
T0=[-100,500];
T1=[-500,100];


[X,Y]=hermite(P0,P1,T0,T1);
figure();
plot(X,Y);

L = [ 2 1 4 4 5 6 6 9 8 ;
     3 2 1 7 9 7 1 2 3];
     
    
[X,Y]=bezier(L,0.01);    
figure();
plot(X,Y);
title("coucou");



A = [ 2 1 4 4 5 6 6 9 8 ; 
      3 2 1 7 9 7 1 2 3 ; 
      2 1 9 8 0 0 0 0 0 ; 
      5 4 5 4 0 0 0 0 0]; 
      

# bezier2 représente la superposition de deux lettres
figure();
bezier2(A,0.01);



%O = [ 5 6 9 5 1 4 5; 
%      1 1 5 9 5 1 1]

M=    [ 0 0 0  5  5  5; 
        0 4 5  5  4  2;
        5 5 5 10 10 10; 
        2 4 5  5  4  0];

# on fait les lettres en mettant des points à peu près
# les points doivent sur un graphe représenté à peu près la lettre
# quand on les relie        
M2=    [ 0 1 5; 
        0 5 2;
        5 9 10;
        2 5 0];
        
P = [ 4.2 4 4.5 4.9 5 ; 
      1.3 0 0 1 3 ;
      4 4.5 5 5.5 6
      1.5 2.9 4 2.9 1.5]
figure();
bezier2(P,0.001);

figure();
bezier2(M2,0.001);

figure();

huit=[ 1 0 2 1 0  2 1; 
       1 2 2 1 0  0 1];


bezier2(huit,0.001);
# plus p est petit plus la courbe est arrondi
# si 0.2 alors la forme est plus carré