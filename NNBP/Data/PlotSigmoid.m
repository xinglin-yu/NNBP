%% plot sigmod
figure(2)
x=-10:0.1:10
y=1./(1+exp(-x));
plot(x,y,'r')
grid on
hold on
plot([x(1) x(end)],[0.5 0.5],'b')
plot([0 0],[0 1],'b')

xlabel('x')
ylabel('y')

title('Sigmod function: y=1/(1+exp(-x))')
