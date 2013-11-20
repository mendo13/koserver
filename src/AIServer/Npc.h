#pragma once

#include "NpcTable.h"
#include "NpcMagicProcess.h"

#define MAX_PATH_SIZE		100

#define NPC_MAX_USER_LIST	5

#define NPC_ATTACK_SHOUT	0
#define NPC_SUBTYPE_LONG_MON 1

#define NPC_TRACING_STEP	100

#define NPC_HAVE_USER_LIST	5
#define NPC_HAVE_ITEM_LIST	6
#define NPC_PATTEN_LIST		5
#define NPC_PATH_LIST		50
#define NPC_MAX_PATH_LIST	100
#define NPC_EXP_RANGE		50
#define NPC_EXP_PERSENT		50

#define NPC_SECFORMETER_MOVE	4
#define NPC_SECFORMETER_RUN		4
#define NPC_VIEW_RANGE			100

#define MAX_MAGIC_TYPE3			20
#define MAX_MAGIC_TYPE4			9

struct  _NpcSkillList
{
	short	sSid;
	uint8	tLevel;
	uint8	tOnOff;
};

struct  _NpcGiveItem
{
	int 	sSid;			// item serial number
	short	count;			// item ����(���� ����)
};

struct _Target
{
	uint16	id;							// ���ݴ��� User uid
	bool bSet;
	float x;						// User�� x pos
	float y;						// User�� y pos
	float z;						// User�� z pos
};

struct _PattenPos
{
	short x;
	short z;
};

struct _PathList
{
	_PattenPos pPattenPos[NPC_MAX_PATH_LIST];
};

struct _TargetHealer
{
	short	sNID;				// npc nid
	short	sValue;				// ����
};

class MAP;

#include "../GameServer/Unit.h"

enum MonSearchType
{
	MonSearchSameFamily,	// find any available mobs of the same family
	MonSearchAny,			// find any available mob
	MonSearchNeedsHealing	// find any mob that needs healing
};

enum CloseTargetResult
{
	CloseTargetInvalid,
	CloseTargetNotInRange,
	CloseTargetInGeneralRange,
	CloseTargetInAttackRange
};

enum NpcSpecialType
{
	NpcSpecialTypeNone				= 0,
	NpcSpecialTypeCycleSpawn		= 7,
	NpcSpecialTypeKarusWarder1		= 90,
	NpcSpecialTypeKarusWarder2		= 91,
	NpcSpecialTypeElmoradWarder1	= 92,
	NpcSpecialTypeElmoradWarder2	= 93,
	NpcSpecialTypeKarusKeeper		= 98,
	NpcSpecialTypeElmoradKeeper		= 99
};

struct __Vector3;
class CNpc : public Unit
{
public:
	uint16 GetID() { return m_sNid; }
	INLINE uint16 GetProtoID() { return GetProto()->m_sSid; }
	std::string & GetName() { return GetProto()->m_strName; }

	int32 GetHealth() { return m_iHP; }
	int32 GetMaxHealth() { return GetProto()->m_iMaxHP; }
	int32 GetMana() { return m_sMP; }
	int32 GetMaxMana() { return GetProto()->m_sMaxMP; }

	void GetInOut(Packet &, uint8) {}
	void AddToRegion(int16 sRegionX, int16 sRegionZ) {}

	void HpChange(int amount, Unit *pAttacker = nullptr, bool bSendToGameServer = true);
	void MSpChange(int amount) {}

	INLINE CNpcTable * GetProto() { return m_proto; }
	INLINE uint8 GetType() { return GetProto()->m_tNpcType; }

	INLINE bool isHealer() { return GetType() == NPC_HEALER; } 

	INLINE bool isGuard()
	{
		return GetType() == NPC_GUARD || GetType() == NPC_PATROL_GUARD || GetType() == NPC_STORE_GUARD;
	}

	INLINE bool isGate() 
	{
		return GetType() == NPC_GATE 
			|| GetType() == NPC_PHOENIX_GATE 
			|| GetType() == NPC_SPECIAL_GATE 
			|| GetType() == NPC_VICTORY_GATE; 
	}

	INLINE bool isArtifact() 
	{ 
		return GetType() == NPC_ARTIFACT 
			|| GetType() == NPC_DESTROYED_ARTIFACT 
			|| GetType() == NPC_ARTIFACT1 
			|| GetType() == NPC_ARTIFACT2 
			|| GetType() == NPC_ARTIFACT3 
			|| GetType() == NPC_ARTIFACT4; 
	}

	INLINE bool isNonAttackingObject() { return isGate() || GetType() == NPC_GATE_LEVER || isArtifact() || GetType() == NPC_SCARECROW || GetType() == NPC_GATE2; }
	INLINE bool isNonAttackableObject() { return isGate() || GetType() == NPC_GATE_LEVER; }

	INLINE bool isDead() { return m_NpcState == NPC_DEAD || m_iHP <= 0; }
	INLINE bool isAlive() { return !isDead(); }
	INLINE bool isMonster() { return m_bMonster; }

	INLINE bool hasTarget() { return m_Target.bSet; }

	CNpcTable *m_proto;

	_Target	m_Target;				// ������ ���� ����,,
	short		m_ItemUserLevel;		// ������ ���� �̻� �����۸� ���������� �����ؾ��ϴ� �����Ƿ���

	std::map<uint16, uint32> m_DamagedUserList; // max NPC_HAVE_USER_LIST?
	FastMutex m_damageListLock;

	int		m_TotalDamage;
	short   m_sMaxDamageUserid;		// ������ �ְ��� �������� �� ������ ���̵� ����..

	_PathList m_PathList;			// Npc�� �н� ����Ʈ 
	_PattenPos m_pPattenPos;		// Npc�� ����,,

	//int m_iPattenNumber;		// ������ ���Ϲ�ȣ
	short m_iPattenFrame;			// ������ ���� ��ġ..

	uint8 m_byMoveType;			// NPC�� �ൿŸ��(�̵�����)
	uint8 m_byInitMoveType;		// NPC�� �ʱ� �ൿŸ��(�̵�����)
	short m_sPathCount;			// NPC�� PathList Count
	short m_sMaxPathCount;		// NPC�� PathList Max Count

	bool	m_bFirstLive;		// NPC �� ó�� �����Ǵ��� �׾��� ���Ƴ����� �Ǵ�.
	uint8	m_OldNpcState, m_NpcState;

	short	m_sNid;

	float		m_nInitX;			// ó�� ������ ��ġ X
	float		m_nInitY;			// ó�� ������ ��ġ Y
	float		m_nInitZ;			// ó�� ������ ��ġ Z

	float		m_fPrevX;			// Prev X Pos;
	float		m_fPrevY;			// Prev Y Pos;
	float		m_fPrevZ;			// Prev Z Pos;

	//
	//	PathFind Info
	//
	short		m_min_x;
	short		m_min_y;
	short		m_max_x;
	short		m_max_y;

	typedef struct { long cx; long cy; } Size;
	Size	m_vMapSize;

	float m_fStartPoint_X, m_fStartPoint_Y;
	float m_fEndPoint_X, m_fEndPoint_Y;

	short m_sStepCount;

	CPathFind m_vPathFind;
	_PathNode	*m_pPath;

	int		m_nInitMinX;					// �ʱ���ġ
	int		m_nInitMinY;
	int		m_nInitMaxX;
	int		m_nInitMaxY;

	time_t	m_fHPChangeTime;
	time_t	m_tFaintingTime;

	//----------------------------------------------------------------
	//	MONSTER DB �ʿ� �ִ� ������
	//----------------------------------------------------------------
	short   m_sSize;						// ĳ������ ����(100 �ۼ�Ʈ ����)
	int     m_iWeapon_1;			// ���� ����
	int     m_iWeapon_2;			// ���� ����
	uint8	m_byActType;		// �ൿ����
	uint8	m_byRank;			// ����
	uint8	m_byTitle;			// ����
	int 	m_iSellingGroup;	// ������ �׷�(���ǸŸ� ���� NPC�� ���츸)
	int		m_iMaxHP;			// �ִ� HP
	short	m_sMaxMP;			// �ִ� MP
	short	m_sAttack;			// ���ݰ�(���� �������� ����..)
	short	m_sAttackDelay;		// ���ݵ�����
	short	m_sSpeed;			// �̵��ӵ�	
	float   m_fSpeed_1;			// �⺻ �̵� Ÿ��		(1�ʿ� �� �� �ִ� �Ÿ�)
	float   m_fSpeed_2;			// �ٴ� �̵� Ÿ��..		(1�ʿ� �� �� �ִ� �Ÿ�)
	short	m_sStandTime;		// ���ִ� �ð�

	uint8	m_bySearchRange;	// �� Ž�� ����
	uint8	m_byAttackRange;	// �����Ÿ�
	uint8	m_byTracingRange;	// �߰� �Ÿ�

	int		m_iMoney;			// �������� ��
	int		m_iItem;			// �������� ������

	int			m_iHP;				// ���� HP
	short		m_sMP;				// ���� MP

	float   m_fSecForMetor;		// �ʴ� �� �� �ִ� �Ÿ�..

	//----------------------------------------------------------------
	//	MONSTER AI�� ���õ� ������
	//----------------------------------------------------------------
	uint8	m_tNpcAttType;		// ���� ���� : ����(1), �İ�(0)
	bool	m_bHasFriends;		// When set, monsters behave in groups (defined by their family type) and will seek out help from nearby similar mobs.
	uint8	m_byAttackPos;		// User�� ���� �κп��� �����ϴ����� �Ǵ�(8����)
	uint8	m_byBattlePos;		// � ������ ������ �������� �Ǵ�..
	bool	m_byGateOpen;		// ������ ���쿡.. ����... Gate Npc Status -> 1 : open 0 : close
	uint8	m_byMaxDamagedNation;	// ���� ���� ������ ������ ����.. (1:ī�罺, 2:��������)
	uint8	m_byObjectType;         // ������ 0, objectŸ��(����, ����)�� 1
	uint8	m_byDungeonFamily;		// �������� ���� �йи� ���� (���� ��)
	NpcSpecialType	m_bySpecialType;		// �������� ���°� ���ϴ����� �Ǵ�(0:������ ����, 1:���ϴ� ������, 
	// 2:�״°��� �����ϴ� ������(���������� �������� ������ ����), 
	// 3:������������ ������ ������ �ִ� ������(���������Ͱ� ������ �����Ǵ� �����ʹ� ���� �׵���)
	// 4:���ϸ鼭 �״°��� �����ϴ� ������ (m_sControlSid)
	// 5:ó���� �׾��ִٰ� �����ϴ� ������,,
	// 6:�����ð��� ���� �Ŀ� �ൿ�ϴ� ������,,
	// 100:�׾����� �������� ���� ���� ������ ������ �ּ���
	uint8	m_byTrapNumber;			// �������� Ʈ���� ��ȣ,,
	uint8	m_byChangeType;			// 0:��������, 1:���ϱ� ���� �غ�, 2:�ٸ������ͷ� ����, 3:�������� ����, 100:�������� ����
	uint8	m_byRegenType;			// 0:���������� ������ ��.. , 1:�ѹ� ������ ������ �ȵǴ� Ư�� ��, 2:������ �ȵ�
	uint8    m_byDeadType;			// 0:���� �ִ� ����, 100:�����̺�Ʈ�� ���� ����


	//----------------------------------------------------------------
	//	MONSTER_POS DB �ʿ� �ִ� ������
	//----------------------------------------------------------------
	time_t	m_Delay;			// this doesn't really need to be time_t, but we'll use it (at least for now) for consistency
	time_t	m_fDelayTime;		// Npc Threadüũ Ÿ��...

	uint8	m_byType;
	int		m_sRegenTime;		// NPC �����ð�

	uint8	m_byDirection;

	int		m_nLimitMinX;		// Ȱ�� ����
	int		m_nLimitMinZ;
	int		m_nLimitMaxX;
	int		m_nLimitMaxZ;

	bool	m_bIsEventNpc;

	float m_fAdd_x;
	float m_fAdd_z;

	float m_fBattlePos_x;	
	float m_fBattlePos_z;

	float m_fSecForRealMoveMetor;		// �ʴ� �� �� �ִ� �Ÿ�..(���� Ŭ���̾�Ʈ�� �����ִ� �Ÿ�)

	bool m_bPathFlag;					// �н� ���ε� ���࿩�� üũ ����..

	//----------------------------------------------------------------
	//	NPC �̵� ����
	//----------------------------------------------------------------
	_NpcPosition	m_pPoint[MAX_PATH_LINE];			// �̵��� ���� ��ǥ

	short m_iAniFrameIndex;
	short m_iAniFrameCount;
	uint8 m_byPathCount;					// �н��� ���� �̵��ϴ� ������ ���� ��ġ�� �ʵ���,, 
	bool m_bStopFollowingTarget;		// when set, indicates that an NPC should stop following its target
	uint8 m_byActionFlag;				// �ൿ��ȭ �÷��� ( 0 : �ൿ��ȭ ����, 1 : ���ݿ��� �߰�)

	bool m_bTracing;
	float m_fTracingStartX, m_fTracingStartZ;

	short m_iFind_X[4];					// find enemy���� ã�� Region�˻翵��
	short m_iFind_Y[4];

	float   m_fOldSpeed_1;			// �⺻ �̵� Ÿ��		(1�ʿ� �� �� �ִ� �Ÿ�)
	float   m_fOldSpeed_2;			// �ٴ� �̵� Ÿ��..		(1�ʿ� �� �� �ִ� �Ÿ�)

	bool	m_bMonster;

	uint32	m_nActiveSkillID;		// ID of skill currently being cast
	int16	m_sActiveTargetID;		// ID of the target of the skill currently being cast
	uint16	m_sActiveCastTime;		// Cast time of the skill currently being cast (in seconds)

	bool	m_bDelete; // when set, will remove the NPC from the server after execution.

public:
	CNpc();
	virtual ~CNpc();

	void Init();	//	NPC �⺻���� �ʱ�ȭ
	void InitTarget(void);
	void InitUserList();
	void InitPos();

	void Load(uint16 sNpcID, CNpcTable * proto, bool bMonster);
	void SendMoveResult(float fX, float fY, float fZ, float fSpeed = 0.0f);

protected:
	void ClearPathFindData(void);

public:

	void FillNpcInfo(Packet & result);
	void NpcStrategy(uint8 type);
	int  FindFriend(MonSearchType type = MonSearchSameFamily);
	void  FindFriendRegion(int x, int z, MAP* pMap, _TargetHealer* pHealer, MonSearchType type = MonSearchSameFamily);
	bool IsCloseTarget(CUser *pUser, int nRange);
	void SendExpToUserList();
	void RecvAttackReq(int nDamage, uint16 sAttackerID, AttributeType attributeType = AttributeNone);
	void ChangeTarget(int nAttackType, CUser *pUser);
	void ChangeNTarget(CNpc *pNpc);
	bool ResetPath();
	bool GetTargetPos(float& x, float& z);
	bool IsChangePath();
	time_t Attack();
	time_t LongAndMagicAttack();
	void TracingAttack();
	int GetTargetPath(int option = 0);
	CloseTargetResult IsCloseTarget(int nRange, AttackType attackType);
	bool StepMove();
	bool StepNoPathMove();
	bool IsMovingEnd();
	int  IsSurround(CUser* pUser);
	bool IsDamagedUserList(CUser *pUser);
	bool IsPathFindCheck(float fDistance);
	void IsNoPathFind(float fDistance);
	void GiveNpcHaveItem();

	time_t NpcLive();
	time_t NpcTracing();
	time_t NpcAttacking();
	time_t NpcMoving();
	time_t NpcSleeping();
	time_t NpcFainting();
	time_t NpcHealing();
	time_t NpcCasting();
	time_t NpcStanding();
	time_t NpcBack();
	bool SetLive();

	bool isInSpawnRange(int nX, int nZ);
	bool RandomMove();
	bool RandomBackMove();
	bool IsInPathRange();
	int GetNearPathPoint();

	short GetDamage(Unit *pTarget, _MAGIC_TABLE *pSkill = nullptr, bool bPreviewOnly = false);
	short GetDamage(CUser *pTarget, _MAGIC_TABLE *pSkill = nullptr, bool bPreviewOnly = false);
	short GetDamage(CNpc *pTarget, _MAGIC_TABLE *pSkill = nullptr, bool bPreviewOnly = false);

	void SendAttackRequest(int16 tid);

	bool RegisterRegion(float x, float z);
	void SendInOut(InOutType type);
	void SendNpcInfo();
	void SendRegionUpdate();
	void Dead(Unit * pKiller = nullptr, bool bSendDeathPacket = true);
	bool isShowBox();

	bool FindEnemy();
	bool CheckFindEnemy();
	int FindEnemyRegion();
	float FindEnemyExpand(int nRX, int nRZ, float fCompDis, UnitType unitType);
	int GetMyField();

	int GetDir(float x1, float z1, float x2, float z2);
	void NpcMoveEnd();

	void GetVectorPosition(__Vector3 & vOrig, __Vector3 & vDest, float fDis, __Vector3 * vResult);
	void CalcAdaptivePosition(__Vector3 & vPosOrig, __Vector3 & vPosDest, float fAttackDistance, __Vector3 * vResult);
	void ComputeDestPos(__Vector3 & vCur, float fDegree, float fDistance, __Vector3 * vResult);
	void Yaw2D(float fDirX, float fDirZ, float& fYawResult);
	float GetDistance(__Vector3 & vOrig, __Vector3 & vDest);
	int  PathFind(CPoint start, CPoint end, float fDistance);
	bool GetUserInView();
	bool GetUserInViewRange(int x, int z);
	void MoveAttack();
	void HpChange();
	int	 ItemProdution(int item_number);
	int  GetItemGrade(int item_grade);
	int  GetItemCodeNumber(int level, int item_type);
	int  GetWeaponItemCodeNumber(bool bWeapon);
	int  GetPartyExp( int party_level, int man, int nNpcExp );
	void ChangeAbility(int iChangeType);
	bool Teleport();

	bool isHostileTo(Unit * pTarget);
};
