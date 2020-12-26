figure(1);
data = [144 952 1972 2591 2616 2886 3396 6381 7336 11321 22378 23223 24823 30151 30797 36583 38513 42629];
bar(data);

title("Messages per Person");
xlabel("Name");
ylabel("Messages (Thousands)");


set(gca, 'xtick', 1:18, 'xticklabel', {'Maverick',  'Carson'    , 'Charles'    ,     'Teddy'      ,     'David'       ,    'Lucas'    ,       'Brad'     ,      'Nick' ,  'Nathan'     ,     'Daniel'  ,  'Karl'         ,   'Ethan'          ,     'Lawson'   ,       'Conor'     ,  'Mathieu' 'Noah'  ,          'Evan',           'Peter'});
xtickangle(60);
saveas(gcf, 'plots/carson_total_messages.png');