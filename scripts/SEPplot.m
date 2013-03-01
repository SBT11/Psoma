%% SEPplot

%% Parameters
trajFile = '../data/traj.dat';
spikeFile = '../data/LIF_spike.dat';
xAxisLim = [-16 16];
yAxisLim = [-16 16];


%% Loading files
traj = importdata(trajFile);
ST = importdata(spikeFile);

% %% Isolating trajectory segments from teleportations
% s_idx = unique(traj(:,9));
% tmp = [];
% for i=1:length(s_idx)
%     if sum(traj(:,9)==s_idx(i))<2
%         tmp = [tmp,i];
%     end
% end
% s_idx(tmp) = [];
% 
% %% Placing spikes for SEP
% all_mr = unique(ST(:,2));
% SEPs = cell(1,length(all_mr));
% 
% for i = 1:length(s_idx)
%     segment = traj()
%     tmpr = find(ST())
% end

%% Placing spikes for SEP
all_mr = unique(ST(:,2));
SEPs = cell(1,length(all_mr));
for i = 1:length(all_mr)
    SEPs{i} = [];
end

for i = 1:size(ST,1)
    mr_idx = find(all_mr==ST(i,2)); 
    traj_idx = find(traj(:,1)==ST(i,1));
    SEPs{mr_idx} = [SEPs{mr_idx};[traj(traj_idx,2),traj(traj_idx,3)]];
    if(mod(i/size(ST,1),0.1)<0.001)
        disp([num2str(i/size(ST,1)*100),'%']);
    end
end

%% Display
figure,
nl = floor(sqrt(length(all_mr)));
nc = ceil(length(all_mr)/nl);
for i = 1:length(all_mr)
    subplot(nl,nc,i);
    plot(SEPs{i}(:,1),SEPs{i}(:,2),'.');
    title(all_mr(i));
    xlim(xAxisLim);
    ylim(yAxisLim),
    
end