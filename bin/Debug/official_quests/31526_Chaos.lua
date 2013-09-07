local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 31526;

local IsTakeToday = 0;

if EVENT == 100 then
	SelectMsg(UID, 3, -1, 9264, NPC, 7143, 3001, 7139, 3002, 7116, 3003, 7117, 3004, 7149, 3005);
end

if EVENT == 241 then
	Ret = 1;
end

if EVENT == 3001 then
   NpcMsg(UID,31526) -- Guide
end

if EVENT == 3002 then
   IsTakeToday = GetUserDailyOp(UID, 1);
   if IsTakeToday == 1 then
	GiveItem(UID, 910246000, 1);
   else
	SelectMsg(UID, 2, savenum, 9280, NPC, 10, 241);
   end	
   
   return -- Daily Redis.. Map of Chaos
end

if EVENT == 3003 then
   return --810150000 Map of Chaos Exchange Coupon
end

if EVENT == 3004 then
   return -- Reward Wing
end

if EVENT == 3005 then
   return -- 900106000  Voucher of Chaos
end

