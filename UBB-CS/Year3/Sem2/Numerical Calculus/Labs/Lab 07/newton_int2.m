function f = newton_int(d, xi, x)
    m = length(x);
    f = zeros(1, m);

    for j = 1:m
      dif = x(j)-xi;
      f(j) = (d(1,:)*[1,cumprod(dif(1:end-1))]');
    end
end
