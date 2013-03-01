%% PostProcessST
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Script for reformating LIF_spike output file in usual array format:
%       col1        |     col2       |       col3         |     col4
%   stimulus index  |  trial index   |   spike time (ms)  |  neuron index
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Parameters
trajFile = '../data/traj.dat';
spikeFile = '../data/LIF_spike.dat';
outFile = './ST.dat';

%% Loading Data
ST = importdata(spikeFile);
traj = importdata(trajFile);

%% Extracting Stimulus and Trial indexes of spikes
trajSti = unique(traj(:,9))';
trajTri = unique(traj(:,8))';
nbSti = length(trajSti);
nbTri = length(trajTri);
disp(['Number of Stimuli detected: ',num2str(nbSti)]);
disp(['Number of Trials detected: ',num2str(nbTri)]);

outST = zeros(size(ST,1),4);
outST(:,3:4) = ST;

for i = 1:nbSti
    atraj = traj(traj(:,9)==trajSti(i),:);
    for j = 1:nbTri
        disp(['Processing: stimulus ',num2str(i-1),', trial ',num2str(j-1)]);
        tmpr = find(outST(:,3)>=min(atraj(atraj(:,8)==trajTri(j),1)) & outST(:,3)<=max(atraj(atraj(:,8)==trajTri(j),1)));
        outST(tmpr,1) = i-1;
        outST(tmpr,2) = j-1;
        outST(tmpr,3) = outST(tmpr,3) - min(atraj(atraj(:,8)==trajTri(j),1));
    end
end
outST = sortrows(outST);

%% Saving output
dlmwrite(outFile,outST,'delimiter',' ');

%% Display
% figure, box on,
% alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
% for sti = unique(outST(:,1)')
%     for tri = unique(outST(:,2)')
%         plot(outST(outST(:,1)==sti & outST(:,2)==tri,3),outST(outST(:,1)==sti & outST(:,2)==tri,4),'.k');
%         xlabel('time (ms)')
%         ylabel('neuron index')
%         title([alphabet(sti+1),' - trial ',num2str(tri)]);
%         pause(0.5);
%     end
% end