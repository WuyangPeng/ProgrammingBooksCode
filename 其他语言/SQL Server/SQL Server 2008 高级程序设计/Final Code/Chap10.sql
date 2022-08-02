USE Accounting;
GO

CREATE VIEW CustomerPhoneList_vw
AS
   SELECT CustomerName, Contact, Phone
   FROM Customers;

SELECT * FROM CustomerPhoneList_vw;

SELECT * FROM Customers;

USE AccountingChapter10;
GO

CREATE VIEW Employees_vw
AS
SELECT   EmployeeID,
         FirstName,
         MiddleInitial,
         LastName,
         Title,
         HireDate,
         TerminationDate,
         ManagerEmpID,
         Department
FROM Employees;

SELECT *
FROM Employees_vw;

CREATE VIEW CurrentEmployees_vw
AS
SELECT   EmployeeID,
         FirstName,
         MiddleInitial,
         LastName,
         Title,
         HireDate,
         ManagerEmpID,
         Department
FROM Employees
WHERE TerminationDate IS NULL;

SELECT   EmployeeID,
         FirstName,
         LastName,
         TerminationDate
FROM Employees;

SELECT   EmployeeID,
         FirstName,
         LastName
FROM CurrentEmployees_vw;

USE AdventureWorks2008
GO

CREATE VIEW CustomerOrders_vw
AS
SELECT sc.AccountNumber,
       soh.SalesOrderID,
       soh.OrderDate,
       sod.ProductID,
       pp.Name,
       sod.OrderQty,
       sod.UnitPrice,
       sod.UnitPriceDiscount * sod.UnitPrice * sod.OrderQty AS TotalDiscount,
       sod.LineTotal
FROM   Sales.Customer AS sc
INNER JOIN Sales.SalesOrderHeader AS soh
      ON sc.CustomerID = soh.CustomerID
INNER JOIN Sales.SalesOrderDetail AS sod
      ON soh.SalesOrderID = sod.SalesOrderID
INNER JOIN Production.Product AS pp
      ON sod.ProductID = pp.ProductID;

SELECT *
FROM CustomerOrders_vw;

SELECT AccountNumber, LineTotal
FROM CustomerOrders_vw
WHERE OrderDate = '01/07/2002';

USE AdventureWorks2008
GO

CREATE VIEW YesterdaysOrders_vw
AS
SELECT sc.AccountNumber,
       soh.SalesOrderID,
       soh.OrderDate,
       sod.ProductID,
       pp.Name,
       sod.OrderQty,
       sod.UnitPrice,
       sod.UnitPriceDiscount * sod.UnitPrice * sod.OrderQty AS TotalDiscount,
       sod.LineTotal
FROM   Sales.Customer AS sc
INNER JOIN   Sales.SalesOrderHeader AS soh
      ON sc.CustomerID = soh.CustomerID
INNER JOIN   Sales.SalesOrderDetail AS sod
      ON soh.SalesOrderID = sod.SalesOrderID
INNER JOIN Production.Product AS pp
      ON sod.ProductID = pp.ProductID
WHERE CAST(soh.OrderDate AS Date) = 
      CAST(DATEADD(day,-1,GETDATE()) AS Date);

USE AdventureWorks2008

UPDATE Sales.SalesOrderHeader
SET OrderDate = CAST(DATEADD(day,-1,GETDATE()) AS Date),
    DueDate = CAST(DATEADD(day,11,GETDATE()) AS Date),
    ShipDate = CAST(DATEADD(day,6,GETDATE()) AS Date)
WHERE Sales.SalesOrderID BETWEEN 43659 AND 43662; 

SELECT AccountNumber, SalesOrderID, OrderDate FROM YesterdaysOrders_vw;


CREATE VIEW PortlandAreaAddresses_vw
AS
SELECT AddressID,
       AddressLine1,
       City,
       StateProvinceID,
       PostalCode,
       ModifiedDate
FROM Person.Address
WHERE PostalCode LIKE '970%'
   OR PostalCode LIKE '971%'
   OR PostalCode LIKE '972%'
   OR PostalCode LIKE '986[6-9]%'
WITH CHECK OPTION;

UPDATE PortlandAreaAddresses_vw
SET PostalCode = '33333'  -- it was 97205
WHERE AddressID = 22;

UPDATE Person.Address
SET PostalCode = '33333'  -- it was 97205
WHERE AddressID = 22;

SELECT *
FROM sys.sql_modules
WHERE object_id = OBJECT_ID('dbo.YesterdaysOrders_vw');

ALTER VIEW CustomerOrders_vw
WITH ENCRYPTION
AS
SELECT   sc.AccountNumber,
         soh.SalesOrderID,
         soh.OrderDate,
         sod.ProductID,
         pp.Name,
         sod.OrderQty,
         sod.UnitPrice,
         sod.UnitPriceDiscount * sod.UnitPrice * sod.OrderQty AS TotalDiscount,
         sod.LineTotal
FROM     Sales.Customer AS sc
INNER JOIN   Sales.SalesOrderHeader AS soh
      ON sc.CustomerID = soh.CustomerID
INNER JOIN   Sales.SalesOrderDetail AS sod
      ON soh.SalesOrderID = sod.SalesOrderID
INNER JOIN Production.Product AS pp
      ON sod.ProductID = pp.ProductID;

EXEC sp_helptext CustomerOrders_vw

SELECT *
FROM sys.sql_modules
WHERE object_id = OBJECT_ID('dbo.CustomerOrders_vw');

ALTER VIEW CustomerOrders_vw
WITH SCHEMABINDING
AS
SELECT   sc.AccountNumber,
         soh.SalesOrderID,
         soh.OrderDate,
         sod.ProductID,
         pp.Name,
         sod.OrderQty,
         sod.UnitPrice,
         sod.UnitPriceDiscount * sod.UnitPrice * sod.OrderQty AS TotalDiscount,
         sod.LineTotal
FROM     Sales.Customer AS sc
INNER JOIN   Sales.SalesOrderHeader AS soh
      ON sc.CustomerID = soh.CustomerID
INNER JOIN   Sales.SalesOrderDetail AS sod
      ON soh.SalesOrderID = sod.SalesOrderID
INNER JOIN Production.Product AS pp
      ON sod.ProductID = pp.ProductID;

SELECT * FROM CustomerOrders_vw;

CREATE UNIQUE CLUSTERED INDEX ivCustomerOrders
ON CustomerOrders_vw(AccountNumber, SalesOrderID, ProductID);

