file_name = '2-1.csv';
data = csvread(file_name,0,1);
lX = data(:,1);
lY = data(:,2);
lZ = data(:,3);
rX = data(:,4);
rY = data(:,5);
rZ = data(:,6);


c = 'red';
scatter(lX,lY,c);
hold on;
c = 'black';
scatter(rX,rY,c);
hold on;
a = 50;
c = 'blue';
scatter(0,0,a,c,'filled');
legend('Left Hand','Right Hand', 'Sensor', 'Location','southwest')
ylim([-50 700])



