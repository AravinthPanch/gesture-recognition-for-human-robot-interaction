% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction

clc()
clear()

file_path = '../../data/results/';
dataSets = {'accuracy-anbc.csv','accuracy-svm.csv','accuracy-mindist-4.csv'};
plotFileNames = {'test-accuracy-anbc','test-accuracy-svm','test-accuracy-mindist'};
titleName = {'Adaptive Naive Bayes Classifier (ANBC)', 'Support Vector Machine (SVM)', 'Minimum Distance (MinDist)'};

for i = 1:3
    dataSetFilePath = strcat(file_path, dataSets{i});
    data = csvread(dataSetFilePath,1,0);
    
    label = arrayfun(@(x) data(data(:,1) == x, :), unique(data(:,1)), 'uniformoutput', false);
    
    iterations = size(label{1},1);
    x = data(1:iterations,2);
    
    plot(x,label{1}(:,3), 'red', 'LineWidth', 1.5);
    hold on;
    plot(x,label{2}(:,3), 'blue','LineWidth', 1.5);
    hold on;
    plot(x,label{3}(:,3), 'green','LineWidth', 1.5);
    hold on;
    plot(x,label{4}(:,3), 'magenta','LineWidth', 1.5);
    hold on;
    plot(x,label{5}(:,3), 'black','LineWidth', 1.5);
    hold on;
    plot(x,label{6}(:,3), 'yellow','LineWidth', 1.5);
    hold off;
    
    set(gca,'YLim', [0 105]);
    
    title(strcat('Prediction Accuracy vs Null Rejection Accuracy of',{' '},titleName{i}));
    ylabel('Accuracy in %');
    xlabel('Null Rejection Coefficient');
    legend('Null Gesture','Walk','Turn Right','Turn Left','Move Right','Move Left')
    
    set(gcf, 'Units','point', 'Position',[100 100 1200 500])
    set(gcf, 'PaperPositionMode','auto')
    
    print(plotFileNames{i},'-dpng')
    
end
