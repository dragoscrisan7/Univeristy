f = @(x) 1./(2+sin(x));
romberg(f,0,pi/2,10^(-6),50)
vpa(pi*sqrt(3)/9,6)
