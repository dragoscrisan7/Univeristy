function P = aitken(fi, x, xi)
    n = length(x);
    P = zeros(n, n);
    for i = 1:n
        P(i,1) = fi(i);
        for j = 1:i-1
            P(i,j+1) = ((xi-x(j))* P(i, j) - (xi-x(i)) * P(j,j)) /(x(i) - x(j))
        end
    end
end
