%% plot error
figure(1)
load XOR2_Error.txt
data=XOR2_Error;
plot(data,'r')
xlabel('Iteration')
ylabel('Error')
grid on
hold on
title('2 Layer BP Neural Network for XOR with 2 input and 1 output-The Error line')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])

%% plot result
figure(2)
load XOR2_Result.txt
data=XOR2_Result;
plot(data,'r')
xlabel('times')
ylabel('Accuracy')
grid on
hold on
title('2 Layer BP Neural Network for XOR with 2 input and 1 output-The Result line')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])

