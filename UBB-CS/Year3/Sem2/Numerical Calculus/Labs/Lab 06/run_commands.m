#run code

lagrange_int([1 2 3], [1 4 9], 5);

#1)
#a)
xi = linspace(-2, 4, 10);
fi = (xi + 1)./(3*xi.^2 + 2*xi + 1)

#b)
x = linspace(-2,4,500);
f=(x + 1)./(3*x.^2 + 2*x + 1);
L9f = lagrange_int(xi, fi, x);
plot(x,f,x,L9f,'g',xi,fi,'o')

#c)
plot(x,abs(f-L9f));
max(abs(f-L9f));

#2)
y = lagrange_b([1980:10:2020], [4451 5287 6090 6970 7821], [2005, 2015])
abs(y-[6474,7405])./abs([6474,7405])

#3)
xi = [100, 121, 144]
fi = sqrt(xi)

x = 118;
sqrt_118 = lagrange_int(xi, fi, x);

disp(['Approximated square root of 118: ', num2str(sqrt_118)]);
