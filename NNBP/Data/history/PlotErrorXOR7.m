%% plot error
figure(1)
load XOR7_Error.txt
data=XOR7_Error;
plot(data,'r')
xlabel('Iteration')
ylabel('Error')
grid on
hold on
title('2 Layer BP Neural Network for XOR with 7 input and 1 output')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])

%% plot result
figure(2)
load XOR7_Result.txt
data=XOR7_Result;
plot(data,'r')
xlabel('Iteration')
ylabel('Error')
grid on
hold on
title('2 Layer BP Neural Network for XOR with 7 input and 1 output')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])









