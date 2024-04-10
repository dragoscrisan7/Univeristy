function [z,t]=div_diff2(x,f,fd)
    n=length(x);
    z=repelem(x,2);
    t=zeros(2*n);
    t(:,1)=repelem(f,2)';
    t(1:2:2*n-1,2)=fd';
    t(2:2:2*n-2,2)=(diff(f)./diff(x))';
    for j=3:2*n
        t(1:2*n-j+1,j)=diff(t(1:2*n-j+2,j-1))./(z(j:2*n)-z(1:2*n-j+1))';
    end
end
