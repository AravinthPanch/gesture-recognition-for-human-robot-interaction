file_name = '1-1.csv';
data = csvread(file_name,0,1);
lX = data(:,1);
lY = data(:,2);
lZ = data(:,3);
rX = data(:,4);
rY = data(:,5);
rZ = data(:,6);

a = 500;

scatter3(mean(lX),mean(lY), mean(lZ), a, 'filled');




