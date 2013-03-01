%%%%%%%%%%%%%%%%%%%%%%%%%
%
%   Stimuli Map
%
%   JP - 2010/11/29
%
%%%%%%%%%%%%%%%%%%%%%%%%%

% creates a map for Braille Stimuli (every letter saved in new cell, with
% upper left dot at position [0,0]);

all_sti_map = cell(1,27);
alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
offsetXY = [3.75,-3.75];

% dot line,colonne
dot11 = [0,0].*offsetXY;
dot12 = [1,0].*offsetXY;
dot21 = [0,1].*offsetXY;
dot22 = [1,1].*offsetXY;
dot31 = [0,2].*offsetXY;
dot32 = [1,2].*offsetXY;

all_sti_map{1} = [dot11];
all_sti_map{2} = [dot11;dot21];
all_sti_map{3} = [dot11;dot12];
all_sti_map{4} = [dot11;dot12;dot22];
all_sti_map{5} = [dot11;dot22];
all_sti_map{6} = [dot11;dot21;dot12];
all_sti_map{7} = [dot11;dot21;dot12;dot22];
all_sti_map{8} = [dot11;dot21;dot22];
all_sti_map{9} = [dot12;dot21];
all_sti_map{10} = [dot12;dot21;dot22];
all_sti_map{11} = [dot11;dot31];
all_sti_map{12} = [dot11;dot21;dot31];
all_sti_map{13} = [dot11;dot12;dot31];
all_sti_map{14} = [dot11;dot12;dot22;dot31];
all_sti_map{15} = [dot11;dot22;dot31];
all_sti_map{16} = [dot11;dot21;dot12;dot31];
all_sti_map{17} = [dot11;dot21;dot12;dot22;dot31];
all_sti_map{18} = [dot11;dot21;dot22;dot31];
all_sti_map{19} = [dot12;dot21;dot31];
all_sti_map{20} = [dot12;dot21;dot22;dot31];
all_sti_map{21} = [dot11;dot31;dot32];
all_sti_map{22} = [dot11;dot21;dot31;dot32];
all_sti_map{23} = [dot12;dot21;dot22;dot32];
all_sti_map{24} = [dot11;dot12;dot31;dot32];
all_sti_map{25} = [dot11;dot12;dot22;dot31;dot32];
all_sti_map{26} = [dot11;dot22;dot31;dot32];
all_sti_map{27} = [];

% for i=1:length(all_sti_map)
%     plot(all_sti_map{i}(:,1),all_sti_map{i}(:,2),'o');
%     axis([-3,10,-10,3]);
%     title(alphabet(i));
%     pause,
% end

%% Creating array for PSoma NET file
for i=1:26,
    all_sti_map{i}(:,2) = all_sti_map{i}(:,2)-3.75+100*(i-1);
end
stimuli = cell2mat(all_sti_map');
stimuli = [stimuli,zeros(size(stimuli,1),1)]