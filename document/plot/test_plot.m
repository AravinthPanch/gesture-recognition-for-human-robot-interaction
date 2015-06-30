clc()
clear()

file_path = '../../source/human-robot-interaction/data/test/';
file_name = strcat( file_path, '0.csv');
data = csvread(file_name,1,1);
lX = data(:,1);
lY = data(:,2);
lZ = data(:,3);
rX = data(:,4);
rY = data(:,5);
rZ = data(:,6);

scatter3(lX, lY, lZ);




