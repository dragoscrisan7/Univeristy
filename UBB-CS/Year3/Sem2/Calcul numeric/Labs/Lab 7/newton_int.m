function f = newton_int(d, xi, x)
    n = length(xi);
    m = length(x);
    f = zeros(1, m);

    for j = 1:m
        prod_term = 1;
        sum_term = d(1);
        for i = 2:n
            prod_term = prod_term .* (x(j) - xi(i-1));
            sum_term = sum_term + d(i) * prod_term;
        end
        f(j) = sum_term;
    end
end

