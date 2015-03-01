%************************************************************
%
%  Get 10 sequences of XYZ data from CSVs (setup is not really generic)
%
%************************************************************

function data = get_xyz_data(path,name)

x = csvread(strcat(path, filesep, name, '_x.csv'));
y = csvread(strcat(path, filesep, name, '_y.csv'));
z = csvread(strcat(path, filesep, name, '_z.csv'));


data = cat(3, x, y, z);