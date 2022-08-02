SELECT *
FROM Person.Person
INNER JOIN HumanResources.Employee
    ON Person.Person.BusinessEntityID = HumanResources.Employee.BusinessEntityID

SELECT Person.BusinessEntity.*, JobTitle
FROM Person.BusinessEntity
INNER JOIN HumanResources.Employee
    ON Person.BusinessEntity.BusinessEntityID = HumanResources.Employee.BusinessEntityID

SELECT Person.BusinessEntity.*, BusinessEntityID
FROM Person.BusinessEntity
INNER JOIN HumanResources.Employee
        ON Person.BusinessEntity.BusinessEntityID = HumanResources.Employee.BusinessEntityID

SELECT Person. BusinessEntity.*, HumanResources.Employee. BusinessEntityID
FROM Person. BusinessEntity
INNER JOIN HumanResources.Employee
    ON Person. BusinessEntity. BusinessEntityID 
        = HumanResources.Employee. BusinessEntityID

SELECT pbe.*, hre.BusinessEntityID
FROM Person.BusinessEntity pbe
INNER JOIN HumanResources.Employee hre
    ON pbe.BusinessEntityID = hre.BusinessEntityID

SELECT pbe.*, HumanResources.Employee.BusinessEntityID
FROM Person.BusinessEntity pbe
INNER JOIN HumanResources.Employee hre
    ON pbe.BusinessEntityID = hre.BusinessEntityID

SELECT pbe.BusinessEntityID, hre.JobTitle, pp.FirstName, pp.LastName
FROM Person.BusinessEntity pbe
INNER JOIN HumanResources.Employee hre
    ON pbe.BusinessEntityID = hre.BusinessEntityID
INNER JOIN Person.Person pp
	ON pbe.BusinessEntityID = pp.BusinessEntityID
WHERE hre.BusinessEntityID < 4

SELECT COUNT(*)
FROM Person.BusinessEntity

SELECT LastName + ', ' + FirstName AS Name, AccountNumber

SELECT CAST(LastName + ', ' + FirstName AS varchar(35)) AS Name, AccountNumber
FROM Person.Person pp
JOIN Sales.Customer sc
 ON pp.BusinessEntityID = sc.PersonID

SELECT sso.SpecialOfferID, Description, DiscountPct, ProductID
FROM Sales.SpecialOffer sso
JOIN Sales.SpecialOfferProduct ssop
ON sso.SpecialOfferID = ssop.SpecialOfferID
WHERE sso.SpecialOfferID != 1

SELECT sso.SpecialOfferID, Description, DiscountPct, ProductID
FROM Sales.SpecialOffer sso
LEFT OUTER JOIN Sales.SpecialOfferProduct ssop
 ON sso.SpecialOfferID = ssop.SpecialOfferID
WHERE sso.SpecialOfferID != 1

SELECT sso.SpecialOfferID, Description, DiscountPct, ProductID
FROM Sales.SpecialOfferProduct ssop
RIGHT OUTER JOIN Sales.SpecialOffer sso
 ON ssop.SpecialOfferID = sso.SpecialOfferID 
WHERE sso.SpecialOfferID != 1

SELECT Description
FROM Sales.SpecialOfferProduct ssop
RIGHT OUTER JOIN Sales.SpecialOffer sso
 ON ssop.SpecialOfferID = sso.SpecialOfferID
WHERE sso.SpecialOfferID != 1
  AND ssop.SpecialOfferID IS NULL

IF (NULL=NULL)
   PRINT 'It Does'
ELSE
   PRINT 'It Doesn''t'

SELECT pbe.BusinessEntityID, hre.JobTitle, pp.FirstName, pp.LastName
FROM Person.BusinessEntity pbe
INNER JOIN HumanResources.Employee hre
    ON pbe.BusinessEntityID = hre.BusinessEntityID
INNER JOIN Person.Person pp
    ON pbe.BusinessEntityID = pp.BusinessEntityID
WHERE hre.BusinessEntityID < 4

SELECT COUNT(*)
FROM Person.BusinessEntity

SELECT  pp.BusinessEntityID, pp.FirstName, pp.LastName 
FROM Person.Person pp
LEFT OUTER JOIN HumanResources.Employee hre
    ON pp.BusinessEntityID = hre.BusinessEntityID
WHERE hre.BusinessEntityID IS NULL

SELECT  pp.BusinessEntityID, pp.FirstName, pp.LastName 
FROM HumanResources.Employee hre
RIGHT OUTER JOIN Person.Person pp
	ON pp.BusinessEntityID = hre.BusinessEntityID
WHERE hre.BusinessEntityID IS NULL

USE Chapter4DB

SELECT v.VendorName
FROM Vendors v

SELECT v.VendorName
FROM Vendors v
LEFT OUTER JOIN VendorAddress va
             ON v.VendorID = va.VendorID

SELECT * 
FROM VendorAddress

SELECT v.VendorName, va.VendorID
FROM Vendors v
LEFT OUTER JOIN VendorAddress va
             ON v.VendorID = va.VendorID

SELECT v.VendorName, a.Address
FROM Vendors v
LEFT OUTER JOIN VendorAddress va
             ON v.VendorID = va.VendorID
JOIN Address a
   ON va.AddressID = a.AddressID

SELECT v.VendorName, a.Address
FROM Vendors v
LEFT OUTER JOIN VendorAddress va
             ON v.VendorID = va.VendorID
LEFT OUTER JOIN Address a
             ON va.AddressID = a.AddressID

SELECT v.VendorName, a.Address
FROM VendorAddress va
JOIN Address a
   ON va.AddressID = a.AddressID
RIGHT OUTER JOIN Vendors v
              ON v.VendorID = va.VendorID

SELECT v.VendorName, a.Address
FROM VendorAddress va
JOIN Address a
   ON va.AddressID = a.AddressID
RIGHT OUTER JOIN Vendors v
              ON v.VendorID = va.VendorID

SELECT a.Address, va.AddressID
FROM VendorAddress va
FULL JOIN Address a
       ON va.AddressID = a.AddressID

SELECT a.Address, va.AddressID, v.VendorID, v.VendorName
FROM VendorAddress va
FULL JOIN Address a
       ON va.AddressID = a.AddressID
FULL JOIN Vendors v
       ON va.VendorID = v.VendorID

SELECT v.VendorName, a.Address
FROM Vendors v
CROSS JOIN Address a

USE AdventureWorks2008

SELECT *
FROM Person.Person
INNER JOIN HumanResources.Employee
    ON Person.Person.BusinessEntityID = HumanResources.Employee.BusinessEntityID

SELECT *
FROM Person.Person, HumanResources.Employee
WHERE Person.Person.BusinessEntityID = HumanResources.Employee.BusinessEntityID

SELECT sso.SpecialOfferID, Description, DiscountPct, ProductID
FROM Sales.SpecialOffer sso
JOIN Sales.SpecialOfferProduct ssop
ON sso.SpecialOfferID = ssop.SpecialOfferID
WHERE sso.SpecialOfferID != 1

SELECT sso.SpecialOfferID, Description, DiscountPct, ProductID
FROM Sales.SpecialOffer sso,
     Sales.SpecialOfferProduct ssop
WHERE sso.SpecialOfferID *= ssop.SpecialOfferID
  AND sso.SpecialOfferID != 1

USE Chapter4DB

SELECT v.VendorName, a.Address
FROM Vendors v
CROSS JOIN Address a

USE Chapter4DB

SELECT v.VendorName, a.Address
FROM Vendors v, Address a

USE AdventureWorks2008

SELECT FirstName + ' ' + LastName AS Name, pe.EmailAddress
       EmailAddress
FROM Person.Person pp
JOIN Person.EmailAddress pe
  ON pp.BusinessEntityID = pe.BusinessEntityID
JOIN Sales.Customer sc
  ON pp.BusinessEntityID = sc.CustomerID

UNION

SELECT FirstName + ' ' + LastName AS Name, pe.EmailAddress
       EmailAddress
FROM Person.Person pp
JOIN Person.EmailAddress pe
  ON pp.BusinessEntityID = pe.BusinessEntityID
JOIN Purchasing.Vendor pv
  ON pp.BusinessEntityID = pv.BusinessEntityID

CREATE TABLE UnionTest1
(
   idcol   int       IDENTITY,
   col2    char(3),
)

CREATE TABLE UnionTest2
(
   idcol   int       IDENTITY,
   col4    char(3),
)

INSERT INTO UnionTest1
VALUES
   ('AAA')

INSERT INTO UnionTest1
VALUES
   ('BBB')

INSERT INTO UnionTest1
VALUES
   ('CCC')

INSERT INTO UnionTest2
VALUES
   ('CCC')

INSERT INTO UnionTest2
VALUES
   ('DDD')

INSERT INTO UnionTest2
VALUES
   ('EEE')

SELECT col2 
FROM UnionTest1

UNION

SELECT col4
FROM UnionTest2

PRINT 'Divider Line--------------------------'

SELECT col2 
FROM UnionTest1

UNION ALL

SELECT col4
FROM UnionTest2

DROP TABLE UnionTest1
DROP TABLE UnionTest2
