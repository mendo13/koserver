local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 14438;
local savenum = -1

if EVENT == 3000 then
   SelectMsg(UID, 3, savenum, 6420, NPC, 4328, 350, 4154, 241);
end

if EVENT == 241 then
   Ret = 1;
end

if EVENT == 350 then
   GetClanRank = CheckKnight(UID)
   if GetClanRank == 3 then -- Accrýted 5
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 360, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end
   
   if GetClanRank == 4 then -- Accrýted 4
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 361, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 5 then -- Accrýted 3
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 362, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 6 then -- Accrýted 2
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 363, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end
   
   if GetClanRank == 7 then -- Accrýted 1
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6407, NPC, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 8 then -- Royal 5
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 364, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 9 then -- Royal 4
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 365, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 10 then -- Royal 3
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 366, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 11 then -- Royal 2
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6410, NPC, 4330, 367, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank == 12 then -- Royal 1
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6409, NPC, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end

   if GetClanRank < 3 then -- Accrýted 5 ten aþaðý bir clan ise
      Leader = isClanLeader(UID)
      if Leader then 
	  SelectMsg(UID, 3, savenum, 6385, NPC, 27, 241);
	  else
	  SelectMsg(UID, 3, savenum, 6384, NPC, 27, 241);
	  end
   end
end

-- CLAN POINTLERE GORE CLANA RUTBE ATLATTIR

if EVENT == 360 then -- Accrýted 4 yapmak için 7k CP
   CP = CheckClanPoint(UID)
   if CP < 252000 then
   SelectMsg(UID, 3, savenum, 6419, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 252000)
   PromoteKnight(UID,4)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 361 then -- Accrýted 3 yapmak için 10k CP
   CP = CheckClanPoint(UID)
   if CP < 360000 then
   SelectMsg(UID, 3, savenum, 6418, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 360000)
   PromoteKnight(UID,5)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 362 then -- Accrýted 2 yapmak için 15k CP
   CP = CheckClanPoint(UID)
   if CP < 540000 then
   SelectMsg(UID, 3, savenum, 6417, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 540000)
   PromoteKnight(UID,6)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 363 then -- Accrýted 1 yapmak için 20k CP
   CP = CheckClanPoint(UID)
   if CP < 720000 then
   SelectMsg(UID, 3, savenum, 6416, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 720000)
   PromoteKnight(UID,7)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 364 then -- Royal 4 yapmak için 30k CP
   CP = CheckClanPoint(UID)
   if CP < 1080000 then
   SelectMsg(UID, 3, savenum, 6415, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 1080000)
   PromoteKnight(UID,9)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 365 then -- Royal 3 yapmak için 35k CP
   CP = CheckClanPoint(UID)
   if CP < 1260000 then
   SelectMsg(UID, 3, savenum, 6414, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 1260000)
   PromoteKnight(UID,10)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 366 then -- Royal 2 yapmak için 40k CP
   CP = CheckClanPoint(UID)
   if CP < 1440000 then
   SelectMsg(UID, 3, savenum, 6413, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 1440000)
   PromoteKnight(UID,11)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end

if EVENT == 367 then -- Royal 1 yapmak için 45k CP
   CP = CheckClanPoint(UID)
   if CP < 1620000 then
   SelectMsg(UID, 3, savenum, 6412, NPC, 27, 241);
   else -- OK
   ShowNpcEffect(UID, 31062)
   RobClanPoint(UID, 1620000)
   PromoteKnight(UID,12)
   SelectMsg(UID, 3 , savenum, 6411, NPC, 27, 241);
   end
end