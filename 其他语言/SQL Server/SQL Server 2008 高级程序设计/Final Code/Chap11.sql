USE Accounting;
DECLARE @Ident int;

INSERT INTO Orders
(CustomerNo,OrderDate, EmployeeID)
VALUES
(1, GETDATE(), 1);
SELECT @Ident = @@IDENTITY;
INSERT INTO OrderDetails
(OrderID, PartNo, Description, UnitPrice, Qty)
VALUES
(@Ident, '2R2416', 'Cylinder Head', 1300, 2);
SELECT 'The OrderID of the INSERTed row is ' + CONVERT(varchar(8),@Ident);

USE AdventureWorks2008;

DECLARE @Test money;
SET @Test = MAX(UnitPrice) FROM [Order Details];
SELECT @Test;


USE AdventureWorks2008;

DECLARE @Test money;
SET @Test = (SELECT MAX(UnitPrice) FROM Sales.SalesOrderDetail);
SELECT @Test;

USE AdventureWorks2008;

DECLARE @Test money;
SELECT @Test = MAX(UnitPrice) FROM Sales.SalesOrderDetail;
SELECT @Test;

CREATE TABLE TestIdent
(
  IDCol   int   IDENTITY
  PRIMARY KEY
);

CREATE TABLE TestChild1
(
  IDcol   int
  PRIMARY KEY
  FOREIGN KEY
  REFERENCES TestIdent(IDCol)
);

CREATE TABLE TestChild2
(
  IDcol   int
  PRIMARY KEY
  FOREIGN KEY
  REFERENCES TestIdent(IDCol)
);

/*****************************************
** This script illustrates how the identity
** value gets lost as soon as another INSERT
** happens
****************************************** */

DECLARE @Ident   int;  -- This will be a holding variable
/* We'll use it to show how we can
** move values from system functions
** into a safe place.
*/
INSERT INTO TestIdent
  DEFAULT VALUES;
SET @Ident = @@IDENTITY;
PRINT 'The value we got originally from @@IDENTITY was ' +
CONVERT(varchar(2),@Ident);
PRINT 'The value currently in @@IDENTITY is ' + CONVERT(varchar(2),@@IDENTITY);

/* On this first INSERT using @@IDENTITY, we're going to get lucky.
** We'll get a proper value because there is nothing between our
** original INSERT and this one. You'll see that on the INSERT that
** will follow after this one, we won't be so lucky anymore. */
INSERT INTO TestChild1
VALUES
  (@@IDENTITY);

PRINT 'The value we got originally from @@IDENTITY was ' +
CONVERT(varchar(2),@Ident);
IF (SELECT @@IDENTITY) IS NULL
  PRINT 'The value currently in @@IDENTITY is NULL';
ELSE
  PRINT 'The value currently in @@IDENTITY is ' + CONVERT(varchar(2),@@IDENTITY);
-- The next line is just a spacer for our print out
PRINT '';
/* The next line is going to blow up because the one column in
** the table is the primary key, and primary keys can't be set
** to NULL. @@IDENTITY will be NULL because we just issued an
** INSERT statement a few lines ago, and the table we did the
** INSERT into doesn't have an identity field. Perhaps the biggest
** thing to note here is when @@IDENTITY changed - right after
** the next INSERT statement. */
INSERT INTO TestChild2
VALUES
  (@@IDENTITY);

/*****************************************
** This script illustrates how the identity
** value gets lost as soon as another INSERT
** happens
****************************************** */

DECLARE @Ident   int;  -- This will be a holding variable

/* We'll use it to show how we can
** move values from system functions
** into a safe place.
*/
INSERT INTO TestIdent
  DEFAULT VALUES;
SET @Ident = @@IDENTITY;
PRINT 'The value we got originally from @@IDENTITY was ' +
CONVERT(varchar(2),@Ident);
PRINT 'The value currently in @@IDENTITY is ' + CONVERT(varchar(2),@@IDENTITY);

/* On this first INSERT using @@IDENTITY, we're going to get lucky.
** We'll get a proper value because there is nothing between our
** original INSERT and this one. You'll see that on the INSERT that
** will follow after this one, we won't be so lucky anymore. */
INSERT INTO TestChild1
VALUES
  (@@IDENTITY);

PRINT 'The value we got originally from @@IDENTITY was ' +
CONVERT(varchar(2),@Ident);
IF (SELECT @@IDENTITY) IS NULL
  PRINT 'The value currently in @@IDENTITY is NULL';
ELSE
  PRINT 'The value currently in @@IDENTITY is ' + CONVERT(varchar(2),@@IDENTITY);
-- The next line is just a spacer for our print out
PRINT '';
/* This time all will go fine because we are using the value that
** we have placed in safekeeping instead of @@IDENTITY directly.*/
INSERT INTO TestChild2
VALUES



USE AdventureWorks2008
SELECT * FROM Person.Person;


USE AdventureWorks2008;
GO

DECLARE @RowCount int;  --Notice the single @ sign
SELECT * FROM Person.Person;
SELECT @RowCount = @@ROWCOUNT;


SELECT * FROM Person.Person WHERE ContactID = 1 GO


USE AdventureWorks2008;

DECLARE @MyVarchar varchar(50);  --This DECLARE only lasts for this batch!

SELECT @MyVarchar = 'Honey, I''m home...';

PRINT 'Done with first Batch...';

GO

PRINT @MyVarchar;  --This generates an error since @MyVarchar
                  --isn't declared in this batch
PRINT 'Done with second Batch';

GO

PRINT 'Done with third batch';   -- Notice that this still gets executed
                                -- even after the error

GO


USE master;

CREATE DATABASE Test;

CREATE TABLE TestTable
(
   col1   int,
   col2   int
);


USE Test;

SELECT TABLE_CATALOG
FROM INFORMATION_SCHEMA.TABLES
WHERE TABLE_NAME = 'TestTable';


USE MASTER;
DROP DATABASE Test;

CREATE DATABASE Test;

USE Test;

CREATE TABLE TestTable
(
   col1   int,
   col2   int
);

CREATE DATABASE Test;
GO

USE Test;
CREATE TABLE TestTable
(
   col1   int,
   col2   int
);

USE Test;

ALTER TABLE TestTable
  ADD col3 int;
INSERT INTO TestTable
  (col1, col2, col3)
VALUES
  (1,1,1);


USE AdventureWorks2008;
GO

--Create The Table. We'll pull info from here for our dynamic SQL
CREATE TABLE DynamicSQLExample
(
   TableID     int   IDENTITY   NOT NULL
      CONSTRAINT PKDynamicSQLExample
                 PRIMARY KEY,
   SchemaName  varchar(128)     NOT NULL,
   TableName   varchar(128)     NOT NULL
);
GO

/* Populate the table. In this case, We're grabbing every user
** table object in this database                             */
INSERT INTO DynamicSQLExample
SELECT s.name AS SchemaName, t.name AS TableName
   FROM sys.schemas s
   JOIN sys.tables t
    ON s.schema_id = t.schema_id;


DECLARE @SchemaName     varchar(128);
DECLARE @TableName      varchar(128);

-- Grab the table name that goes with our ID
SELECT @SchemaName = SchemaName, @TableName = TableName
   FROM DynamicSQLExample
   WHERE TableID = 25;

-- Finally, pass that value into the EXEC statement
EXEC ('SELECT * FROM ' + @SchemaName + '.' + @TableName);


USE AdventureWorks2008;
/* First, we'll declare to variables. One for stuff we're putting into
** the EXEC, and one that we think will get something back out (it won't)
*/
DECLARE @InVar   varchar(50);
DECLARE @OutVar  varchar(50);

-- Set up our string to feed into the EXEC command
SET @InVar = 'SELECT @OutVar = FirstName FROM Person.Contact WHERE ContactID = 1';
-- Now run it
EXEC (@Invar);
-- Now, just to show there's no difference, run the select without using a in variable
EXEC ('SELECT @OutVar = FirstName FROM Person.Contac WHERE ContactID = 1');
-- @OutVar will still be NULL because we haven't been able to put anything in it
SELECT @OutVar;


USE AdventureWorks2008;
-- This time, we only need one variable. It does need to be longer though.
DECLARE @InVar varchar(200);
/* Set up our string to feed into the EXEC command. This time we're going
** to feed it several statements at a time. They will all execute as one
** batch.
*/
SET @InVar = 'DECLARE @OutVar varchar(50);
SELECT @OutVar = FirstName FROM Person.Person WHERE BusinessEntityID  = 1;
SELECT ''The Value Is '' + @OutVar';
-- Now run it
EXEC (@Invar);

USE AdventureWorks2008;

EXEC('SELECT * FROM Production.UnitMeasure');

SELECT 'The Rowcount is ' + CAST(@@ROWCOUNT as varchar);


USE AdventureWorks2008;

-- This won't work
DECLARE @NumberOfLetters int = 15;
EXEC('SELECT LEFT(Name,' + CAST(@NumberOfLetters AS varchar) + ') AS ShortName
FROM Production.Product');
GO
-- But this does
DECLARE @NumberOfLetters AS int = 15;
DECLARE @str AS varchar(255);
SET @str = 'SELECT LEFT(Name,' + CAST(@NumberOfLetters AS varchar) + ') AS ShortName
FROM Production.Product';
EXEC(@str);


-- We'll run a SELECT looking for our table to start with to prove it's not there
SELECT 'Found Table ' + s.name + '.' + t.name
   FROM sys.schemas s
   JOIN sys.tables t
        ON s.schema_id = t.schema_id
   WHERE s.name = 'dbo'
     AND t.name = 'OurIFTest';


-- Now we're run our conditional CREATE statement
IF NOT EXISTS (
    SELECT s.name AS SchemaName, t.name AS TableName
       FROM sys.schemas s
       JOIN sys.tables t
            ON s.schema_id = t.schema_id
       WHERE s.name = 'dbo'
         AND t.name = 'OurIFTest'
              )
    CREATE TABLE OurIFTest(
        Col1    int        PRIMARY KEY
        );

-- And now look again to prove that it's been created.
SELECT 'Found Table ' + s.name + '.' + t.name
   FROM sys.schemas s
   JOIN sys.tables t
        ON s.schema_id = t.schema_id
   WHERE s.name = 'dbo'
     AND t.name = 'OurIFTest';


-- Now we're run our conditional CREATE statement
IF NOT EXISTS (
    SELECT s.name AS SchemaName, t.name AS TableName
        FROM sys.schemas s
        JOIN sys.tables t
            ON s.schema_id = t.schema_id
       WHERE s.name = 'dbo'
         AND t.name = 'OurIFTest'
              )
    CREATE TABLE OurIFTest(
        Col1    int        PRIMARY KEY
        );
ELSE
    PRINT 'WARNING: Skipping CREATE as table already exists';


-- This time we're adding a check to see if the table DOES already exist
-- We'll remove it if it does so that the rest of our example can test the
-- IF condition. Just remove this first IF EXISTS block if you want to test
-- the ELSE condition below again.
IF EXISTS (
    SELECT s.name AS SchemaName, t.name AS TableName
       FROM sys.schemas s
       JOIN sys.tables t
            ON s.schema_id = t.schema_id
       WHERE s.name = 'dbo'
         AND t.name = 'OurIFTest'
              )
    DROP TABLE OurIFTest;

-- Now we're run our conditional CREATE statement
IF NOT EXISTS (
    SELECT s.name AS SchemaName, t.name AS TableName
        FROM sys.schemas s
        JOIN sys.tables t
            ON s.schema_id = t.schema_id
        WHERE s.name = 'dbo'
            AND t.name = 'OurIFTest'
              )
    BEGIN
        PRINT 'Table dbo.OurIFTest not found.';
        PRINT 'CREATING: Table dbo.OurIFTest';
        CREATE TABLE OurIFTest(
            Col1    int    PRIMARY KEY
            );
    END
ELSE
        PRINT 'WARNING: Skipping CREATE as table already exists';


USE AdventureWorks2008;
GO

SELECT TOP 10 SalesOrderID, 
              SalesOrderID % 10 AS 'Last Digit', 
              Position = CASE SalesOrderID % 10
                           WHEN 1 THEN 'First'
                           WHEN 2 THEN 'Second'
                           WHEN 3 THEN 'Third'
                           WHEN 4 THEN 'Fourth'
                           ELSE 'Something Else'
                         END
FROM Sales.SalesOrderHeader;


USE AdventureWorks2008;
GO

SELECT TOP 10 SalesOrderID % 10 AS 'OrderLastDigit',
   ProductID % 10 AS 'ProductLastDigit',
   "How Close?" = CASE SalesOrderID % 10
      WHEN ProductID % 1 THEN 'Exact Match!'
      WHEN ProductID % 1 - 1 THEN 'Within 1'
      WHEN ProductID % 1 + 1 THEN 'Within 1'
      ELSE 'More Than One Apart'
   END
FROM Sales.SalesOrderDetail
ORDER BY SalesOrderID DESC;


SELECT TOP 10 SalesOrderID % 10 AS 'OrderLastDigit',
   ProductID % 10 AS 'ProductLastDigit',
   "How Close?" = CASE
      WHEN (SalesOrderID % 10) < 3 THEN 'Ends With Less Than Three'
      WHEN ProductID = 6 THEN 'ProductID is 6'
      WHEN ABS(SalesOrderID % 10 - ProductID) <= 1 THEN 'Within 1'
      ELSE 'More Than One Apart'
   END
FROM Sales.SalesOrderDetail
ORDER BY SalesOrderID DESC;

USE AdventureWorks2008;
GO

/* I'm setting up some holding variables here. This way, if we get asked
** to run the query again with a slightly different value, we'll only have
** to change it in one place.
*/
DECLARE @Markup     money;
DECLARE @Multiplier money;

SELECT @Markup = .10;                -- Change the markup here
SELECT @Multiplier = @Markup + 1;    -- We want the end price, not the amount
                                     -- of the increase, so add 1


/* Now execute things for our results. Note that we're limiting things
** to the top 10 items for brevity -- in reality, we either wouldn't do this
** at all, or we would have a more complex WHERE clause to limit the
** increase to a particular set of products
*/
SELECT TOP 10 ProductID, Name, ListPrice,
   ListPrice * @Multiplier AS "Marked Up Price", "New Price" =
   CASE WHEN FLOOR(ListPrice * @Multiplier + .24)
             > FLOOR(ListPrice * @Multiplier)
                     THEN FLOOR(ListPrice * @Multiplier) + .95
        WHEN FLOOR(ListPrice * @Multiplier + .5) >
             FLOOR(ListPrice * @Multiplier)
                     THEN FLOOR(ListPrice * @Multiplier) + .75
        ELSE FLOOR(ListPrice * @Multiplier) + .49
   END
FROM Production.Product
WHERE ProductID % 10 = 0  -- this is just to help the example
ORDER BY ProductID DESC;


WHILE 1 = 1
BEGIN
   WAITFOR TIME '01:00';
   EXEC sp_updatestats;
   RAISERROR('Statistics Updated for Database', 1, 1) WITH LOG;
END


WAITFOR DELAY '01:00';

WAITFOR TIME '01:00';

BEGIN TRY
    -- Try and create our table
    CREATE TABLE OurIFTest(
        Col1    int        PRIMARY KEY
        );
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
