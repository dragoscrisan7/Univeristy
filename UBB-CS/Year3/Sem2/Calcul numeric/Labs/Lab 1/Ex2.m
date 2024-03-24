#exercise 2:
#f,g,h:[0,2pi]->R

#sinx
y=linspace(0,2*pi,101);
plot(y,sin(y),y,sin(2*y),y,sin(3*y),'k','g','b')
clf
plot(y,sin(y))
hold on
plot(y,sin(2*y))
hold off

f = @(y) sin(y)
fplot(f,[0,2*pi])
hold on
fplot(@(y)sin(2*y))
subplot(3,1,1)
plot(y,sin(y))
subplot(3,1,2)
plot(y,sin(2*y))
subplot(3,1,3)
plot(y,sin(3*y))
