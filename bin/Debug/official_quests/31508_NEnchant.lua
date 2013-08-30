
local UserClass;
local QuestNum;
local Ret = 0;
local NPC = 31508;


if EVENT == 100 then
	SelectMsg(UID, 3, -1, 242, NPC, 7091, 7099, 7092, 7100, 7093, 7101);
end

if EVENT == 7099 then
	SelectMsg(UID, 3, -1, 242, NPC, 7099, 666);
end

if EVENT == 7100 then
	SelectMsg(UID, 3, -1, 242, NPC, 7099, 667);
end

if EVENT == 7101 then
	SelectMsg(UID, 3, -1, 242, NPC, 7099, 668);
end


if EVENT == 666 then
	CastSkill(UID,302327)
	GoldLose(UID, 50000)
	NpcMsg(UID, 9137)
end

if EVENT == 667 then
	CastSkill(UID,302331)
	GoldLose(UID, 50000)
	NpcMsg(UID, 9137)
end

if EVENT == 668 then
	CastSkill(UID,302328)
	GoldLose(UID, 50000)
	NpcMsg(UID, 9137)
end