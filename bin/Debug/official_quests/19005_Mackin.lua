local NPC = 19005;

if EVENT == 100 then
   MONEY = HowmuchItem(UID, 900000000);
   if MONEY >= 1000000 then
      SelectMsg(UID, 3, -1, 8075, NPC, 4481, 205, 3019, 203);
   else
      SelectMsg(UID, 2, -1, 11338, NPC, 27);
   end
end

if EVENT == 205 then
   GoldLose(UID, 1000000)
   SelectMsg(UID, 16, -1, NPC);
end
