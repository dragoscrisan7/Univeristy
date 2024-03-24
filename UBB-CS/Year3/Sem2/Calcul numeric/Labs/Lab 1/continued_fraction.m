function result = continued_fraction(n)
    if n == 1
        result = 1 + 1;
    else
        result = 1 + 1 / continued_fraction(n - 1);
    end
end
