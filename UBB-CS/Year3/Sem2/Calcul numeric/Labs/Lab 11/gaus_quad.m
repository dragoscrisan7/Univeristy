function [I, g_nodes, g_coeff] = gaus_quad(f, n, g_type)
  alpha = zeros(1,n)
  switch g_type
    case 1 #Legenfre
      beta = [2, (4-([1:n-1]).^(-2)).^(-1)];
    case 2 #Chebyshev
      beta = [pi, 1/2, 1/4*ones(1,n-2)];
    case 3
      beta = [pi/2, 1/4];
    case 4
      #beta = [1,1,4,9,16,..(n-1)^2]
    case 5

  endswitch
  J = diag(alpha) + diag(sqrt(beta(2:n)),1)+diag(sqrt(beta(2:n)), -1);
  [v,d] = eig(J);
  g_nodes = diag(d);
  g_coeff = beta(1)*v(1,:).^2;
  I = g_coeff*f(g_nodes);
end
