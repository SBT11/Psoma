%% SEP trajectory generator

%% Parameters
Xboundry = [-15,15];    % mm
Yboundry = [-15,15];    % mm
Ystep = 0.2;    % mm
Speed = 60;     % mm/s

%% Run
array = [];
for y = Yboundry(1):Ystep:Yboundry(2)
    array = [array; [[Xboundry(1),y,0,Speed,-1];[Xboundry(2),y,0,Speed,0]]];
end
disp(array)
disp(size(array))