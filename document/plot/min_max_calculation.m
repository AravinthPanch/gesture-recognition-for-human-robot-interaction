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
    -949.532, -17.4535;
    -598.238, 636.283;
    -330.703, 2668.16;
    -330.703, 853.287;
    -862.075, 707.269;
    -330.703, 2688.34
    ];


i = 1;
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


mean(lX)
mean(lY)
mean(lZ)
mean(rX)
mean(rY)
mean(rZ)

