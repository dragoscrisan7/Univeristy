xi=[0,1/3,1/2,1];
fi=cos(pi*xi);
d=div_diff(xi,fi);
xx=linspace(0,1,100);
plot(xx,cos(pi*xx),xx,lab7(d,xi,xx))
cos(pi/5)
lab7(d,xi,1/5)
xi=[1000,1010,1020,1030,1040,1050];
fi=log10(xi);
d=div_diff(xi,fi);
logex=lab7(d,xi,[1001,1002,1003,1004,1005,1006,1007,1008,1009])
log10([1001,1002,1003,1004,1005,1006,1007,1008,1009])


x_nodes=linspace(-4,4,9);
y_nodes=2.^x_nodes;

x_value = log2(sqrt(2));
approx_sqrt = lab7ex2(y_nodes,x_nodes,x_value)

sqrt(2)
