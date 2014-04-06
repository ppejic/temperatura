clear all;
close all;

T=-30:1:400;
Ro = 100;
alpha = 3.90802e-03;
beta = -5.802e-07;
IDAC = 250e-06;
PGA = 16;

R = Ro.*(1+alpha.*T+beta.*(T.^2));
Uin = R.*IDAC;
U = Uin.*PGA;
U = ceil(U*1000)/1000;  

format long;
U=round(U/(122e-09));
U = U';

save('podaci.c', 'U', '-ascii');