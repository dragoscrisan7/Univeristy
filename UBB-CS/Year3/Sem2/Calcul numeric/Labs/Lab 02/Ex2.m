#2
#a)
syms x
f = sin(x)
T3 = taylor(f,x,0,'Order',4)
T5 = taylor(f,x,0,'Order',6)
ezplot(f,[-pi,pi])
hold on
ezplot(T3,[-pi,pi])
ezplot(T5,[-pi,pi])

#b)
vpa(sin(pi/5),6);#=0.5877
for k = 2:20
   T = taylor(f,x,0,'Order',k);
   k
   vpa(subs(T,x,-pi/3),6)#change -pi/3 with pi/5 for other exercise
end
