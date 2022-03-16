pkg load image
pkg load signal


clear all
close all

Fs=8000;
Ts=1/Fs;
t=[0:Ts:1];
t2=[0:Ts:0.1];

F_silence=0;
silence=0*t2;

F_C=262; %DO3
C=sin(2*pi*F_C*t);
C=0.8*C;

F_E=330; %MI3
E=sin(2*pi*F_E*t);
E=0.8*E;

F_G=392; %SOL3
G=sin(2*pi*F_G*t);
G=0.8*G;

F_C2=523; %DO4
C2=sin(2*pi*F_C2*t);
C2=0.8*C2;

arpege=[silence C silence E silence G silence C2 silence];
%sound(arpege,Fs);

figure();
plot(arpege);
title("arpege 1");

% Génération du bruit
N=size(arpege)(2);
bruit = (rand(1,length(arpege))*0.4)-0.2;
arpege2 = arpege + bruit;

%sound(arpege2,Fs);
figure()
plot(arpege2);
title("arpege 2");

%partie2

% bout signal (1024) -> calcul spectre puis mettre dans colonne du spectro
% pareil pour autre interval de données pour 2eme colonne, etc
% fft renvoie des nombres complexes
% calculer valeur absolue (abs())
% fenetre de hamming -> mult par fenetre de hamming pour améliorer la qualité du spectro

spectre1=[];
for i=1:100:(length(arpege)-1024)
  extrait=arpege(i:(i+1023));
  a1=abs(fft(extrait));
  #a1=abs(fft(extrait.*(hamming(length(extrait)))'));
  a1=a1((length(a1)/2):end);
  
  spectre1=[spectre1 , a1];
end

#spectre2=[];
#for i=1:100:(length(arpege2)-1024)
#  extrait2=arpege2(i:(i+1023));
#  a2=abs(fft(extrait2.*(hamming(length(extrait2)))'));
#  a2=a2((length(a2)/2):end);
#  
#  spectre2=[spectre2 ; a2];
#end
 
spectre1=spectre1';
#spectre2=spectre2';

figure()
specgram(spectre1,1024,Fs,hamming(1024));

#figure()
#s2=specgram(spectre2);
#plot(s2);
#title("spectre 2");


%partie3