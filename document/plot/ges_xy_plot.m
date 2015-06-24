% Author: Aravinth Panchadcharam
% Email: me@aravinth.info
% Project: Gesture Recognition For Human-Robot Interaction

dataSets = {'1.csv','2.csv','3.csv','4.csv','5.csv'};
dataSetsNames = {'Walk Gesture','Turn Right Gesture','Turn Left Gesture','Move Right Gesture','Move Left Gesture'};
plotFileNames = {'plot-ges-1','plot-ges-2','plot-ges-3','plot-ges-4','plot-ges-5'};
numberOfDataSets = size(dataSets,2);

% Plot X and Y positions of gestures at position 1. 
% 550 samples are plotted since not every gesture has 600 samples at
% position 1.
for i = 1:numberOfDataSets
    selectedDataSet = csvread(dataSets{i},0,1);
    
    lX = selectedDataSet(1:550,1);
    lY = selectedDataSet(1:550,2);   
    rX = selectedDataSet(1:550,4);
    rY = selectedDataSet(1:550,5);
    
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
    
    legend('Left Hand','Right Hand', 'Sensor')
    xlabel('X-coordinate [mm]');
    ylabel('Y-coordinate [mm]');
    title(dataSetsNames{i})

% Save the plots to file
    saveas(h, plotFileNames{i} ,'png')
end

% Plot x,z axis at position 1
i = 1;
selectedDataSet = csvread(dataSets{i},0,1);

lX = selectedDataSet(:,1);    
lZ = selectedDataSet(:,3);    
rX = selectedDataSet(:,4);
rZ = selectedDataSet(:,6);

% Plot Left hand in black (-ve) and right hand in red (+ve) analogy    
c = 'black';
scatter(lX,lZ,c);
hold on;
c = 'red';
scatter(rX,rZ,c);
hold on;
a = 500;
c = 'blue';
d = '+';
h = scatter(0,0,a,c,d);
hold off;

ylim([-50 3500])
legend('Left Hand','Right Hand', 'Sensor')
xlabel('X-coordinate [mm]');
ylabel('Z-coordinate [mm]');
title('Training data of Walk Gesture at 4 different position')

% Save the plots to file
saveas(h, 'plot-ges-pos-4' ,'png')