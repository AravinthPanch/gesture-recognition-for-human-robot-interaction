clc()
clear()

file_path = '../../data/results/prediction-likelihood/';
file_name = strcat( file_path, '2.csv');
data = csvread(file_name,1,0);

x = data(:,1);
y = data(:,2);


plot(y);
set(gca,'YLim', [0 5]);
set(gca,'YTick', 0:1:5);




