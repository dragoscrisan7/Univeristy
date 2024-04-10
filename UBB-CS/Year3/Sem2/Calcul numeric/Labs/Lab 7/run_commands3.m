x_values = [1000, 1010, 1020, 1030, 1040, 1050];

lg_x_values = [3.0000000, 3.0043214, 3.0086002, 3.0128372, 3.0170333, 3.0211893];

d = div_diff(x_values, lg_x_values);

x_to_aprox = 1001:1009;

lg_x_approximations = newton_int(d, x_values, x_to_approx);

disp('Approximations of lg x for x = 1001, 1002, ..., 1009:');
disp(lg_x_approximations);
