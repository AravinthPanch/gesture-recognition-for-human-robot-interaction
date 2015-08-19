% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction

clc()
clear()

file_path = '../../data/results/validation-subset/';
dataSets = {'anbc-recall-nr-0-10.csv'};
plotFileNames = {'test-accuracy-anbc','test-accuracy-svm','test-accuracy-mindist'};
titleName = {'Adaptive Naive Bayes Classifier (ANBC)', 'Support Vector Machine (SVM)', 'Minimum Distance (MinDist)'};

i = 1;
dataSetFilePath = strcat(file_path, dataSets{i});
data = csvread(dataSetFilePath,1,0);

class0 = data(:,2)*100;
class1 = data(:,3)*100;
class2 = data(:,4)*100;
class3 = data(:,5)*100;
class4 = data(:,6)*100;
class5 = data(:,7)*100;
nr = data(:,1);

plot(nr, class0, 'red', 'LineWidth', 1.5);
hold on;
plot(nr, class1, 'blue','LineWidth', 1.5);
hold on;
plot(nr, class2, 'green','LineWidth', 1.5);
hold on;
plot(nr, class3, 'magenta','LineWidth', 1.5);
hold on;
plot(nr, class4, 'black','LineWidth', 1.5);
hold on;
plot(nr, class5, 'yellow','LineWidth', 1.5);
hold off;

set(gca,'YLim', [0 105]);
title(strcat('Prediction Accuracy vs Null Rejection Accuracy of',{' '},titleName{i}));
ylabel('Accuracy in %');
xlabel('Null Rejection Coefficient');
legend('Null Gesture','Walk','Turn Right','Turn Left','Move Right','Move Left')

set(gcf, 'Units','point', 'Position',[100 100 1200 500])
set(gcf, 'PaperPositionMode','auto')

print(strcat('output/',plotFileNames{i}),'-dpng')