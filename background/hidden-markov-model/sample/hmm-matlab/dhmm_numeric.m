% Adapted from Zoubin Ghahramani http://mlg.eng.cam.ac.uk/zoubin/software.html


% function [E,P,Pi,LL]=dhmm_numeric(X,alphabet,K,cyc,tol);
% 
% simple Hidden Markov Model - variable lengths and discrete symbols
%
% X - N x p array of Xs, p sequences
% bins - possible bins of Xs
% K - number of states (default 2)
% cyc - maximum number of cycles of Baum-Welch (default 100)
% tol - termination tolerance (prop change in likelihood) (default 0.0001)
%
% E - observation emission probabilities
% P - state transition probabilities
% Pi - initial state prior probabilities
% LL - log likelihood curve
%
% Iterates until a proportional change < tol in the log likelihood 
% or cyc steps of Baum-Welch

function [E,P,Pi,LL]=dhmm_numeric(X,pP,bins,K,cyc,tol)

D = size(X,2);
num_bins = size(bins,1); 

epsi = 1e-10;

% number of sequences
N = size(X,1);

% length of each sequence
T = ones(1,N);
for n=1:N,
  T(n)=size(X{n},1);
end;

TMAX = max(T);

if nargin<6   tol=0.0001; end;
if nargin<5   cyc=100; end;
if nargin<4   K=2; end;

fprintf('\n********************************************************************\n');
fprintf('Training %i sequences of maximum length %i from an alphabet of size %i\n',N,TMAX,num_bins);
fprintf('HMM with %i hidden states\n',K);
fprintf('********************************************************************\n');

E = (0.1*rand(num_bins,K)+ones(num_bins,K))/num_bins;
E = cdiv(E,csum(E));

%E = (1/num_bins).*ones(num_bins,K);

B=zeros(TMAX,K);

Pi= rand(1,K);
Pi=Pi/sum(Pi);

% transition matrix
P = pP;
P=rdiv(P,rsum(P));

% This is useful if the transition matrix is initialized with many zeros
% i.e. for a left-to-right HMM
P=sparse(P);

LL=[];
lik=0;

for cycle=1:cyc

  %%%% FORWARD-BACKWARD
  

  Gammainit=zeros(1,K);
  Gammasum=zeros(1,K);
  Gammaksum = zeros(num_bins,K);
  Scale=zeros(TMAX,1);
  sxi=sparse(K,K);

  for n=1:N
    alpha=zeros(T(n),K);
    beta=zeros(T(n),K);
    gamma=zeros(T(n),K);
    gammaksum = zeros(num_bins,K);  

    % Inital values of B = Prob(output|s_i), given data X

    Xcurrent=X{n};
    
    for i=1:T(n)
        %for j=1:D
          % find the letter in the alphabet
          % m = findstr(alphabet,Xcurrent(i));
            m = find(bins==Xcurrent(i));
            if (m == 0)
              fprintf('Error: Symbol not found\n');  
              return;
            end
            B(i,:) = E(m,:);
        %end
    end;

    scale=zeros(T(n),1);
    alpha(1,:)=Pi(:)'.*B(1,:);
    scale(1)=sum(alpha(1,:));
    alpha(1,:)=alpha(1,:)/scale(1);
    for i=2:T(n)
      alpha(i,:)=(alpha(i-1,:)*P).*B(i,:);
      scale(i)=sum(alpha(i,:));
      alpha(i,:)=alpha(i,:)/scale(i);
    end;

    beta(T(n),:)=ones(1,K)/scale(T(n));
    for i=T(n)-1:-1:1
      beta(i,:)=(beta(i+1,:).*B(i+1,:))*(P')/scale(i); 
    end;

    gamma=(alpha.*beta)+epsi;
    gamma=rdiv(gamma,rsum(gamma));

    gammasum=sum(gamma);

    for i = 1:T(n)
      % find the letter in the alphabet
      % m = findstr(alphabet,Xcurrent(i));
      m = find(bins==Xcurrent(i));
      gammaksum(m,:) = gammaksum(m,:) + gamma(i,:);
    end;

    for i=1:T(n)-1
      t=P.*( alpha(i,:)' * (beta(i+1,:).*B(i+1,:)));
      sxi=sxi+t/sum(t(:));
    end;

    Gammainit=Gammainit+gamma(1,:);
    Gammasum=Gammasum+gammasum;
    Gammaksum = Gammaksum + gammaksum;

    for i=1:T(n)-1
      Scale(i,:) = Scale(i,:) + log(scale(i,:));
    end;
    Scale(T(n),:) = Scale(T(n),:) + log(scale(T(n),:));

  end;
  
  %%%% M STEP 
  
  % outputs

  E = cdiv(Gammaksum,Gammasum);

  % transition matrix 
  P = sparse(rdiv(sxi,rsum(sxi)));
  P = P*eye(size(P,1));

  % priors
  Pi=Gammainit/sum(Gammainit);

  oldlik=lik;
  lik=sum(Scale);
  LL=[LL lik];
  fprintf('\ncycle %i log likelihood = %f ',cycle,lik);  
  if (cycle<=2)    likbase=lik;
  elseif (lik<(oldlik - 1e-6))     fprintf('vionum_binstion');
  elseif ((lik-likbase)<(1 + tol)*(oldlik-likbase)||~isfinite(lik)) 
    fprintf('\nend\n');    return;
  end;

end










