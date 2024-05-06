#f(x) = (x+1) / 3x^2 + 2x + 1
f = @(x) (x+1) ./ (3*x.^2 + 2*x + 1);
num_nodes = 7;
xi = linspace(-2, 4, num_nodes);
fi = f(xi);

figure;
plot(xi, fi, 'o', 'DisplayName', 'Nodes');
hold on;

xx = linspace(-2, 4, 1000);
ff = f(xx);

plot(xx, ff, 'DisplayName', 'f(x)');

lagrange_interp = lagrange_int(xi, fi, xx);

plot(xx, lagrange_interp, 'DisplayName', 'Lagrange Interpolation');

xlabel('x');
ylabel('f(x)');
title('Interpolation using Lagrange Interpolation');
legend;
