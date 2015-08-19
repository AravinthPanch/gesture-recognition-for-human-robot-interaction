% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction

clc();
clear();

file_path = '../../data/train/csv/';
dataSets = {'1.csv','2.csv','3.csv','4.csv','5.csv'};
dataSetsNames = {'Walk Gesture','Turn Right Gesture','Turn Left Gesture','Move Right Gesture','Move Left Gesture'};
plotFileNames = {'plot-ges-1','plot-ges-2','plot-ges-3','plot-ges-4','plot-ges-5'};
numberOfDataSets = size(dataSets,2);

dataRange = [
    -949.532,-17.4535;
    -598.238,636.283;
    -330.703,2668.16;
    -330.703,853.287;
    -862.075,707.269;
    -330.703,2688.34
    ];

% Plot X and Y positions of gestures at position 1.
% 550 samples are plotted since not every gesture has 600 samples at
% position 1.
a = 150;
for i = 1:numberOfDataSets
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    lX = selectedDataSet(:,1);
    lY = selectedDataSet(:,2);
    lZ = selectedDataSet(:,3);
    rX = selectedDataSet(:,4);
    rY = selectedDataSet(:,5);
    rZ = selectedDataSet(:,6);
    
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
    
    
    switch i
        case 1
            c = 'red';
        case 2
            c = 'black';
        case 3
            c = 'blue';
        case 4
            c = 'green';
        case 5
            c = 'magenta';
    end
    
    scatter(mean(lX),mean(lY), a, c, '<', 'filled');
    hold on;
    h = scatter(mean(rX),mean(rY), a, c , '>' , 'filled');
    
    legend('Walk Gesture - Left Hand','Walk Gesture - Right Hand','Turn Right Gesture - Left Hand','Turn Right Gesture - Right Hand','Turn Left Gesture - Left Hand','Turn Left Gesture - Right Hand','Move Right Gesture - Left Hand','Move Right Gesture - Right Hand','Move Left Gesture - Left Hand','Move Left Gesture - Right Hand', 'location','eastoutside')
    title('Left and right hand position for each gesture using normalized mean values')
    xlabel('X normalized');
    ylabel('Y normalized');
    xlim([0 1]);
    ylim([0 1]);
    grid on;
    set(gcf,'units','points','position',[100,100,1200,500]);
    set(gcf, 'PaperPositionMode','auto');
    
    print('output/train-all-ges-mean','-dpng');
end


