USE Accounting;

DECLARE @Counter  int = 1;

WHILE @Counter <= 10
BEGIN
   INSERT INTO Orders
      VALUES (1, DATEADD(mi,@Counter,GETDATE()), 1);
   SET @Counter = @Counter + 1;
END


SELECT * 
FROM Orders 
WHERE OrderDate = GETDATE();


SELECT * 
FROM Orders 
WHERE CONVERT(varchar(12), OrderDate, 101) = CONVERT(varchar(12), GETDATE(), 101)


CREATE FUNCTION dbo.DayOnly(@Date date)
RETURNS date
AS
BEGIN
   RETURN @Date;
END


CREATE FUNCTION dbo.DayOnly(@Date datetime)
RETURNS varchar(12)
AS
BEGIN
   RETURN CONVERT(varchar(12), @Date, 101);
END


SELECT * 
FROM Orders 
WHERE dbo.DayOnly(OrderDate) = dbo.DayOnly(GETDATE());


USE AdventureWorks2008;

SELECT Name, 
       ListPrice,
       (SELECT AVG(ListPrice) FROM Production.Product) AS Average, 
        ListPrice - (SELECT AVG(ListPrice) FROM Production.Product) 
         AS Difference
FROM Production.Product
WHERE ProductSubCategoryID = 1; -- The Mountain Bikes Sub-cat


CREATE FUNCTION dbo.AveragePrice()
RETURNS money
WITH SCHEMABINDING
AS 
BEGIN
   RETURN (SELECT AVG(ListPrice) FROM Production.Product);
END
GO

CREATE FUNCTION dbo.PriceDifference(@Price money)
RETURNS money
AS 
BEGIN
   RETURN @Price - dbo.AveragePrice();
END


USE AdventureWorks2008

SELECT Name, 
       ListPrice,
       dbo.AveragePrice() AS Average, 
       dbo.PriceDifference(ListPrice) AS Difference
FROM Production.Product
WHERE ProductSubCategoryID = 1; -- The Mountain Bikes Sub-cat


USE AdventureWorks2008
GO

CREATE FUNCTION dbo.fnContactList()
RETURNS TABLE
AS
RETURN (SELECT BusinessEntityID,
            LastName + ‘, ‘ + FirstName AS Name
        FROM Person.Person);
GO


SELECT *
FROM dbo.fnContactList();


--CREATE our view
CREATE VIEW vFullContactName
AS
SELECT p.BusinessEntityID,
            LastName + ‘, ‘ + FirstName AS Name,
            ea.EmailAddress
        FROM Person.Person as p
        LEFT OUTER JOIN Person.EmailAddress ea 
          ON ea.BusinessEntityID = p.BusinessEntityID;
GO


SELECT * 
FROM vFullContactName
WHERE Name LIKE ‘Ad%’;


USE AdventureWorks2008;
GO

CREATE FUNCTION dbo.fnContactSearch(@LastName nvarchar(50))
RETURNS TABLE
AS
RETURN (SELECT p.BusinessEntityID,
            LastName + ‘, ‘ + FirstName AS Name,
            ea.EmailAddress
        FROM Person.Person as p
        LEFT OUTER JOIN Person.EmailAddress ea 
          ON ea.BusinessEntityID = p.BusinessEntityID
        WHERE LastName Like @LastName + ‘%’);
GO


SELECT * 
FROM fnContactSearch(‘Ad’);


USE AdventureWorks2008;

SELECT
        TheReport.EmployeeID,
        TheReport.JobTitle,
        TheReport.LastName,
        TheReport.FirstName
FROM
        HumanResources.Employee2 as TheBoss
JOIN HumanResources.Employee2 AS TheReport 
        ON TheBoss.EmployeeID = TheReport.ManagerID
WHERE TheBoss.LastName = ‘Huntington’ AND TheBoss.FirstName = ‘Karla’;

CREATE FUNCTION dbo.fnGetReports
       (@EmployeeID AS int)
       RETURNS @Reports TABLE
       (
       EmployeeID    int         NOT NULL,
       ManagerID   int         NULL
       )
AS
BEGIN

/* Since we’ll need to call this function recursively - that is once for each 
** reporting employee (to make sure that they don’t have reports of their
** own), we need a holding variable to keep track of which employee we’re
** currently working on. */
DECLARE @Employee AS int;

/* This inserts the current employee into our working table. The significance
** here is that we need the first record as something of a primer due to the
** recursive nature of the function - this is how we get it. */
INSERT INTO @Reports
   SELECT EmployeeID, ManagerID 
   FROM HumanResources.Employee2 
   WHERE EmployeeID = @EmployeeID;

/* Now we also need a primer for the recursive calls we’re getting ready to
** start making to this function. This would probably be better done with a
** cursor, but we haven’t gotten to that chapter yet, so.... */
SELECT @Employee = MIN(EmployeeID) 
FROM HumanResources.Employee2
WHERE ManagerID = @EmployeeID;

/* This next part would probably be better done with a cursor but we haven’t
** gotten to that chapter yet, so we’ll fake it. Notice the recursive call
** to our function! */
WHILE @Employee IS NOT NULL
   BEGIN
      INSERT INTO @Reports
           SELECT * 
           FROM fnGetReports(@Employee);

           SELECT @Employee = MIN(EmployeeID) 
           FROM HumanResources.Employee2 
           WHERE EmployeeID > @Employee
              AND ManagerID = @EmployeeID;
   END

RETURN;

END
GO


SELECT * FROM fnGetReports(4);


DECLARE @EmployeeID int;

SELECT @EmployeeID = EmployeeID
FROM HumanResources.Employee2 e
WHERE LastName = ‘Huntington’
AND FirstName = ‘Karla’;

SELECT e.EmployeeID, e.LastName, e.FirstName, m.LastName AS ReportsTo
FROM HumanResources.Employee2 AS e
JOIN dbo.fnGetReports(@EmployeeID) AS r
  ON e.EmployeeID = r.EmployeeID
JOIN HumanResources.Employee2 AS m
  ON m.EmployeeID = r.ManagerID;


USE Accounting;

SELECT OBJECTPROPERTY(OBJECT_ID(‘DayOnly’), ‘IsDeterministic’);


ALTER FUNCTION dbo.DayOnly(@Date date)
RETURNS date
WITH SCHEMABINDING
AS
BEGIN
   RETURN @Date;
END


CREATE FUNCTION dbo.AveragePrice()
RETURNS money
WITH SCHEMABINDING
AS 
BEGIN
   RETURN (SELECT AVG(ListPrice) FROM Production.Product);
END
GO

CREATE FUNCTION dbo.PriceDifference(@Price money)
RETURNS money
AS 
BEGIN
   RETURN @Price - dbo.AveragePrice();
END






