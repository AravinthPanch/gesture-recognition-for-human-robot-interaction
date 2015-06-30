% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction

clc();
clear();

file_path = '../../source/human-robot-interaction/data/test/';
dataSets = {'1.csv','2.csv','3.csv','4.csv','5.csv'};
dataSetsNames = {'Walk Gesture','Turn Right Gesture','Turn Left Gesture','Move Right Gesture','Move Left Gesture'};
plotFileNames = {'test-walk','test-turn-right','test-turn-left','test-move-right','test-move-left'};
numberOfDataSets = size(dataSets,2);

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
    
    % Plot Left hand in black (-ve) and right hand in red (+ve) analogy
    c = 'black';
    scatter(lX,lY,c);
    hold on;
    c = 'red';
    scatter(rX,rY,c);
    hold on;
    a = 500;
    c = 'blue';
    d = '+';
    h = scatter(0,0,a,c,d);
    hold off;
        
    if i == 3 || i == 4
        legend('Left Hand','Right Hand', 'Sensor', 'Location','southeast')
    else
        legend('Left Hand','Right Hand', 'Sensor')
    end
    
    xlabel('X in [mm]');
    ylabel('Y in [mm]');
    title(dataSetsNames{i})
    
    % Save the plots to file
    saveas(h, plotFileNames{i} ,'png')
end

