%% plot error
figure(1)
load dataXOR2.txt
data=dataXOR2;
plot(data,'r')
xlabel('Iteration')
ylabel('Error')
grid on
hold on
title('2 Layer BP Neural Network for XOR')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])










