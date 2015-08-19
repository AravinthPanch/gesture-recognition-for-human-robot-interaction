% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction

clc();
clear();

file_path = '../../data/train/csv/';
dataSets = {'1.csv','2.csv','3.csv','4.csv','5.csv'};
dataSetsNames = {'Walk Gesture','Turn Right Gesture','Turn Left Gesture','Move Right Gesture','Move Left Gesture'};
plotFileNames = {'test-walk','test-turn-right','test-turn-left','test-move-right','test-move-left'};
numberOfDataSets = size(dataSets,2);


dataRange = [
    -949.532, -17.4535;
    -598.238, 636.283;
    -330.703, 2668.16;
    -330.703, 853.287;
    -862.075, 707.269;
    -330.703, 2688.34
    ];


% Plot X and Y positions of gestures at position 1.
% 550 samples are plotted since not every gesture has 600 samples at
% position 1.
for i = 1:numberOfDataSets
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    lX = selectedDataSet(30:90,1);
    lY = selectedDataSet(30:90,2);
    rX = selectedDataSet(30:90,4);
    rY = selectedDataSet(30:90,5);
    
    lXRange = dataRange(1,2) - dataRange(1,1);
    minMaxFunction = @(x) (x - dataRange(1,1)) / lXRange;
    lX = minMaxFunction(lX);
    
    lYRange = dataRange(2,2) - dataRange(2,1);
    minMaxFunction = @(x) (x - dataRange(2,1)) / lYRange;
    lY = minMaxFunction(lY);
    
    rXRange = dataRange(4,2) - dataRange(4,1);
    minMaxFunction = @(x) (x - dataRange(4,1)) / rXRange;
    rX = minMaxFunction(rX);
    
    rYRange = dataRange(5,2) - dataRange(5,1);
    minMaxFunction = @(x) (x - dataRange(5,1)) / rYRange;
    rY = minMaxFunction(rY);
    
    
     % Plot Left hand in black (-ve) and right hand in red (+ve) analogy
    c = 'black';
    scatter(lX,lY,c);
    hold on;
    c = 'red';
    h = scatter(rX,rY,c);
    hold off;
        
    legend('Left Hand','Right Hand')
    xlabel('X normalized');
    ylabel('Y normalized');
    title(dataSetsNames{i});
    xlim([0 1]);
    ylim([0 1]);
    grid on;
    
    % Save the plots to file
    saveas(h, strcat('output/', plotFileNames{i}) ,'png')
end

