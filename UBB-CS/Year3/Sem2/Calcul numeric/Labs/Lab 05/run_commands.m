%ex1

%generate matrix
[A,b]=get_matrix(1000);

x0=zeros(1000,1);
maxnit=1000;
err=10^(-5);

[x,nit]=jacobi_it(A,b,x0,maxnit,err);
[x,nit]=gauss_it(A,b,x0,maxnit,err);


%ex2
%a x=A\b;
A=[10,7,8,7;7,5,6,5;8,6,10,9;7,5,9,10];
b=[32,23,33,31]';
x=A\b

%b
b2=[32.1,22.9,33.1,30.9]';
x2=A\b2;
norm(b-b2)/norm(b)

%c
A2=[10,7,8.1,7.2; 7.8,5.04,6,5; 8,5.98,9.89,9; 6.99,4.99,9,9.98];
x3=A2\b
norm(A-A2)/norm(A)

norm(x-x3)/norm(x)

cond(A)
cond(A2)
