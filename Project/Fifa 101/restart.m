restartHomePlayers;
restartAwayPlayers;
resetFootball;
poss = 0;
key = 1;


% Reset Camera %
camproj('perspective');
campos('manual');
camtarget('auto');
camtarget([0 0 0]);
set(gca,'CameraPosition',[0 100 90]);
% Reset Camera %