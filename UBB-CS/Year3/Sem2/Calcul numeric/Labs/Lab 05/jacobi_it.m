function[x,mit] = jacobi_it(A,b,X0,maxmit,err)
  M = diag(diag(A));
  N = M - A;
  T = inv(M) * N;
  alpha = norm(T, inf);
  c = inv(M) * b;

  x = X0;
  for mit = 1:maxmit
    x_old = x;
    x = T * x_old + c;
     if norm(x - x_old, inf) < err * (1 - alpha) / alpha
            return;
    endif
  endfor
end
