function [x, mit] = gauss_seidel_sor(A, b, X0, maxmit, err, omega)
    L = -tril(A, -1);
    D = diag(diag(A));
    U = -triu(A, 1);

    M = D - L;
    N = U;

    T = inv(D - L) * U;
    c = inv(D - L) * b;

    x = X0;
    for mit = 1:maxmit
        x_old = x;
        x = T * x_old + c;
        if norm(x - x_old, inf) < err
            return;
        end
    end
end
