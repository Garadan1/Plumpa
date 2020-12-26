% MATLAB - preliminaryResults.txt plotting script
% This script sucks because you have to manually insert data
% It also sucks because it's ugly, but I don't like MATLAB so I don't care
% enough to fix it
% Hopefully these graphs will allow us to catch errors in the code.
figure(6);
data = [15619	95334	90651	72456];
bar(data/1000);
title("Messages per Year (as of Dec. 2020)");
xlabel("Year");
ylabel("Messages (Thousand)");
axis([0 5 0 100]);
set(gca, 'xtick', 1:4, 'xticklabel', {'2017','2018','2019','2020'});
saveas(gcf, 'plots/messages_per_year.png');


figure(1);
data = [16.622	20.853	22.971	24.832	20.994	25.108	23.866	19.171	23.887	28.403	22.621	24.732];
bar(data);
title("Messages per Month of Year");
xlabel("Month");
ylabel("Messages (Thousand)");
axis([0 13 0 30]);
set(gca, 'xtick', 1:12, 'xticklabel', {'Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'});
saveas(gcf, 'plots/messages_per_month_of_year.png');

figure(2); 
data = [8566	8977	11500	9672	8935	10557	9397	9184	12750	10693	7167	9045	8317	8201	8522	8100	10314	8953	8142	9492	6937	9395	8657	8325	11612	7984	8759	7767	7379	7037	3724];
bar(data/1000);
title("Messages per Day of Month");
xlabel("Day");
ylabel("Messages (Thousand)");
axis([0 32 0 13]);
saveas(gcf, 'plots/messages_per_day_of_month.png');

figure(3);
data = [12377	10660	5947	3142	2009	1574	1035	1437	1370	2984	4346	7070	15201	13607	15447	18561	21603	20148	23233	20644	18232	18214	16004	19215];
bar(data/1000);
title("Messages per Hour of Day");
xlabel("Hour");
ylabel("Messages (Thousand)");
axis([0 25 0 24]);
saveas(gcf, 'plots/messages_per_hour_of_day.png');

figure(4);
%Note manual shift to 0-index - messages on the hour are the last bar
data = [4776	4833	4651	4623	4582	4645	4727	4881	4636	4556	4573	4729	4511	4676	4740	4733	4665	4700	4730	4646	4535	4567	4662	4690	4543	4636	4443	4402	4372	4559	4623	4334	4282	4534	4474	4686	4575	4480	4630	4334	4544	4619	4534	4344	4381	4455	4416	4445	4306	4277	4445	4497	4453	4630	4499	4487	4561	4452	4696 5045	];
bar(data/1000);
title("Messages per Minute of Hour");
xlabel("Minute");
ylabel("Messages (Thousand)");
axis([0 61 0 6]);
saveas(gcf, 'plots/messages_per_minute_of_hour.png');

figure(5);
%Note manual shift to 0-index - messages on the minute are the last bar
data = [4671	4557	4576	4502	4568	4628	4450	4522	4647	4588	4518	4588	4587	4520	4607	4532	4492	4558	4731	4452	4521	4565	4549	4631	4475	4565	4734	4455	4507	4465	4590	4525	4543	4556	4642	4707	4534	4557	4455	4626	4568	4614	4533	4626	4568	4583	4546	4615	4546	4633	4466	4585	4719	4587	4612	4571	4516	4649	4560	4467];
bar(data/1000);
title("Messages per Second of Minute");
xlabel("Second");
ylabel("Messages (Thousand)");
axis([0 61 0 5]);
saveas(gcf, 'plots/messages_per_second_of_minute.png');