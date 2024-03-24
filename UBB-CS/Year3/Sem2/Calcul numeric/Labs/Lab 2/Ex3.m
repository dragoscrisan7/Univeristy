#3
#a)
syms x
f = log(1+x)
#approximate log(2) degree 2 and 5
T2 = taylor(f,x,0,'Order',3)
T5 = taylor(f,x,0,'Order',6)

ezplot(f,[-0.9,1])
hold on
ezplot(T2,[-0.9,1])
ezplot(T5,[-0.9,1])

#c)
a = taylor(log(1-x),x,0,'Order',8)

#d)
b = taylor(log(1+x),x,0,'Order',8)
a-b

#e)
log(2);#=0.6931
#x=1/3;
for k=3:12
  c = taylor(log(1-x),x,0,'Order',k);
  d = taylor(log(1+x),x,0,'Order',k);
  c-d;
  k
  vpa(subs(c-d,x,1/3),6)
end
