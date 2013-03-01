%% First spike SD


%% Parameters
trajFile = '../data/traj.dat';
spikeFile = '../data/LIF_spike.dat';
xaxis = [-2:0.2:10];
MR_idx = 18;     % index of MR to consider, if -1 then consider all MR
sd_binsize = 5;     % number of repetitions on which to compute SD, -1 compute on all repetitions

%% Loading Data
ST = importdata(spikeFile);
traj = importdata(trajFile);

%% Extracting Repetitions Boundry Times
repeats = unique(traj(:,8))';
nbReps = length(repeats);
repTimes = zeros(2,nbReps);
for r = 1:nbReps
    repTimes(:,r) = [min(traj(traj(:,8)==repeats(r),1)),max(traj(traj(:,8)==repeats(r),1))];
end

%% Extracting First Spike Times
if MR_idx == -1
    MR = unique(ST(:,2))';
else
    MR = MR_idx;
end
nbMRs = length(MR);
sTimes = -1*ones(nbMRs,nbReps);
for r = 1:nbReps
    st = ST(ST(:,1)>=repTimes(1,r) & ST(:,1)<=repTimes(2,r),:);
    for mr = 1:nbMRs
        sTimes(mr,r) = min(st(st(:,2)==MR(mr),1)) - repTimes(1,r);
    end
end

%% Computing SD
if sd_binsize==-1
    SDs = std(sTimes')';
else
    nb_sds = floor(nbReps/sd_binsize);
    SDs = -1*ones(nbMRs,nb_sds);
    for s = 1:nb_sds
        SDs(:,s) = std(sTimes(:,(s-1)*sd_binsize+1:s*sd_binsize)')';
    end
end

%% Display
figure, hist(SDs(:),xaxis);

%% Accumulating data
% if ~exist('SDs_out','var')
%     SDs_out = SDs;
% else
%     SDs_out = [SDs_out;SDs];
% end