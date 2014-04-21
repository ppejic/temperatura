clear all;
close all;

T=-30:1:400;
Ro = 100;
alpha = 3.90802e-03;
beta = -5.802e-07;
IDAC = 500e-06;
PGA = 64;
LSB = 7.63e-09;

R = Ro.*(1+alpha.*T+beta.*(T.^2));
Uin = R.*IDAC;
U = Uin./LSB;

format long;
Uout = round(Uin./LSB);
Uout = Uout';
bina = dec2bin(Uout);

%format long;
%U=round(U/(122e-09));

