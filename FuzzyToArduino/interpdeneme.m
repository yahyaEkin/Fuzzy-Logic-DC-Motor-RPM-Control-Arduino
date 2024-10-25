input = -815;       %// Örnek input değeri
lookupMin = -820;   %// Lookup table'daki minimum değer
lookupMax = 820;    %// Lookup table'daki maksimum değer
interval = 20;      %// Lookup table'daki aralık

%// Input değerini hangi aralığa yerleştireceğimizi hesaplayın
index = (input - lookupMin) / interval;

%// Lookup table'dan değeri alın
selectedValue = lookupMin + (index * interval);
disp(selectedValue)