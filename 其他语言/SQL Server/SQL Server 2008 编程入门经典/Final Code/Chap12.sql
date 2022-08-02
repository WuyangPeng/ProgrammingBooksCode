USE AdventureWorks2008

GO
CREATE PROC spEmployee
AS
   SELECT * FROM HumanResources.Employee;

EXEC spEmployee;

USE AdventureWorks2008;

GO

CREATE PROC spEmployeeByName
    @LastName  nvarchar(50)
AS

SELECT p.LastName, p.FirstName, e.JobTitle, e.HireDate
FROM Person.Person p
JOIN HumanResources.Employee e
    ON p. BusinessEntityID = e.BusinessEntityID
WHERE p.LastName LIKE @LastName + '%';


EXEC spEmployeeByName 'Dobney';


USE AdventureWorks2008;

DROP PROC spEmployeeByName; -- Get rid of the previous version
GO
CREATE PROC spEmployeeByName
@LastName nvarchar(50) = NULL
AS
IF @LastName IS NOT NULL
    SELECT p.LastName, p.FirstName, e.JobTitle, e.HireDate
    FROM Person.Person p
    JOIN HumanResources.Employee e
        ON p.BusinessEntityID = e.BusinessEntityID
    WHERE p.LastName LIKE @LastName + '%';
ELSE
    SELECT p.LastName, p.FirstName, e.JobTitle, e.HireDate
    FROM Person.Person p
    JOIN HumanResources.Employee e
        ON p.BusinessEntityID = e.BusinessEntityID;


EXEC spEmployeeByName;


USE AdventureWorks2008;

BEGIN TRY
-- Try and create our table
CREATE TABLE OurIFTest(
    Col1    int     PRIMARY KEY
    )
END TRY
BEGIN CATCH
    -- Uh oh, something went wrong, see if it's something
    -- we know what to do with
    DECLARE @MyOutputParameter int;

    IF ERROR_NUMBER() = 2714 -- Object exists error, we knew this might happen
    BEGIN
        PRINT 'WARNING: Skipping CREATE as table already exists';
        EXEC dbo.uspLogError @ErrorLogID = @MyOutputParameter OUTPUT;
        PRINT 'A error was logged. The Log ID for our error was ' 
                + CAST(@MyOutputParameter AS varchar);
    END
    ELSE    -- hmm, we don't recognize it, so report it and bail
        RAISERROR('something not good happened this time around', 16, 1 );
END CATCH


SELECT * 
FROM ErrorLog
WHERE ErrorLogID = 3; -- change this value to whatever your 
                     -- results said it was logged as

USE AdventureWorks2008;
GO

CREATE PROC spTestReturns
AS
   DECLARE @MyMessage        varchar(50);
   DECLARE @MyOtherMessage   varchar(50);

   SELECT @MyMessage = 'Hi, it''s that line before the RETURN';
   PRINT @MyMessage;
   RETURN;
   SELECT @MyOtherMessage = 'Sorry, but we won''t get this far';
   PRINT @MyOtherMessage;
RETURN;

EXEC @ReturnVal = spMySproc;

DECLARE @Return int;

EXEC @Return = spTestReturns;
SELECT @Return;


USE AdventureWorks2008;
GO

ALTER PROC spTestReturns
AS
   DECLARE @MyMessage        varchar(50);
   DECLARE @MyOtherMessage   varchar(50);

   SELECT @MyMessage = 'Hi, it''s that line before the RETURN';
   PRINT @MyMessage
   RETURN 100;
   SELECT @MyOtherMessage = 'Sorry, but we won''t get this far';
   PRINT @MyOtherMessage;
RETURN;

USE AdventureWorks2008;
GO

INSERT INTO Person.BusinessEntityContact
           (BusinessEntityID
           ,PersonID
           ,ContactTypeID)
     VALUES
           (0,0,1);


USE AdventureWorks2008;
GO

DECLARE   @Error   int;

-- Bogus INSERT - there is no PersonID or BusinessEntityID of 0. Either of 
-- these could cause the error we see when running this statement.
INSERT INTO Person.BusinessEntityContact
           (BusinessEntityID
           ,PersonID
           ,ContactTypeID)
     VALUES
           (0,0,1);

-- Move our error code into safekeeping. Note that, after this statement,
-- @@Error will be reset to whatever error number applies to this statement
SELECT @Error = @@ERROR;

-- Print out a blank separator line
PRINT '';

-- The value of our holding variable is just what we would expect
PRINT 'The Value of @Error is ' + CONVERT(varchar, @Error);

-- The value of @@ERROR has been reset - it's back to zero
-- since our last statement (the PRINT) didn't have an error.
PRINT 'The Value of @@ERROR is ' + CONVERT(varchar, @@ERROR);


USE AdventureWorks2008;
GO

INSERT INTO Person.BusinessEntityContact
           (BusinessEntityID
           ,PersonID
           ,ContactTypeID)
     VALUES(0,0,1);

USE AdventureWorks2008
GO

CREATE PROC spInsertValidatedBusinessEntityContact
    @BusinessEntityID int,
    @PersonID int,
    @ContactTypeID int
AS
BEGIN

    DECLARE @Error int;

    INSERT INTO Person.BusinessEntityContact
           (BusinessEntityID
           ,PersonID
           ,ContactTypeID)
    VALUES
        (@BusinessEntityID, @PersonID, @ContactTypeID);

    SET @Error = @@ERROR;

    IF @Error = 0
        PRINT 'New Record Inserted';
    ELSE
    BEGIN
        IF @Error = 547 -- Foreign Key violation. Tell them about it.
            PRINT 'At least one provided parameter was not found. Correct and retry';
        ELSE -- something unknown
            PRINT 'Unknown error occurred. Please contact your system admin';
    END
END

EXEC spInsertValidatedBusinessEntityContact 1, 1, 11;


BEGIN TRY
    -- Try and create our table
    CREATE TABLE OurIFTest(
        Col1    int        PRIMARY KEY
        )
END TRY
BEGIN CATCH
    -- Uh oh, something went wrong, see if it's something
    -- we know what to do with
    DECLARE @ErrorNo    int,
            @Severity    tinyint,
            @State        smallint,
            @LineNo        int,
            @Message    nvarchar(4000);
    SELECT 
        @ErrorNo = ERROR_NUMBER(),
        @Severity = ERROR_SEVERITY(),
        @State = ERROR_STATE(),
        @LineNo = ERROR_LINE (),
        @Message = ERROR_MESSAGE();

    IF @ErrorNo = 2714 -- Object exists error, we knew this might happen
        PRINT 'WARNING: Skipping CREATE as table already exists';
    ELSE -- hmm, we don't recognize it, so report it and bail
        RAISERROR(@Message, 16, 1 );
END CATCH


CREATE TABLE OurIFTest(
    Col1    int        PRIMARY KEY
    );
IF @@ERROR != 0
    PRINT 'Problems!';
ELSE
    PRINT 'Everything went OK!';


CREATE PROCEDURE HumanResources.uspUpdateEmployeeHireInfo2
    @BusinessEntityID int, 
    @JobTitle nvarchar(50), 
    @HireDate datetime, 
    @RateChangeDate datetime, 
    @Rate money, 
    @PayFrequency tinyint, 
    @CurrentFlag dbo.Flag 
WITH EXECUTE AS CALLER
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        UPDATE HumanResources.Employee 
        SET JobTitle = @JobTitle, 
            HireDate = @HireDate, 
            CurrentFlag = @CurrentFlag 
        WHERE BusinessEntityID = @BusinessEntityID;

        INSERT INTO HumanResources.EmployeePayHistory
            (BusinessEntityID,
             RateChangeDate,
             Rate,
             PayFrequency) 
        VALUES (@BusinessEntityID, @RateChangeDate, @Rate, @PayFrequency);

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        -- Rollback any active or uncommittable transactions before
        -- inserting information in the ErrorLog
        IF @@TRANCOUNT > 0
        BEGIN
            ROLLBACK TRANSACTION;
        END

        EXECUTE dbo.uspLogError;
    END CATCH;
END;



CREATE PROCEDURE HumanResources.uspEmployeeHireInfo2
    @BusinessEntityID [int], 
    @JobTitle [nvarchar](50), 
    @HireDate [datetime],
    @RateChangeDate [datetime], 
    @Rate [money], 
    @PayFrequency [tinyint], 
    @CurrentFlag [dbo].[Flag] 
WITH EXECUTE AS CALLER
AS
BEGIN
    SET NOCOUNT ON;

    -- Set up "constants" for error codes
    DECLARE @BUSINESS_ENTITY_ID_NOT_FOUND int = -1000,
            @DUPLICATE_RATE_CHANGE        int = -2000;
    
    BEGIN TRY
        BEGIN TRANSACTION;

        UPDATE HumanResources.Employee 
        SET JobTitle = @JobTitle, 
            HireDate = @HireDate,
            CurrentFlag = @CurrentFlag 
        WHERE BusinessEntityID = @BusinessEntityID;

        IF @@ROWCOUNT > 0  
        -- things happened as expected
          INSERT INTO HumanResources.EmployeePayHistory
             (BusinessEntityID,
              RateChangeDate
              Rate,
              PayFrequency) 
          VALUES 
             (@BusinessEntityID, 
              @RateChangeDate, 
              @Rate, 
              @PayFrequency);
        ELSE    
        -- ruh roh, the update didn't happen, so skip the insert,
        -- set the return value and exit
        BEGIN
          PRINT 'BusinessEntityID Not Found';
          ROLLBACK TRAN;
          RETURN @BUSINESS_ENTITY_ID_NOT_FOUND;
        END
    
           COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        -- Rollback any active or uncommittable transactions before
        -- inserting information in the ErrorLog
        IF @@TRANCOUNT > 0
        BEGIN
            ROLLBACK TRANSACTION;
        END
    
        EXECUTE dbo.uspLogError;
    
        IF ERROR_NUMBER() = 2627   -- Primary Key violation
        BEGIN
            PRINT 'Duplicate Rate Change Found';
            RETURN @DUPLICATE_RATE_CHANGE;
        END
    END CATCH;
END;


DECLARE @Return int;

EXEC @Return = HumanResources.uspEmployeeHireInfo2
    @BusinessEntityID = 1, 
    @JobTitle = 'His New Title', 
    @HireDate = '1996-07-01', 
    @RateChangeDate = '2008-07-31', 
    @Rate = 15, 
    @PayFrequency = 1, 
    @CurrentFlag = 1;

SELECT @Return;



DECLARE @Return int;

EXEC @Return = HumanResources.uspEmployeeHireInfo2
    @BusinessEntityID = 99999, 
    @JobTitle = 'My Invalid Employee',;
    @HireDate = '2008-07-31',
    @RateChangeDate = '2008-07-31', 
    @Rate = 15, 
    @PayFrequency = 1,
    @CurrentFlag = 1;

SELECT @Return;


RAISERROR ('Hi there, I''m an error', 1, 1);



sp_addmessage
   @msgnum = 60000,
   @severity = 10,
   @msgtext = '%s is not a valid Order date.
Order date must be within 7 days of current date.';



EXEC spMySproc '1/1/2004'
   WITH RECOMPILE


CREATE PROC spFactorial
@ValueIn int,
@ValueOut int OUTPUT
AS 
DECLARE @InWorking int;
DECLARE @OutWorking int;
IF @ValueIn != 1 
BEGIN
      SELECT @InWorking = @ValueIn - 1;

      EXEC spFactorial @InWorking, @OutWorking OUTPUT;

      SELECT @ValueOut = @ValueIn * @OutWorking;
END
ELSE
BEGIN
      SELECT @ValueOut = 1;
END 
RETURN;
GO 


DECLARE @WorkingOut int;
DECLARE @WorkingIn int;
SELECT @WorkingIn = 5;
EXEC spFactorial @WorkingIn, @WorkingOut OUTPUT;

PRINT CAST(@WorkingIn AS varchar) + ' factorial is ' + CAST(@WorkingOut AS varchar);

CREATE PROC spTriangular
@ValueIn int, 
@ValueOut int OUTPUT 
AS 
DECLARE @InWorking int;
DECLARE @OutWorking int;
IF @ValueIn != 1
BEGIN 
        SELECT @InWorking = @ValueIn - 1;
        

        EXEC spTriangular @InWorking, @OutWorking OUTPUT;
        
        SELECT @ValueOut = @ValueIn + @OutWorking;
END 
ELSE 
BEGIN 
        SELECT @ValueOut = 1;
END 
RETURN;
GO


DECLARE @WorkingOut int;
DECLARE @WorkingIn int;
SELECT @WorkingIn = 5;
EXEC spTriangular @WorkingIn, @WorkingOut OUTPUT;

PRINT CAST(@WorkingIn AS varchar) + ' Triangular is ' + CAST(@WorkingOut AS varchar);

