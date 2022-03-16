clear all 
close all

pkg load image
img=imread('D:\Toulouse\UT3\M1\S8\3DIS\TP1\2CV.jpg');
figure
image(img);

img(1:10,1,1:3)

tmp = img(1,1,1:3);

n=4;
szdim = size(img)
nb = 1:n;
vect = [ones(1,n),zeros(1,7-n)];
vect = int2str(vect);
vect = bin2dec(vect);
szdim(1);

quantif=bitand(img(:,:,1:3),vect);
figure
image(quantif);
imwrite(M,CVquantif);
img(1:10,1,1:3)
quantif(1:10,1,1:3)



