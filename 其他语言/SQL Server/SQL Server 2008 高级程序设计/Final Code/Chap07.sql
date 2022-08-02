SELECT DISTINCT sod.ProductID
FROM Sales.SalesOrderHeader soh
JOIN Sales.SalesOrderDetail sod
  ON soh.SalesOrderID = sod.SalesOrderID
WHERE OrderDate = '07/01/2001';  --This is first OrderDate in the system

SELECT DISTINCT soh.OrderDate, sod.ProductID
FROM Sales.SalesOrderHeader soh
JOIN Sales.SalesOrderDetail sod
  ON soh.SalesOrderID = sod.SalesOrderID
WHERE OrderDate = (SELECT MIN(OrderDate) FROM Sales.SalesOrderHeader);

SELECT ProductID, Name
FROM Production.Product
WHERE ProductID IN (
 SELECT ProductID FROM Sales.SpecialOfferProduct);

SELECT DISTINCT pp.ProductID, Name
FROM Production.Product pp
JOIN Sales.SpecialOfferProduct ssop
 ON pp.ProductID = ssop.ProductID;

SELECT Description
FROM Sales.SpecialOfferProduct ssop
RIGHT OUTER JOIN Sales.SpecialOffer sso
 ON ssop.SpecialOfferID = sso.SpecialOfferID
WHERE sso.SpecialOfferID != 1
  AND ssop.SpecialOfferID IS NULL;

SELECT Description
FROM Sales.SpecialOffer sso
WHERE sso.SpecialOfferID != 1
  AND sso.SpecialOfferID NOT IN
    (SELECT SpecialOfferID FROM Sales.SpecialOfferProduct);

USE AdventureWorks2008;

-- Get a list of customers and the date of their first order
SELECT soh.CustomerID, MIN(soh.OrderDate) AS OrderDate
INTO #MinOrderDates
FROM Sales.SalesOrderHeader soh
GROUP BY soh.CustomerID;

-- Do something additional with that information
SELECT soh.CustomerID, soh.SalesOrderID, soh.OrderDate
FROM Sales.SalesOrderHeader soh
JOIN #MinOrderDates t
  ON soh.CustomerID = t.CustomerID
  AND soh.OrderDate = t.OrderDate
ORDER BY soh.CustomerID;

DROP TABLE #MinOrderDates;

SELECT soh1.CustomerID, soh1.SalesOrderID, soh1.OrderDate
FROM Sales.SalesOrderHeader soh1
WHERE soh1.OrderDate = (SELECT Min(soh2.OrderDate) 
                      FROM Sales.SalesOrderHeader soh2
                      WHERE soh2.CustomerID = soh1.CustomerID)
ORDER BY CustomerID;

SELECT sc.AccountNumber, 
   (SELECT Min(OrderDate) 
           FROM Sales.SalesOrderHeader soh
           WHERE soh.CustomerID = sc.CustomerID) 
           AS OrderDate
FROM Sales.Customer sc;

SELECT sc.AccountNumber, sst.Name
FROM Sales.SalesOrderHeader soh
JOIN Sales.SalesOrderDetail sod
 ON soh.SalesOrderID = sod.SalesOrderID
JOIN Production.Product pp
 ON sod.ProductID = pp.ProductID
JOIN Sales.Customer sc
 ON sc.CustomerID = soh.CustomerID
JOIN Sales.SalesTerritory sst
 ON sst.TerritoryID = sc.TerritoryID
WHERE pp.Name = 'HL Mountain Rear Wheel';

SELECT DISTINCT sc.AccountNumber, sst.Name
FROM Sales.Customer AS sc
JOIN Sales.SalesTerritory sst
 ON sc.TerritoryID = sst.TerritoryID
JOIN
  (SELECT CustomerID 
 FROM Sales.SalesOrderHeader soh
 JOIN Sales.SalesOrderDetail sod
        ON soh.SalesOrderID = sod.SalesOrderID
 JOIN Production.Product pp
        ON sod.ProductID = pp.ProductID
 WHERE pp.Name = 'HL Mountain Rear Wheel') AS dt1
  ON sc.CustomerID = dt1.CustomerID
JOIN
  (SELECT CustomerID 
 FROM Sales.SalesOrderHeader soh
 JOIN Sales.SalesOrderDetail sod
        ON soh.SalesOrderID = sod.SalesOrderID
 JOIN Production.Product pp
        ON sod.ProductID = pp.ProductID
 WHERE Name = 'HL Mountain Front Wheel') AS dt2
  ON sc.CustomerID = dt2.CustomerID;

SELECT BusinessEntityID, LastName + ', ' + FirstName AS Name
FROM Person.Person pp
WHERE EXISTS
   (SELECT BusinessEntityID 
           FROM HumanResources.Employee hre
           WHERE hre.BusinessEntityID = pp.BusinessEntityID);

SELECT pp.BusinessEntityID, LastName + ', ' + FirstName AS Name
FROM Person.Person pp
JOIN HumanResources.Employee hre
  ON pp.BusinessEntityID = hre.BusinessEntityID;

SELECT pp.BusinessEntityID, LastName + ', ' + FirstName AS Name
FROM Person.Person pp
LEFT JOIN HumanResources.Employee hre
  ON pp.BusinessEntityID = hre.BusinessEntityID
WHERE hre.BusinessEntityID IS NULL;

SELECT BusinessEntityID, LastName + ', ' + FirstName AS Name
FROM Person.Person pp
WHERE NOT EXISTS
   (SELECT BusinessEntityID 
           FROM HumanResources.Employee hre
           WHERE hre.BusinessEntityID = pp.BusinessEntityID);

IF EXISTS
  (SELECT *
   FROM sys.objects
   WHERE OBJECT_NAME(object_id) = 'foo'
     AND SCHEMA_NAME(schema_id) = 'dbo'
     AND OBJECTPROPERTY(object_id, 'IsUserTable') = 1)
BEGIN
  DROP TABLE dbo.foo;
  PRINT 'Table foo has been dropped';
END
GO

CREATE TABLE dbo.foo
(
  Column1 int IDENTITY(1,1) NOT NULL,
  Column2 varchar(50)NULL
);

USE MASTER;
GO

IF NOT EXISTS 
 (SELECT 'True' 
  FROM sys.databases 
  WHERE name = 'AdventureWorksCreate')
BEGIN
   CREATE DATABASE AdventureWorksCreate;
END
ELSE
BEGIN
   PRINT 'Database already exists. Skipping CREATE DATABASE Statement';
END
GO

SELECT 'The Customer has an Order numbered ' + SalesOrderID
FROM Sales.SalesOrderHeader
WHERE CustomerID = 29825;

SELECT 'The Customer has an Order numbered ' + CAST(SalesOrderID AS varchar)
FROM Sales.SalesOrderHeader
WHERE CustomerID = 29825;

CREATE TABLE ConvertTest
(
   ColID   int   IDENTITY,
   ColTS   timestamp
);
GO

INSERT INTO ConvertTest
   DEFAULT VALUES;

SELECT ColTS AS Uncoverted, CAST(ColTS AS int) AS Converted
FROM ConvertTest;

SELECT OrderDate, CAST(OrderDate AS varchar) AS Converted
FROM Sales.SalesOrderHeader
WHERE SalesOrderID = 43663;

SELECT OrderDate, CONVERT(varchar(12), OrderDate, 111) AS Converted
FROM Sales.SalesOrderHeader
WHERE SalesOrderID = 43663;

SELECT OrderDate, CONVERT(varchar(12), OrderDate, 5) AS Converted
FROM Sales.SalesOrderHeader
WHERE SalesOrderID = 43663;

USE AdventureWorks2008

CREATE TABLE Sales.MonthlyRollup
(
  Year      smallint    NOT NULL,
  Month     tinyint     NOT NULL,
  ProductID int         NOT NULL
    FOREIGN KEY 
      REFERENCES Production.Product(ProductID),
  QtySold   int         NOT NULL,
  CONSTRAINT PKYearMonthProductID
    PRIMARY KEY 
      (Year, Month, ProductID)
);

SELECT soh.OrderDate, sod.ProductID, SUM(sod.OrderQty) AS QtySold
FROM Sales.SalesOrderHeader soh
JOIN Sales.SalesOrderDetail sod
  ON soh.SalesOrderID = sod.SalesOrderID
WHERE soh.OrderDate >= '2003-08-01' 
  AND soh.OrderDate < '2003-08-02'
GROUP BY soh.OrderDate, sod.ProductID;

MERGE Sales.MonthlyRollup AS smr
USING
(
  SELECT soh.OrderDate, sod.ProductID, SUM(sod.OrderQty) AS QtySold
  FROM Sales.SalesOrderHeader soh
  JOIN Sales.SalesOrderDetail sod
    ON soh.SalesOrderID = sod.SalesOrderID
  WHERE soh.OrderDate >= '2003-08-01' AND soh.OrderDate < '2003-08-02'
  GROUP BY soh.OrderDate, sod.ProductID
) AS s
ON (s.ProductID = smr.ProductID)
WHEN MATCHED THEN
  UPDATE SET smr.QtySold = smr.QtySold + s.QtySold
WHEN NOT MATCHED THEN
  INSERT (Year, Month, ProductID, QtySold)
  VALUES (DATEPART(yy, s.OrderDate),
          DATEPART(m, s.OrderDate),
          s.ProductID,
          s.QtySold);

SELECT * 
FROM Sales.MonthlyRollup;

MERGE Sales.MonthlyRollup AS smr
USING
(
  SELECT soh.OrderDate, sod.ProductID, SUM(sod.OrderQty) AS QtySold
  FROM Sales.SalesOrderHeader soh
  JOIN Sales.SalesOrderDetail sod
    ON soh.SalesOrderID = sod.SalesOrderID
  WHERE soh.OrderDate >= '2003-08-02' AND soh.OrderDate < '2003-08-03'
  GROUP BY soh.OrderDate, sod.ProductID
) AS s
ON (s.ProductID = smr.ProductID)
WHEN MATCHED THEN
  UPDATE SET smr.QtySold = smr.QtySold + s.QtySold
WHEN NOT MATCHED THEN
  INSERT (Year, Month, ProductID, QtySold)
  VALUES (DATEPART(yy, s.OrderDate),
          DATEPART(m, s.OrderDate),
          s.ProductID,
          s.QtySold);

SELECT * 
FROM Sales.MonthlyRollup;

USE AdventureWorks2008
TRUNCATE TABLE Sales.MonthlyRollup;

MERGE Sales.MonthlyRollup AS smr
USING
(
  SELECT soh.OrderDate, sod.ProductID, SUM(sod.OrderQty) AS QtySold
  FROM Sales.SalesOrderHeader soh
  JOIN Sales.SalesOrderDetail sod
    ON soh.SalesOrderID = sod.SalesOrderID
  WHERE soh.OrderDate >= '2003-08-01' AND soh.OrderDate < '2003-08-02'
  GROUP BY soh.OrderDate, sod.ProductID
) AS s
ON (s.ProductID = smr.ProductID)
WHEN MATCHED THEN
  UPDATE SET smr.QtySold = smr.QtySold + s.QtySold
WHEN NOT MATCHED THEN
  INSERT (Year, Month, ProductID, QtySold)
  VALUES (DATEPART(yy, s.OrderDate),
          DATEPART(m, s.OrderDate),
          s.ProductID,
          s.QtySold)
OUTPUT $action,
        inserted.Year,
        inserted.Month,
        inserted.ProductID,
        inserted.QtySold,
        deleted.Year,
        deleted.Month,
        deleted.ProductID,
        deleted.QtySold;

MERGE Sales.MonthlyRollup AS smr
USING
(
  SELECT soh.OrderDate, sod.ProductID, SUM(sod.OrderQty) AS QtySold
  FROM Sales.SalesOrderHeader soh
  JOIN Sales.SalesOrderDetail sod
    ON soh.SalesOrderID = sod.SalesOrderID
  WHERE soh.OrderDate >= '2003-08-02' AND soh.OrderDate < '2003-08-03'
  GROUP BY soh.OrderDate, sod.ProductID
) AS s
ON (s.ProductID = smr.ProductID)
WHEN MATCHED THEN
  UPDATE SET smr.QtySold = smr.QtySold + s.QtySold
WHEN NOT MATCHED THEN
  INSERT (Year, Month, ProductID, QtySold)
  VALUES (DATEPART(yy, s.OrderDate),
          DATEPART(m, s.OrderDate),
          s.ProductID,
          s.QtySold)
OUTPUT $action,
        inserted.Year,
        inserted.Month,
        inserted.ProductID,
        inserted.QtySold,
        deleted.Year,
        deleted.Month,
        deleted.ProductID,
        deleted.QtySold;


