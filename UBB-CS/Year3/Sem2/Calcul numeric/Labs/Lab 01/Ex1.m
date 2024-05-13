#exercise 1:
#p(x)=1x^5 -5x^4 -16x^3 +16x^2 -17x +21

#b)
p = [1,-5,-16,16,-17,21];
polyval(p,-2.5)

#a)[-4,7.2]
x=-4:0.1:7.2;
px=polyval(p,x);
plot(x,px);

#c)
roots(p)

