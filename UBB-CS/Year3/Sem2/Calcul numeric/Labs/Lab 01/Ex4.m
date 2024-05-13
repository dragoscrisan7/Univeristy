#exercise 4:
#f:[-2,2]x[0.5,4.5]->R
#f(x,y)=sin(e^x)cos(log y)

[x,y]=meshgrid(linspace(-2,2),linspace(0.5,4.5));
f=sin(exp(x)).*cos(log(y));
mesh(x,y,f)
plot3(x,y,f)
