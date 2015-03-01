%************************************************************
%
%  Create histogram to bin the data
%
%************************************************************

function XClustered = get_point_clusters(data,centroids,D)

XClustered = cell(size(data,2),1);
K = size(centroids,1);

for n = 1:size(data,1)
    for i = 1:size(data,2)
        temp = zeros(K,1);
        for j = 1:K
            if (D==3)
                temp(j) = sqrt( (centroids(j,1) - data(n,i,1))^2+(centroids(j,2) - data(n,i,2))^2+(centroids(j,3) - data(n,i,3))^2);
            end
        end
        [idx,I] = min(temp);
        XClustered{i}(n,1) = I(1);
    end
end
