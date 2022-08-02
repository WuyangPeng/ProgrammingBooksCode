SELECT * FROM INFORMATION_SCHEMA.TABLES;

SELECT * FROM Sales.Customer;

SELECT LastName FROM Person.Person; 

SELECT Name FROM Production.Product; 

SELECT Name, ProductNumber, ReorderPoint
FROM Production.Product

SELECT Name, ProductNumber, ReorderPoint
FROM Production.Product 
WHERE ProductID = 356

SELECT Name, ProductNumber, ReorderPoint
FROM Production.Product
ORDER BY Name;

SELECT Name, ProductNumber, ReorderPoint
FROM Production.Product
ORDER BY ProductNumber;

SELECT Name, SalesPersonID
FROM Sales.Store
WHERE Name BETWEEN 'g' AND 'j'
  AND SalesPersonID > 283
ORDER BY SalesPersonID, Name DESC;

SELECT SalesOrderID, OrderQty
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672);

SELECT SalesOrderID, SUM(OrderQty)
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT SalesOrderID, SUM(OrderQty) AS TotalOrderQty
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT CustomerID, SalesPersonID, COUNT(*)
FROM Sales.SalesOrderHeader
WHERE CustomerID <= 11010
GROUP BY CustomerID, SalesPersonID
ORDER BY CustomerID, SalesPersonID;

SELECT SalesOrderID, AVG(OrderQty)
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT SalesOrderID, MIN(OrderQty)
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT SalesOrderID, MAX(OrderQty)
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT SalesOrderID, MIN(OrderQty), MAX(OrderQty)
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT SalesOrderID, MIN(OrderQty) AS MinOrderQty, MAX(OrderQty) AS MaxOrderQty
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT SalesOrderID AS “Order Number”, MIN(OrderQty) MinOrderQty, MAX(OrderQty) MaxOrderQty
FROM Sales.SalesOrderDetail
WHERE SalesOrderID IN (43660, 43670, 43672)
GROUP BY SalesOrderID;

SELECT COUNT(*)
FROM HumanResources.Employee
WHERE HumanResources.Employee.BusinessEntityID = 5;

SELECT COUNT(*)
FROM HumanResources.Employee;

SELECT COUNT(*)
FROM Person.Person;


SELECT COUNT(*)
FROM Person.Person;


SELECT COUNT(*)
FROM Person.Person
WHERE AdditionalContactInfo IS NULL;

SELECT ManagerID, COUNT(*)
FROM HumanResources.Employee2
GROUP BY ManagerID;

SELECT ManagerID AS Manager, COUNT(*) AS Reports
FROM HumanResources.Employee2
GROUP BY ManagerID;

SELECT ManagerID AS Manager, COUNT(*) AS Reports
FROM HumanResources.Employee2
WHERE EmployeeID != 5
GROUP BY ManagerID;

SELECT ManagerID AS Manager, COUNT(*) AS Reports
FROM HumanResources.Employee2
WHERE EmployeeID != 5
GROUP BY ManagerID
HAVING COUNT(*) > 3;

SELECT ProductID
FROM Sales.SalesOrderDetail
WHERE OrderQty > 30;

SELECT DISTINCT ProductID
FROM Sales.SalesOrderDetail
WHERE OrderQty > 30;

SELECT COUNT(*)
FROM Sales.SalesOrderDetail;

SELECT COUNT(SalesOrderID)
FROM Sales.SalesOrderDetail;

SELECT COUNT(DISTINCT SalesOrderID)
FROM Sales.SalesOrderDetail;


/* This script creates a couple of tables for use with
** several examples in Chapter 3 of Beginning SQL Server
** 2008 Programming
*/

CREATE TABLE Stores
(
  StoreCode    char(4)      NOT NULL PRIMARY KEY,
  Name         varchar(40)  NOT NULL,
  Address      varchar(40)  NULL,
  City         varchar(20)  NOT NULL,
  State        char(2)      NOT NULL,
  Zip          char(5)      NOT NULL
);

CREATE TABLE Sales
(
  OrderNumber  varchar(20)  NOT NULL PRIMARY KEY,
  StoreCode    char(4)      NOT NULL 
    FOREIGN KEY REFERENCES Stores(StoreCode),
  OrderDate    date         NOT NULL,
  Quantity     int          NOT NULL,
  Terms        varchar(12)  NOT NULL,
  TitleID      int          NOT NULL
);

INSERT INTO Stores
VALUES
   ('TEST', 'Test Store', '1234 Anywhere Street', 'Here', 'NY', '00319');

SELECT *
FROM Stores
WHERE StoreCode = 'TEST';

INSERT INTO Stores
   (StoreCode, Name, City, State, Zip)
VALUES
   ('TST2', 'Test Store', 'Here', 'NY', '00319');

SELECT *
FROM Stores
WHERE StoreCode = 'TST2';

EXEC sp_help Sales;

INSERT INTO Sales
   (StoreCode, OrderNumber, OrderDate, Quantity, Terms, TitleID)
VALUES
   ('TEST', 'TESTORDER', '01/01/1999', 10, 'NET 30', 1234567);

INSERT INTO Sales
   (StoreCode, OrderNumber, OrderDate, Quantity, Terms, TitleID)
VALUES
   ('TST2', 'TESTORDER2', '01/01/1999', 10, 'NET 30', 1234567),
   ('TST2', 'TESTORDER3', '02/01/1999', 10, 'NET 30', 1234567);

SELECT *
FROM Sales;

/* This next statement is going to use code to change the “current” database
** to AdventureWorks2008. This makes certain, right in the code that we are going
** to the correct database.
*/

USE AdventureWorks2008;

/* This next statement declares our working table.
** This particular table is actually a variable we are declaring on the fly.
*/

DECLARE @MyTable Table
(
   SalesOrderID      int,
   CustomerID        char(5)
);

/* Now that we have our table variable, we're ready to populate it with data 
** from our SELECT statement. Note that we could just as easily insert the 
** data into a permanent table (instead of a table variable).
*/
INSERT INTO @MyTable
   SELECT SalesOrderID, CustomerID
   FROM AdventureWorks2008.Sales.SalesOrderHeader
   WHERE SalesOrderID BETWEEN 44000 AND 44010;

-- Finally, let's make sure that the data was inserted like we think
SELECT * 
FROM @MyTable;

SELECT *
FROM Stores
WHERE StoreCode = 'TEST';

UPDATE Stores
SET City = 'There'
WHERE StoreCode = 'TEST';

UPDATE Stores
SET city = 'There', state = 'NY'
WHERE StoreCode = 'TEST';

UPDATE Stores
SET Name = Name + ' - ' + StoreCode;

SELECT *
FROM Stores

SELECT * 
FROM Stores
WHERE StoreCode = 'TEST';

DELETE Stores
WHERE StoreCode = 'TEST';

DELETE Sales
WHERE StoreCode = 'TEST';

DELETE Sales
WHERE StoreCode = 'TEST';

DELETE Sales
WHERE StoreCode = 'TST2';

