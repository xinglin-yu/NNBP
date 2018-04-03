%% plot error
figure(1)
load XOR7_Error.txt
data=XOR7_Error;
plot(data,'r')
xlabel('Iteration')
ylabel('Error')
grid on
hold on
title('2 Layer BP Neural Network for XOR with 7 input and 1 output-The Error line')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])

%% plot result
figure(2)
load XOR7_Result.txt
data=XOR7_Result;
average=mean(data);
plot(data,'r')

grid on
hold on
plot([1 length(data)],[average average],'b')

xlabel('times')
ylabel('Accuracy')
title('2 Layer BP Neural Network for XOR with 7 input and 1 output-The Result line')
legend(['Error is ',num2str(data(end)),' after iteration ',num2str(length(data)),' times,',])

