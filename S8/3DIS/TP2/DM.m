pkg load image
pkg load signal

clear all
close all

filename='arpege.ogg';
Fs=16000;
Ts=1/Fs;
t=[0:Ts:1];
t2=[0:Ts:0.1];

F_silence=0;
silence=0*t2;

F_C3=263; %DO3
C3=sin(2*pi*F_C3*t);

F_E=330; %MI3
E=sin(2*pi*F_E*t);

F_G=392; %SOL3
G=sin(2*pi*F_G*t);

F_A=440; %LA3
A=sin(2*pi*F_A*t);

F_B=494; %SI3
B=sin(2*pi*F_B*t);

F_C4=523; %DO4
C4=sin(2*pi*F_C4*t);

F_D=587; %RE4
D=sin(2*pi*F_D*t);



arpege=[G A B G A silence A B C4 silence C4 B silence B G A B G A silence A B C4 D G G];
audiowrite(filename, arpege, Fs);
#sound(arpege,Fs);


spectre1=[];
for i=1:100:(length(arpege)-1024)
  extrait=arpege(i:(i+1023));
  #a1=abs(fft(extrait));
  a1=abs(fft(extrait.*(hamming(length(extrait)))'));
  a1=a1((length(a1)/2):end);
  
  spectre1=[spectre1 , a1];
end
spectre1=spectre1';

figure()
ylabel('Frequency,Hz(1/sec)');
specgram(spectre1,1024,Fs,hamming(1024));
