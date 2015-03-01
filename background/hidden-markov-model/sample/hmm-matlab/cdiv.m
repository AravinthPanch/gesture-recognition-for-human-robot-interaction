% column division
% function Z=cdiv(X,Y)

function Z=cdiv(X,Y)

if(length(X(1,:)) ~= length(Y(1,:)) | length(Y(:,1)) ~=1)
  disp('Error in CDIV');
  return;
end

Z=zeros(size(X));

for i=1:length(X(:,1))
  Z(i,:)=X(i,:)./Y;
end
