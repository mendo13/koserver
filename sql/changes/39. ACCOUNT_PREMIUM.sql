IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'ACCOUNT_PREMIUM') AND type in (N'P', N'PC'))
    DROP PROCEDURE ACCOUNT_PREMIUM;
GO

CREATE PROCEDURE ACCOUNT_PREMIUM
@AccountID varchar(21),
@nRet smallint OUTPUT
AS

DECLARE @Hours datetime

SELECT @Hours = PremiumEndDate FROM TB_USER WHERE strAccountID = @AccountID

SET @nRet = DATEDIFF(HH,GETDATE(),@Hours)

IF @nRet <= 0
	SET @nRet = -1

RETURN
GO