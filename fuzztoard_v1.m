clear all;
fis = readfis('Mamdan3');

% Define input variables
E = -600:20:600; %RPM ERROR
CE = -600:20:600; % CHANGE OF RPM ERROR
N = length(E);
LookUpTableData = zeros(N);

% Compute output values for each combination of input samples
for i = 1:N
    for j = 1:N
        LookUpTableData(i,j) = evalfis(fis,[E(i) CE(j)]);
    end
end

%LookUpTableData = LookUpTableData;
LookUpTableData = round(LookUpTableData);
