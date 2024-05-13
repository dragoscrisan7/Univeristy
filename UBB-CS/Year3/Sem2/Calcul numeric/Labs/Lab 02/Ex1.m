#1
#a) plot e^x and its taylor pol of degree 1,2,3,4 on [-3,3]
#pkg load symbolic
syms x
f = exp(x)
#taylor(f,x,x0=0,'Order',order+1)
T1f = taylor(f,x,0,'Order',2)
T2f = taylor(f,x,0,'Order',3)
T3f = taylor(f,x,0,'Order',4)
T4f = taylor(f,x,0,'Order',5)

#ezplot(f,[-3,3])
#hold on
#ezplot(T1f,[-3,3])
#ezplot(T2f,[-3,3])
#ezplot(T3f,[-3,3])
#ezplot(T4f,[-3,3])

#1
#b)approximate e with 6 correct decimals
exp(1);#=2.7183
vpa(exp(1),7);#=2718282
vpa(subs(T4f,x,1),7);#=2.708

for k = 6:20
    T = taylor(f,x,0,'Order',k);
    k
    vpa(subs(T,x,1),7)
end
