IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'USER_DAILY_OP')
    DROP TABLE USER_DAILY_OP;
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'INSERT_USER_DAILY_OP') AND type in (N'P', N'PC'))
    DROP PROCEDURE INSERT_USER_DAILY_OP;
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'UPDATE_USER_DAILY_OP') AND type in (N'P', N'PC'))
    DROP PROCEDURE UPDATE_USER_DAILY_OP;
GO

CREATE TABLE USER_DAILY_OP (
	[strUserId] [char](21) NULL,
	[ChaosMapTime] [int] NULL,
	[UserRankRewardTime] [int] NULL,
	[PersonalRankRewardTime] [int] NULL,
	[KingWingTime] [int] NULL
) ON [PRIMARY]

GO

CREATE PROCEDURE INSERT_USER_DAILY_OP
@strUserId char(21),
@ChaosTime int,
@UserRankRewardTime int,
@UserPersonalRankRewardTime int,
@KingWingTime int
AS

DELETE FROM USER_DAILY_OP WHERE strUserId = @strUserId
INSERT INTO USER_DAILY_OP VALUES (@strUserId,@ChaosTime,@UserRankRewardTime,@UserPersonalRankRewardTime,@KingWingTime)
GO

CREATE PROCEDURE UPDATE_USER_DAILY_OP
@strUserId char(21),
@Type int,
@UnixTime int
AS

IF @Type = 1
	UPDATE USER_DAILY_OP SET ChaosMapTime = @UnixTime WHERE strUserId = @strUserId
ELSE IF @Type = 2
	UPDATE USER_DAILY_OP SET UserRankRewardTime = @UnixTime WHERE strUserId = @strUserId
ELSE IF @Type = 3
	UPDATE USER_DAILY_OP SET PersonalRankRewardTime = @UnixTime WHERE strUserId = @strUserId
ELSE IF @Type = 4
	UPDATE USER_DAILY_OP SET KingWingTime = @UnixTime WHERE strUserId = @strUserId
GO