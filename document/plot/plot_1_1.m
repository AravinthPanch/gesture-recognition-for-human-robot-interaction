file_name = '2-1.csv';
data = csvread(file_name,0,1);
lX = data(:,4);
lY = data(:,5);
lZ = data(:,6);


scatter3(lX,lZ,lY);

zlim([-1000 1000])
xlim([-1000 1000])
ylim([0 5000])

