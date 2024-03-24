function x = gauss(A,b)
  [r,n]=size(A);
  x = zeros(size(b));
  A=[A,b];
  for j = 1:n-1
    [v,p]=max(abs(A(j:r,j)));
    #example: A([a,b],:)=A([b,a],:);
    p=p+j-1;
    if p~=j
      A([j, p],:)=A([p,j],:);
    endif
    for i = j+1:r
      m = A(i, j)/A(j, j);
    endfor
    A(i, j:n+1)=A(i, j:n+1)-m*A(j, j:n+1);
  endfor
   x = backwards_subs(A(:,1:n),A(:,n+1));
 end
