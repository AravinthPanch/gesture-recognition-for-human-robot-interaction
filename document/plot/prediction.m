% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction


clc();
clear();

file_path = '../../data/results/validation-subset/';
dataSets = {'anbc-prediction-nr-2.csv'};
dataSetsNames = {'Walk Gesture','Turn Right Gesture','Turn Left Gesture','Move Right Gesture','Move Left Gesture'};
plotFileNames = {'test-prediction-walk','test-prediction-turn-right','test-prediction-turn-left','test-prediction-move-right','test-prediction-move-left'};
axisPlotFileNames = {'test-axis-walk','test-axis-turn-right','test-axis-turn-left','test-axis-move-right','test-axis-move-left'};
numberOfDataSets = size(dataSets,2);
dataRange = [
    -949.532, -17.4535;
    -598.238, 636.283;
    -330.703, 2668.16;
    -330.703, 853.287;
    -862.075, 707.269;
    -330.703, 2688.34
    ];

for i = 1:numberOfDataSets
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,0);
    
    % Sort data based on label
    groupDataCell = arrayfun(@(x) selectedDataSet(selectedDataSet(:,1) == x, :), unique(selectedDataSet(:,1)), 'uniformoutput', false);
    
    numberOfClasses  = size(groupDataCell,1);
    
    for lbl = 1:numberOfClasses
        classData = groupDataCell{lbl};
        classData = sortrows(classData,7);
        lX = classData(1:end,4);
        lY = classData(1:end,5);
        lZ = classData(1:end,6);
        rX = classData(1:end,7);
        rY = classData(1:end,8);
        rZ = classData(1:end,9);
        
        
        % Normalize
        lXRange = dataRange(1,2) - dataRange(1,1);
        minMaxFunction = @(x) (x - dataRange(1,1)) / lXRange;
        lX = minMaxFunction(lX);
        
        lYRange = dataRange(2,2) - dataRange(2,1);
        minMaxFunction = @(x) (x - dataRange(2,1)) / lYRange;
        lY = minMaxFunction(lY);
        
        lZRange = dataRange(3,2) - dataRange(3,1);
        minMaxFunction = @(x) (x - dataRange(3,1)) / lZRange;
        lZ = minMaxFunction(lZ);
        
        rXRange = dataRange(4,2) - dataRange(4,1);
        minMaxFunction = @(x) (x - dataRange(4,1)) / rXRange;
        rX = minMaxFunction(rX);
        
        rYRange = dataRange(5,2) - dataRange(5,1);
        minMaxFunction = @(x) (x - dataRange(5,1)) / rYRange;
        rY = minMaxFunction(rY);
        
        rZRange = dataRange(6,2) - dataRange(6,1);
        minMaxFunction = @(x) (x - dataRange(6,1)) / rZRange;
        rZ = minMaxFunction(rZ);
        
        
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
        title(strcat('X,Y,Z coordinates of Left and Right hand of', {' '}, dataSetsNames{lbl}))
        xlabel('Validataion Samples');
        ylabel('Normalized distance');
        legend('Left X','Left Y','Left Z','Right X','Right Y','Right Z')
        set(gca,'YTick', 0:0.2:1);
        
        print(axisPlotFileNames{lbl},'-dpng')
        
        
        % Plot predition only
        predictedClassLabel  = classData(1:end,2);
                
        plot(predictedClassLabel, 'red');
        set(gca,'YLim', [0 6]);
        set(gca,'YTick', 0:1:6);
        
        set(gcf, 'Units','point', 'Position',[100 100 900 150])
        set(gcf, 'PaperPositionMode','auto')
        
        title(strcat('Prediction results of', {' '}, dataSetsNames{lbl}))
        xlabel('Validataion Samples');
        ylabel('Class Label');
        
        print(plotFileNames{lbl},'-dpng')        
        
    end
    
end















