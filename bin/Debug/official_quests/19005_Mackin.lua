local NPC = 19005;
local MONEY = 0;

if EVENT == 100 then
   MONEY = HowmuchItem(UID, 900000000);
   if MONEY > 1000000 then
      SelectMsg(UID, 3, -1, 8075, NPC, 4481, 205,3019, 203);
   else
      EVENT = 205
   end
end

if EVENT == 205 then
	SelectMsg(UID, 3, -1, 8082, NPC,4484,206,3019,207);
end

if EVENT == 206 then
   MONEY = HowmuchItem(UID, 900000000);
   if MONEY > 1000000 then
   GoldLose(UID, 10000)
      SelectMsg(UID, 16, -1,NPC);
   else
      EVENT = 206
   end
end
