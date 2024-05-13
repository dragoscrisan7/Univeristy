% Set recursion limit
#set(0, 'RecursionLimit', 1000);

% Compute f(2)
f_2 = continued_fraction(2);
disp(['f(2) = ', num2str(f_2)]);

% Compute f(10)
f_10 = continued_fraction(10);
disp(['f(10) = ', num2str(f_10)]);

% Compute f(2024)
f_2024 = continued_fraction(2024);
disp(['f(2024) = ', num2str(f_2024)]);

