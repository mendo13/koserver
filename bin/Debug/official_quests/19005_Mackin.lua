
local NPC = 19005;

local MONEY = 0;

if EVENT == 100 then
   MONEY = HowmuchItem(UID, 900000000);
   if MONEY > 1000000 then
      GoldLose(UID, 1000000)
      SelectMsg(UID, 16, -1, NPC);
   else
      EVENT = 160
   end
end

if EVENT == 160 then
   SelectMsg(UID, 2, -1, 11338, NPC, 27);
end