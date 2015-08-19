clc()
clear()

file_path = '../../data/train/csv/';
dataSets = {'1.csv','2.csv','3.csv','4.csv','5.csv'};
numberOfDataSets = size(dataSets,2);

meanOutput = zeros(5,6);


dataRanges  = zeros(6,3);


for i = 1:1
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    lX = selectedDataSet(:,1);
    lY = selectedDataSet(:,2);
    lZ = selectedDataSet(:,3);
    rX = selectedDataSet(:,4);
    rY = selectedDataSet(:,5);
    rZ = selectedDataSet(:,6);
    
    min = min(lX)
    range(i,1)
    
end   


for i = 1:1
    dataSetFilePath = strcat(file_path, dataSets{i});
    selectedDataSet = csvread(dataSetFilePath,1,1);
    
    lX = selectedDataSet(:,1);
    lY = selectedDataSet(:,2);
    lZ = selectedDataSet(:,3);
    rX = selectedDataSet(:,4);
    rY = selectedDataSet(:,5);
    rZ = selectedDataSet(:,6);
    
 
    min = -949.532;
    max = -17.4535;
    range = max - min;
    
    array = (lX - min) / range;
    
    mean(array)
    
    
    meanOutput(i,1)= i;
    meanOutput(i,2)= mean(lX);
    meanOutput(i,3)= mean(lY);
    meanOutput(i,4)= mean(lZ);
    meanOutput(i,5)= mean(rX);
    meanOutput(i,6)= mean(rY);
    meanOutput(i,7)= mean(rZ);        
end

% csvwrite('mean',meanOutput);

