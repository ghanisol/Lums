if (homeGoals > awayGoals)
   msgbox(['Home Team Won!' num2str(homeGoals) '-' num2str(awayGoals)]); 
elseif (awayGoals > homeGoals)
   msgbox(['Away Team Won!' num2str(homeGoals) '-' num2str(awayGoals)]);
else
    msgbox(['Its a Draw!' num2str(homeGoals) '-' num2str(awayGoals)]);
end