/*
EventNum 1011 Karusu Temsil Eder.
EventNum 1012 Humanı Temsil Eder.
Cond1/Cond2 X Koordinatını Temsil Eder.
Cond3/Cond4 Z Koordinatını Temsil Eder.
Exec1 : Işınlanacak Zoneyi Temsil Eder
Exec2 : Işınlanacak Zonenin X Koordinatını Temsil Eder.
Exec3 : Işınlanacak Zonenin Y Koordinatını Temsil Eder.
*/
DELETE FROM EVENT WHERE ZoneNum = 62
INSERT INTO EVENT VALUES (62,1011,1,847,858,962,965,0,2,219,1859,0,0)
INSERT INTO EVENT VALUES (62,1012,1,197,205,39,48,0,1,1859,170,0,0)
/*
Sadece 62 Zonesi İçin Örnek Yapılmıştır...
*/
DELETE FROM QUEST_HELPER WHERE sNpcId = 10510
DELETE FROM QUEST_HELPER WHERE sNpcId = 20510
INSERT INTO QUEST_HELPER VALUES ((SELECT TOP 1 nIndex FROM QUEST_HELPER ORDER BY nIndex DESC) + 1,2,1,0,5,2,1,62,10510,0,0,100,0,0,0,'10510_Victory.lua')
INSERT INTO QUEST_HELPER VALUES ((SELECT TOP 1 nIndex FROM QUEST_HELPER ORDER BY nIndex DESC) + 1,2,1,0,5,1,1,62,20510,0,0,100,0,0,0,'20510_Victory.lua')