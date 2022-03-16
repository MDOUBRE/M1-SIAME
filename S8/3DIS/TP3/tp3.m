pkg load image

% Lecture et affichage de l'image
close all
clear all


# partie 1

img = imread('D:\Toulouse\UT3\M1\S8\3DIS\TP3\chat.jpg');
figure();
image(img);
title('Image Lena origine');
colormap(gray(256));

#figure();
F = fft2(img);
F2=fft2(img);
#imagesc(abs(F),[]);
#title('FFT'); 


# partie 2

# on enlève basses frequences
[Nlig, Ncol]=size(F);
n=80;
F(1:n/2,1:Ncol)=zeros(n/2,Ncol);
F(Nlig-n/2+1:Nlig,1:Ncol)=zeros(n/2,Ncol);

F(1:Nlig,1:n/2)=zeros(Nlig,n/2);
F(1:Nlig,Ncol-n/2+1:Ncol)=zeros(Nlig,n/2);

Fhautefreq=ifft2(F);
Fhautefreq=abs(Fhautefreq);
figure();
imagesc(Fhautefreq);
title('spectre inversé, on voit les hautes fréquences (contours)'); 

figure();
logabsLena=log(abs(F));
imagesc(logabsLena);
title('log - FFT (ave basses fréquences en moins)'); 

# on enleve les hautes frequencence
[Nlig2, Ncol2]=size(F2);
#n2=280;
n2=280;
F2(Nlig2/2-n2/2+1:Nlig2/2+n2/2,Ncol2/2-n2/2+1:Ncol2/2+n2/2)=zeros(n2,n2);

Fbassefreq=ifft2(F2);
Fbassefreq=abs(Fbassefreq);
figure();
imagesc(Fbassefreq);
title('spectre inversé, on voit les basses fréquences'); 

figure();
logabsLena2=log(abs(F2));
imagesc(logabsLena2);
title('log - FFT (ave hautes fréquences en moins)'); 


# partie 3

img2 = imread('D:\Toulouse\UT3\M1\S8\3DIS\TP3\img_b.jpg');
figure();
image(img2);
title('Image Lena poivre et sel');
colormap(gray(256));

F3=fft2(img2);
#
[Nlig3, Ncol3]=size(F3);
n3=450;
F3(Nlig3/2-n3/2+1:Nlig3/2+n3/2,Ncol3/2-n3/2+1:Ncol3/2+n3/2)=zeros(n3,n3);
#
Fpoivreetsel=ifft2(F3);
Fpoivreetsel=abs(Fpoivreetsel);
figure();
imagesc(Fpoivreetsel);
title('spectre inversé, on voit les basses fréquences sans le bruit'); 
colormap(gray(256));
#
figure();
imagesc(medfilt2(img2));
title('utilisation de medfilt2'); 
colormap(gray(256));

figure();
logabsLena3=log(abs(F3));
imagesc(logabsLena3);
title('log - FFT (avec bruit en moins donc hautes fréquences en moins)'); 


