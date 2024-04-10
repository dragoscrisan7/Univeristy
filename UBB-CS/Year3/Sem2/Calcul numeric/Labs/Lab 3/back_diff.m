function t = back_diff(f)
  n = length(f);
  t = zeros(n);
  t(:, 1) = f';
  for j=2:n
    t(j:n,j)=diff(t(j-1:n,j-1));
  endfor
end
