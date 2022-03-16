# partie 1

clear all
close all

[signal,fs] = audioread('D:\Toulouse\UT3\M1\S8\3DIS\TP1\son1_qcm.wav');
info = audioinfo('D:\Toulouse\UT3\M1\S8\3DIS\TP1\diner.wav');
sound(signal,fs)

figure();
plot(signal);
title("signal");

nzero=nonzeros(signal);
nzero=nzero(1:10,1);
figure();
plot(nzero);
title("nzero");

croixrouge=(signal);
figure();
plot(signal,'xr',croixrouge);
title("superpos croix rouge");

#signInt=int32(signal)*2^15;
signInt=(signal)*(2^16)/2;
#signInt=int32(signInt);
signInt10=signInt(1:10,1);
figure();
plot(signInt10);
title(signInt10);


img=imread('D:\Toulouse\UT3\M1\S8\3DIS\TP1\photo.jpg');
figure();
image(img);

imgprem=img(1:10,1,1:3);
#figure();
#image(imgprem);


# partie 2

# quantification d'un signal audiodevinfo
signal2=signal;
q1=12;
q2=8;
q3=4;

quantif12=( floor(signal*2^(q1-1)) )/( 2^(q1-1) );
#sound(quantif12,fs)

quantif8=( floor(signal*2^(q2-1)) )/( 2^(q2-1) );
#sound(quantif8,fs)

quantif4=( floor(signal*2^(q3-1)) )/( 2^(q3-1) );
#sound(quantif4,fs)
# son très dégueulasse avec 4 bits...

# echantillonage

echant2=signal(1:2:length(signal));
#sound(echant2,fs)

echant4=signal(1:4:length(signal));
#sound(echant4,fs)

# quantification d'une image
img1=imread('D:\Toulouse\UT3\M1\S8\3DIS\TP1\photo.jpg');
imgmat=double(img1);

# quantif sur 7 bits
img2=2*floor(imgmat./2);
img2=uint8(img2);
figure();
image(img2);
title("img2");

# quantif sur 6 bits
img4=2*floor(imgmat./2^2);
img4=uint8(img4);
figure();
image(img4);
title("img4");

# quantif sur 5 bits
img8=2*floor(imgmat./2^3);
img8=uint8(img8);
figure();
image(img8);
title("img8");

# quantif sur 1 bits
img128=2*floor(imgmat./2^7);
img128=uint8(img128);
figure();
image(img128);
title("img128");