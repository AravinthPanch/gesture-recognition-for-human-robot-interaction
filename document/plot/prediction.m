% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction


clc();
clear();

file_path = '../../data/results/prediction-likelihood/';
dataSets = {'1.csv','2.csv','3.csv','4.csv','5.csv'};
dataSetsNames = {'Walk Gesture','Turn Right Gesture','Turn Left Gesture','Move Right Gesture','Move Left Gesture'};
plotFileNames = {'test-prediction-walk','test-prediction-turn-right','test-prediction-turn-left','test-prediction-move-right','test-prediction-move-left'};
axisPlotFileNames = {'test-axis-walk','test-axis-turn-right','test-axis-turn-left','test-axis-move-right','test-axis-move-left'};
numberOfDataSets = size(dataSets,2);

for i = 1:numberOfDataSets
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    lX = selectedDataSet(1:1400,3);
    lY = selectedDataSet(1:1400,4);
    lZ = selectedDataSet(1:1400,5);
    rX = selectedDataSet(1:1400,6);
    rY = selectedDataSet(1:1400,7);
    rZ = selectedDataSet(1:1400,8);
    
    plot(lX, 'blue');
    hold on;
    plot(lY, 'red');
    hold on;
    plot(lZ, 'green');
    hold on;
    plot(rX, 'magenta');
    hold on;
    plot(rY, 'black');
    hold on;
    plot(rZ, 'yello');
    hold off;
    
    set(gcf, 'Units','point', 'Position',[100 100 900 150])
    set(gcf, 'PaperPositionMode','auto')
    
    title(strcat('X,Y,Z coordinates of Left and Right hand of', {' '}, dataSetsNames{i}))
    xlabel('Input Samples');
    ylabel('Distance in [mm]');
    legend('Left X','Left Y','Left Z','Right X','Right Y','Right Z')
    
    print(axisPlotFileNames{i},'-dpng')
end


for i = 1:numberOfDataSets
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    predictedClass = selectedDataSet(1:1400,1);
    
    plot(predictedClass, 'red');
    set(gca,'YLim', [0 6]);
    set(gca,'YTick', 0:1:6);
    
    set(gcf, 'Units','point', 'Position',[100 100 900 150])
    set(gcf, 'PaperPositionMode','auto')
    
    title(strcat('Prediction results of', {' '}, dataSetsNames{i}))
    xlabel('Input Samples');
    ylabel('Class Label');
    
    print(plotFileNames{i},'-dpng')
end






