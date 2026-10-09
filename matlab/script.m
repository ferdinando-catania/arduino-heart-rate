

close all
clear all
clc
%data.mat is from arduino
%the first column contains the milliseconds counted during acquisition

%pulse=data(:,2)    
load pulse.mat
%ecg_1=data(:,3)
load ecg.mat  
load 'position pulse peaks'


%% Acquisition data directly from matlab using arduino (extra)

% https://www.mathworks.com/help/supportpkg/arduinoio/
% a=arduino('COM10','uno') %to upload arduino 

%%%%%%%%%%%%%%%%%%%%%%%%%% read analog values from arduino %%%%%%%%%%%%%%%%

%tic
% for i=1:500                        
%     pulse(i)=readVoltage(a,'A0');
%     
% end
%toc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% plot pulse data (data from the sensor 'KY-039')

%we calculated the frequency dividing the number of the samples by
%the time of acquisition: f=1000/18.701= 53.47Hz
% oss: We used the same frequency for ecg and pulse data

fs_ecg=53.47; %sampling frequency ecg 
samples=0:1/fs_ecg:20; %to pass from samples to sec 
samples=samples(1:1000);
pulse=pulse(1:1000);
pulse=pulse.*(5/1023);  %to pass in volts
figure (1) 
subplot(2,1,1)
plot(samples,pulse)
title('PULSE data');
xlabel('time of acquisition (sec)');
ylabel('voltage (V)');
xlim([0 18.8])
ylim([3.66 3.8])
 % We used the ginput function to calculate the position of the peaks
 % then we saved it in the file.mat
% [x,y] = ginput(22);   
% hold on
% plot(x,y,'*')

%% plot ecg data (data from the kit 'AD-8232')

ecg_1=ecg_1(1:1000);
ecg_1=ecg_1.*(5/1023);
subplot(2,1,2) 
plot(samples,ecg_1)
title('ECG data');
xlabel('time of acquisition (sec)');
xlim([0 18.8])
ylabel('voltage (V)');


%% Algorithm to calculate the heart rate from ecg

pause()
hold on 
k1=find(ecg_1>1.9); %k is a vector where its elemetns are the index of the elements of Y1 which are greater than 1.9
k2=diff(k1); %k2 is the difference vector of K1, it's=  K1-1
kf=find(k2>10); %kf is a vector whose elements are the positions of K2 values greater than 20
ki=[k1(kf+1)]; %k1(1) contains the position of the first value above threshold 
plot(samples(ki),ecg_1(ki),'r*')
legend('ecg','spikes')

nc=fs_ecg*0.03; % where 0.03 sec is the duration interval of an R wave, nc=num samples*duration
m =zeros(length(ki),1); 
for i=1:length(ki)
    [y,j]=max(ecg_1(ki(i):ki(i)+nc-1));        
    m(i,1)=j+ki(i)-1;
    
end


rrc=diff(m); % distance in samples between peaks R in this way we obtained the R-R differences in samples.
% Then we converted them into seconds
rrs=rrc*0.004;

fhr_ecg=60./rrs; %%60= 1 min --> beats per minute (BPM)

n_spikes=length(m)-1;
fhr_ecg(1:n_spikes);
rrc=diff(m);
rrs=rrc/fs_ecg;
fhr_ecg=60./rrs;
fhr_ecg(1:n_spikes);


pause()
figure(3)

%% Algorithm to calculate the heart rate from pulse

for a=1:21
     
     fhr_pulse(a)=60./(x(a+1)-x(a)); 
     
end
 
fhr_pulse(:,15) = [ ];  %we deleted the 15' and 21' columns beacause there are Infinities
fhr_pulse(:,20) = [ ];
%% PLOT RESULTS

plot(fhr_ecg,'o')
hold on
plot(fhr_pulse,'*')
title('HEART BEAT (beats per minute)');
xlabel('num. beats examined');
ylabel('val. beats examined');
legend('ecg HR','pulse HR')
fhr_ecg(7,:) = [ ]; %we deleted a 'outlier' from the data


rms(fhr_pulse)
rms(fhr_ecg)

fhr_pulse=fhr_pulse';


fhr_pulse=fhr_pulse-mean(fhr_pulse);
var(fhr_pulse)


fhr_ecg=fhr_ecg-mean(fhr_ecg);
var(fhr_ecg)





