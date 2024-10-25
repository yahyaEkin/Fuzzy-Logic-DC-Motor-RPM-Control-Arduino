
% Matlab'da örnek bir 61x61'lik array oluşturma
matlabArray = randi([0, 255], 61, 61); % 0 ile 255 arasında rastgele tam sayılar

% Matlab'daki array'i Arduino'da kullanılacak formata dönüştürme
% 2 boyutlu array'i tek boyuta dönüştürme
arduinoArray = reshape(LookUpTableData.', 1, []);

% Dönüştürülmüş array'i Arduino'ya aktarmak için uygun formatta yazdırma
disp('const uint16_t LookUpTable[61][61] PROGMEM = {');
for i = 1:size(matlabArray, 1)
    fprintf('{');
    for j = 1:size(matlabArray, 2)
        fprintf('%d', arduinoArray((i-1)*size(matlabArray, 2) + j));
        if j < size(matlabArray, 2)
            fprintf(', ');
        end
    end
    fprintf('}');
    if i < size(matlabArray, 1)
        fprintf(',\n');
    else
        fprintf('\n};');
    end
end
