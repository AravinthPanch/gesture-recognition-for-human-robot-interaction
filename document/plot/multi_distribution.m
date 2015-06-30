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

% Plot X and Y positions of gestures at position 1.
% 550 samples are plotted since not every gesture has 600 samples at
% position 1.
a = 500;
for i = 1:numberOfDataSets
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    lX = selectedDataSet(:,1);
    lY = selectedDataSet(:,2);
    lZ = selectedDataSet(:,3);
    rX = selectedDataSet(:,4);
    rY = selectedDataSet(:,5);
    rZ = selectedDataSet(:,6);
    
    switch i
        case 1
            c = 'red';
        case 2
            c = 'black';
            scatter3(0,0,0, a, c ,'+');
        case 3
            c = 'blue';
        case 4
            c = 'green';
        case 5
            c = 'yello';
    end
    
    scatter3(mean(lZ), mean(lX),mean(lY), a, c, '<', 'filled');
    hold on;
    h = scatter3(mean(rZ), mean(rX),mean(rY), a, c , '>' , 'filled');
    
    title('Mean')
    xlabel('Z [mm]');
    ylabel('X [mm]');
    zlabel('Y [mm]');
    legend('Walk Left Hand','Walk Right Hand','Sensor','Turn Right Left Hand','Turn Right Right Hand','Turn Left Left Hand','Turn Left Right Hand','Move Right Left Hand','Move Right Right Hand','Move Left Left Hand','Move Left Right Hand')
    view(-80,10);
end

