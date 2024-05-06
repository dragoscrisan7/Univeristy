f = @(x) (x+1) ./ (3*x.^2 + 2*x + 1);
num_nodes = 7;
xi = linspace(-2, 4, num_nodes);
fi = f(xi);

dx = xi(2) - xi(1);
dfi_dx = diff(fi) ./ dx;
dfi_dx = [dfi_dx, dfi_dx(end)];

figure;
plot(xi, fi, 'o', 'DisplayName', 'Nodes');
hold on;
xx = linspace(-2, 4, 1000);
ff = f(xx);
plot(xx, ff, 'DisplayName', 'f(x)');

combined_nodes = reshape([xi; xi], 1, []);
combined_values = reshape([fi; fi], 1, []);
combined_derivatives = reshape([dfi_dx; dfi_dx], 1, []);

hermite_interp = pchip(combined_nodes, combined_values, xx, combined_derivatives);

plot(xx, hermite_interp, 'DisplayName', 'Hermite Interpolation');

xlabel('x');
ylabel('f(x)');
title('Interpolation using Hermite Interpolation');
legend;
