%************************************************************
%
%  Create a prior for the transition matrix
%
%************************************************************

function P = prior_transition_matrix(K,LR)

% LR is the allowable number of left-to-right transitions

P = ((1/LR))*eye(K);

for i=1:K-(LR-1)
    for j=1:LR-1
        P(i,i+j) = 1/LR;
    end
end
for i=K-(LR-2):K
    for j=1:K-i+1
        P(i,i+(j-1)) = 1/(K-i+1);
    end
end