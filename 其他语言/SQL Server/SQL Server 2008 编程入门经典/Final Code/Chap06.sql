USE Accounting;

CREATE TABLE Customers
(
   CustomerNo     int   IDENTITY   NOT NULL
      PRIMARY KEY,
   CustomerName   varchar(30)      NOT NULL,
   Address1       varchar(30)      NOT NULL,
   Address2       varchar(30)      NOT NULL,
   City           varchar(20)      NOT NULL,
   State          char(2)          NOT NULL,
   Zip            varchar(10)      NOT NULL,
   Contact        varchar(25)      NOT NULL,
   Phone          char(15)         NOT NULL,
   FedIDNo        varchar(9)       NOT NULL,
   DateInSystem   smalldatetime    NOT NULL
);

USE Accounting

ALTER TABLE Employees
   ADD CONSTRAINT PK_EmployeeID
   PRIMARY KEY (EmployeeID);

USE Accounting

CREATE TABLE Orders
(
   OrderID      int   IDENTITY   NOT NULL
      PRIMARY KEY,
   CustomerNo   int              NOT NULL
      FOREIGN KEY REFERENCES Customers(CustomerNo),
   OrderDate    date             NOT NULL,
   EmployeeID   int              NOT NULL
);

ALTER TABLE Orders
   ADD CONSTRAINT FK_EmployeeCreatesOrder
   FOREIGN KEY (EmployeeID) REFERENCES Employees(EmployeeID);

INSERT INTO Employees
   (
   FirstName,
   LastName,
   Title,
   SSN,
   Salary,
   PriorSalary,
   HireDate,
   ManagerEmpID,
   Department
   )
VALUES
   (
   'Billy Bob',
   'Boson',
   'Head Cook & Bottle Washer',
   '123-45-6789',
   100000,
   80000,
   '1990-01-01',
   1,
   'Cooking and Bottling'
   );

ALTER TABLE Employees
   ADD CONSTRAINT FK_EmployeeHasManager
   FOREIGN KEY (ManagerEmpID) REFERENCES Employees(EmployeeID);


CREATE TABLE Employees (
   EmployeeID        int   IDENTITY   NOT NULL
      PRIMARY KEY,
   FirstName         varchar (25)     NOT NULL,
   MiddleInitial     char (1)         NULL,
   LastName          varchar (25)     NOT NULL,
   Title             varchar (25)     NOT NULL,
   SSN               varchar (11)     NOT NULL,
   Salary            money            NOT NULL,
   PriorSalary       money            NOT NULL,
   LastRaise AS Salary -PriorSalary,
   HireDate          smalldatetime    NOT NULL,
   TerminationDate   smalldatetime    NULL,
   ManagerEmpID      int              NOT NULL 
      REFERENCES Employees(EmployeeID),
   Department        varchar (25)     NOT NULL
);

CREATE TABLE OrderDetails
(
   OrderID      int           NOT NULL,
   PartNo       varchar(10)   NOT NULL,
   Description  varchar(25)   NOT NULL,
   UnitPrice    money         NOT NULL,
   Qty          int           NOT NULL,
   CONSTRAINT    PKOrderDetails
      PRIMARY KEY   (OrderID, PartNo),
   CONSTRAINT    FKOrderContainsDetails
      FOREIGN KEY   (OrderID)
         REFERENCES Orders(OrderID)
         ON UPDATE  NO ACTION
         ON DELETE  CASCADE
);

INSERT INTO OrderDetails
VALUES
   (1, '4X4525', 'This is a part', 25.00, 2);

INSERT INTO Customers -- Our Customer. 
                      -- Remember that CustomerNo is 
                      -- an Identity column
VALUES
   ('Billy Bob''s Shoes', 
   '123 Main St.',
   ' ',
   'Vancouver',
   'WA',
   '98685',
   'Billy Bob',
   '(360) 555-1234',
   '931234567',
   GETDATE()
   );

INSERT INTO Orders
   (CustomerNo, OrderDate, EmployeeID)
VALUES
   (1, GETDATE(), 1);


INSERT INTO OrderDetails
VALUES
   (1, '4X4525', 'This is a part', 25.00, 2)

INSERT INTO OrderDetails
VALUES
   (1, '0R2400', 'This is another part', 50.00, 2);

SELECT OrderID, PartNo FROM OrderDetails;

USE Accounting

-- First, let's look at the rows in both tables
SELECT * 
FROM Orders;

SELECT * 
FROM OrderDetails;

-- Now, let's delete the Order record
DELETE Orders 
WHERE OrderID = 1;

-- Finally, look at both sets of data again
-- and see the CASCADE effect
SELECT * 
FROM Orders;

SELECT * 
FROM OrderDetails;

CREATE TABLE Shippers
(
   ShipperID     int   IDENTITY   NOT NULL
      PRIMARY KEY,
   ShipperName   varchar(30)      NOT NULL,
   Address       varchar(30)      NOT NULL,
   City          varchar(25)      NOT NULL,
   State         char(2)          NOT NULL,
   Zip           varchar(10)      NOT NULL,
   PhoneNo       varchar(14)      NOT NULL
      UNIQUE
);

ALTER TABLE Employees
   ADD CONSTRAINT AK_EmployeeSSN
   UNIQUE (SSN);

ALTER TABLE Customers
   ADD CONSTRAINT CN_CustomerDateInSystem
   CHECK
   (DateInSystem <= GETDATE ());

INSERT INTO Customers
   (CustomerName, Address1, Address2, City, State, Zip, Contact,
    Phone, FedIDNo, DateInSystem)
VALUES
   ('Customer1', 'Address1', 'Add2', 'MyCity', 'NY', '55555',
    'No Contact', '553-1212', '930984954', '12-31-2049');

CREATE TABLE Shippers
(
   ShipperID      int   IDENTITY   NOT NULL
      PRIMARY KEY,
   ShipperName    varchar(30)      NOT NULL,
   DateInSystem   smalldatetime    NOT NULL
      DEFAULT GETDATE ()
);

INSERT INTO Shippers
   (ShipperName)
VALUES
   ('United Parcel Service');

SELECT * FROM Shippers;

ALTER TABLE Customers
   ADD CONSTRAINT CN_CustomerDefaultDateInSystem
      DEFAULT GETDATE() FOR DateInSystem;

ALTER TABLE Customers
   ADD CONSTRAINT CN_CustomerAddress
      DEFAULT 'UNKNOWN' FOR Address1;

INSERT INTO Customers
   (CustomerName,
    Address1,
    Address2,
    City,
    State,
    Zip,
    Contact,
    Phone,
    FedIDNo,
    DateInSystem)
VALUES
   ('MyCust',
    '123 Anywhere',
    '',
    'Reno',
    'NV',
    80808,
    'Joe Bob',
    '555-1212',
    '931234567',
    GETDATE());

ALTER TABLE Customers
   ADD CONSTRAINT CN_CustomerPhoneNo
   CHECK
  (Phone LIKE '([0-9][0-9][0-9]) [0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]');

ALTER TABLE Customers
   WITH NOCHECK
   ADD CONSTRAINT CN_CustomerPhoneNo
   CHECK
   (Phone LIKE '([0-9][0-9][0-9]) [0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]');

INSERT INTO Customers
   (CustomerName,
    Address1,
    Address2,
    City,
    State,
    Zip,
    Contact,
    Phone,
    FedIDNo,
    DateInSystem)
VALUES
   ('MyCust',
    '123 Anywhere',
    '',
    'Reno',
    'NV',
    80808,
    'Joe Bob',
    '(800) 555-1212',
    '931234567',
    GETDATE());

SELECT CustomerNo, CustomerName, Phone FROM Customers;

ALTER TABLE Customers
   NOCHECK
   CONSTRAINT CN_CustomerPhoneNo;

INSERT INTO Customers
   (CustomerName,
    Address1,
    Address2,
    City,
    State,
    Zip,
    Contact,
    Phone,
    FedIDNo,
    DateInSystem)
VALUES
   ('MyCust',
    '123 Anywhere',
    '',
    'Reno',
    'NV',
    80808,
    'Joe Bob',
    '555-1212',
    '931234567',
    GETDATE());

EXEC sp_helpconstraint Customers;

ALTER TABLE Customers
   CHECK
   CONSTRAINT CN_CustomerPhoneNo;

CREATE RULE SalaryRule
   AS @Salary > 0;

EXEC sp_helptext SalaryRule;

EXEC sp_bindrule 'SalaryRule', 'Employees.Salary';

EXEC sp_unbindrule 'Employees.Salary';

CREATE DEFAULT SalaryDefault
   AS 0;

EXEC sp_bindefault 'SalaryDefault', 'Employees.Salary';

