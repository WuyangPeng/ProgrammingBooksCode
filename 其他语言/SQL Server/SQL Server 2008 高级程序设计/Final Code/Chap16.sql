CREATE XML SCHEMA COLLECTION ProductDescriptionSchemaCollectionSummaryRequired 
  AS
    '<xsd:schema targetNamespace="http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelWarrAndMain"
        xmlns="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelWarrAndMain"
        elementFormDefault="qualified"
        xmlns:xsd="http://www.w3.org/2001/XMLSchema" >
        <xsd:element name="Warranty"  >
            <xsd:complexType>
                <xsd:sequence>
                    <xsd:element name="WarrantyPeriod" type="xsd:string"  />
                    <xsd:element name="Description" type="xsd:string"  />
                </xsd:sequence>
            </xsd:complexType>
        </xsd:element>
    </xsd:schema>
    <xs:schema targetNamespace="http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelDescription"
        xmlns="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/
ProductModelDescription"
        elementFormDefault="qualified"
        xmlns:mstns="http://tempuri.org/XMLSchema.xsd"
        xmlns:xs="http://www.w3.org/2001/XMLSchema"
        xmlns:wm="http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/
ProductModelWarrAndMain" >
        <xs:import namespace="http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelWarrAndMain" />
        <xs:element name="ProductDescription" type="ProductDescription" />
            <xs:complexType name="ProductDescription">
                <xs:sequence>
                    <xs:element name="Summary" type="Summary" minOccurs="1" />
                </xs:sequence>
                <xs:attribute name="ProductModelID" type="xs:string" />
                <xs:attribute name="ProductModelName" type="xs:string" />
            </xs:complexType>
            <xs:complexType name="Summary" mixed="true" >
                <xs:sequence>
                    <xs:any processContents="skip" namespace="http://www.w3.org/
1999/xhtml" minOccurs="0" maxOccurs="unbounded" />
                </xs:sequence>
            </xs:complexType>
    </xs:schema>';



DROP XML SCHEMA COLLECTION ProductDescriptionSchemaCollectionSummaryRequired;


SELECT ProductModelID, Instructions.query('declare namespace PI="http://
schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions";
    /PI:root/PI:Location/PI:step') AS Steps
FROM Production.ProductModel
WHERE ProductModelID = 66;


WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelManuInstructions' AS PI)

SELECT ProductModelID, Instructions.query('/PI:root/PI:Location/PI:step') AS Steps
FROM Production.ProductModel
WHERE ProductModelID = 66;


WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelManuInstructions' AS PI)

SELECT ProductModelID,
    Instructions.value('(/PI:root/PI:Location/@LaborHours)[1]',
                       'decimal (5,2)') AS Location
FROM Production.ProductModel
WHERE ProductModelID = 66;


WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelManuInstructions' AS PI)

UPDATE Production.ProductModel
SET Instructions.modify('replace value of (/PI:root/PI:Location/@LaborHours)[1] 
with 1.75')
WHERE ProductModelID = 66;


WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions' AS PI)

SELECT ProductModelID, Instructions.value('(/PI:root/PI:Location/@LaborHours)[1]', 'decimal (5,2)') AS Location
FROM Production.ProductModel
WHERE ProductModelID = 66;


WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions' AS PI)   

SELECT ProductModelID,
    Instructions.value('(/PI:root/PI:Location/@LaborHours)[1]',
                       'decimal (5,2)') AS Location
FROM Production.ProductModel
WHERE ProductModelID = 66;


WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/ProductModelManuInstructions' AS PI)

SELECT pm.ProductModelID,
    pmi.Location.value('./@LocationID', 'int') AS LocationID,
    pmi.Location.value('./@LaborHours', 'decimal(5,2)') AS LaborHours
FROM Production.ProductModel pm
CROSS APPLY pm.Instructions.nodes('/PI:root/PI:Location') AS pmi(Location);



WITH XMLNAMESPACES ('http://schemas.microsoft.com/sqlserver/2004/07/
adventure-works/ProductModelManuInstructions' AS PI)

SELECT ProductModelID, Instructions
FROM Production.ProductModel
WHERE Instructions.exist('/PI:root/PI:Location/PI:step/PI:specs') = 1

USE AdventureWorks2008;

SELECT Sales.Customer.CustomerID,
  Sales.Customer.AccountNumber,
  Sales.SalesOrderHeader.SalesOrderID,
  CAST(Sales.SalesOrderHeader.OrderDate AS date) AS OrderDate
FROM Sales.Customer
JOIN Sales.SalesOrderHeader
  ON Sales.Customer.CustomerID = Sales.SalesOrderHeader.CustomerID
WHERE Sales.Customer.CustomerID = 29890 OR Sales.Customer.CustomerID = 30067;


USE AdventureWorks2008;

SELECT Sales.Customer.CustomerID,
  Sales.Customer.AccountNumber,
  Sales.SalesOrderHeader.SalesOrderID,
  CAST(Sales.SalesOrderHeader.OrderDate AS date) AS OrderDate
FROM Sales.Customer
JOIN Sales.SalesOrderHeader
  ON Sales.Customer.CustomerID = Sales.SalesOrderHeader.CustomerID
WHERE Sales.Customer.CustomerID = 29890 OR Sales.Customer.CustomerID = 30067
FOR XML RAW;


USE AdventureWorks2008;

SELECT Customer.CustomerID,
  Customer.AccountNumber,
  [Order].SalesOrderID,
  CAST([Order].OrderDate AS date) AS OrderDate
FROM Sales.Customer Customer
JOIN Sales.SalesOrderHeader [Order]
  ON Customer.CustomerID = [Order].CustomerID
WHERE Customer.CustomerID = 29890 OR Customer.CustomerID = 30067
FOR XML AUTO;


SELECT CustomerID, COUNT(*)
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;


SELECT CustomerID AS '@CustomerID', COUNT(*)
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;


SELECT CustomerID AS '@CustomerID',
       COUNT(*) AS '@OrderCount'
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;


SELECT CustomerID,
       COUNT(*) AS '@OrderCount'
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;


SELECT CustomerID,
       COUNT(*) AS 'CustomerID/OrderCount'
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;



SELECT CustomerID,
       COUNT(*) AS 'CustomerID/@OrderCount'
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;


SELECT COUNT(*) AS 'CustomerID/@OrderCount',
       CustomerID
FROM Sales.SalesOrderHeader Orders
WHERE CustomerID = 29890 OR CustomerID = 30067
GROUP BY CustomerID
FOR XML PATH;


USE Accounting;

DECLARE @idoc      int;
DECLARE @xmldoc    nvarchar(4000);

-- define the XML document
SET @xmldoc = '
<ROOT>
<Shipper ShipperID="100" CompanyName="Billy Bob&apos;s Great Shipping"/>
<Shipper ShipperID="101" CompanyName="Fred&apos;s Freight"/>
</ROOT>
';

--Load and parse the XML document in memory
EXEC sp_xml_preparedocument @idoc OUTPUT, @xmldoc;

--List out what our shippers table looks like before the insert
SELECT * FROM Shippers;

-- ShipperID is an IDENTITY column, so we need to allow direct updates
SET IDENTITY_INSERT Shippers ON

--See our XML data in a tabular format
SELECT * FROM OPENXML (@idoc, '/ROOT/Shipper', 0) WITH (
    ShipperID           int,
    CompanyName         nvarchar(40));

--Perform and insert based on that data
INSERT INTO Shippers
(ShipperID, ShipperName)
SELECT * FROM OPENXML (@idoc, '/ROOT/Shipper', 0) WITH (
    ShipperID           int,
    CompanyName         nvarchar(40));

--Set things back to normal
SET IDENTITY_INSERT Shippers OFF;

--Now look at the Shippers table after our insert
SELECT * FROM Shippers;

--Now clear the XML document from memory
EXEC sp_xml_removedocument @idoc;





