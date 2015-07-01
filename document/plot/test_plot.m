clc()
clear()

file_path = '../../data/results/';
file_name = strcat( file_path, 'accuracy.csv');
data = csvread(file_name,1,0);


lbl1 = data(1:46,3);
lbl2 = data(47:92,3);
lbl3 = data(93:138,3);
lbl4 = data(139:184,3);
lbl5 = data(185:230,3);
lbl0 = data(231:276,3);

x = data(1:46,2);

plot(x,lbl0, 'blue');
hold on;
plot(x,lbl1, 'red');
hold on;
plot(x,lbl2, 'green');
hold on;
plot(x,lbl3, 'magenta');
hold on;
plot(x,lbl4, 'black');
hold on;
plot(x,lbl5, 'yello');
hold off;

% lX = data(:,1);
% lY = data(:,2);
% lZ = data(:,3);
% rX = data(:,4);
% rY = data(:,5);
% rZ = data(:,6);
%
% scatter3(lX, lY, lZ);




