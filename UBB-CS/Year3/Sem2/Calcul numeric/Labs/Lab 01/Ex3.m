#exercise 3
#{ x(t)=(R+r)cos t - r cos((R/r+1)t)
#{ y(t)=(R+r)sin t - r sin((R/r+1)t)
#t belongs to [0,10pi]

R=3.8;r=1;
t=linspace(0,10*pi,1000);
x=(R+r)*cos(t)-r*cos((R/r+1)*t);
y=(R+r)*sin(t)-r*sin((R/r+1)*t);
plot(x,y)
