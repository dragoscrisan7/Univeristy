% Define the function f(x) = cos(πx) and the nodes
xi = [0, 1/3, 1/2, 1];
fi = cos(pi * xi);

% Compute divided differences
# div_diff from lab 3
d = div_diff(xi,fi);

% Define points for plotting
xx = linspace(0,1,100);

% a) Find the Lagrange polynomial L3f using Newton’s divided differences
L3f = newton_int2(d, xi, xx);

% b) Find a bound for the error R3f
% True function values
true_values = cos(pi * xx);

% Maximum absolute error
error_bound = max(abs(L3f - true_values));

% c) Plot f and L3f on the same set of axes
plot(xx, true_values, xx, L3f);
legend({'f(x) = cos(\pi x)', 'L_3 f'}, 'Location', 'northwest');
xlabel('x');
ylabel('y');
title('True function and Interpolated Polynomial');


% d) Use L3f to approximate cos(π/5)
approximation = newton_int2(d, xi, 1/5)


% e) Find a bound for the error of this approximation
true_value_at_pi_over_5 = cos(pi / 5)
error_of_approximation = abs(approximation - true_value_at_pi_over_5)

#plot(xx,cos(pi*xx),xx,newton_int2(d,xi,xx))
