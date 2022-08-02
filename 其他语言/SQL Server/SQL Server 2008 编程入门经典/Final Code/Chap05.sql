SELECT
 e.NationalIDNumber, p.FirstName,p.LastName, City
FROM
 HumanResources.Employee e
INNER JOIN
 Person.Person p on p.BusinessEntityID = e.BusinessEntityID
INNER JOIN
 Person.BusinessEntityAddress a on p.BusinessEntityID = a.BusinessEntityID
INNER JOIN
 Person.Address pa on pa.AddressID = a.AddressID

CREATE DATABASE Accounting
ON
  (NAME = 'Accounting',
   FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL10.MSSQLSERVER\MSSQL\DATA\AccountingData.mdf',
   SIZE = 10,
   MAXSIZE = 50,
   FILEGROWTH = 5)
LOG ON
  (NAME = 'AccountingLog',
   FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL10.MSSQLSERVER\MSSQL\DATA\AccountingLog.ldf',
   SIZE = 5MB,
   MAXSIZE = 25MB,
   FILEGROWTH = 5MB);

GO

EXEC sp_helpdb 'Accounting'

USE Accounting
CREATE TABLE Customers
(
   CustomerNo    int         IDENTITY  NOT NULL,
   CustomerName  varchar(30)                NOT NULL,
   Address1      varchar(30)                NOT NULL,
   Address2      varchar(30)                NOT NULL,
   City          varchar(20)                NOT NULL,
   State         char(2)                    NOT NULL,
   Zip           varchar(10)                NOT NULL,
   Contact       varchar(25)                NOT NULL,
   Phone         char(15)                   NOT NULL,
   FedIDNo       varchar(9)                 NOT NULL,
   DateInSystem  smalldatetime              NOT NULL
)

EXEC sp_help Customers

USE Accounting

CREATE TABLE Employees
(
   EmployeeID       int          IDENTITY  NOT NULL,
   FirstName        varchar(25)            NOT NULL,
   MiddleInitial    char(1)                NULL,
   LastName         varchar(25)            NOT NULL,
   Title            varchar(25)            NOT NULL,
   SSN              varchar(11)            NOT NULL,
   Salary           money                  NOT NULL,
   PriorSalary      money                  NOT NULL,
   LastRaise AS Salary - PriorSalary,
   HireDate         date                   NOT NULL,
   TerminationDate  date                   NULL,
   ManagerEmpID     int                    NOT NULL,
   Department       varchar(25)            NOT NULL
)

EXEC sp_helpdb Accounting

ALTER DATABASE Accounting
   MODIFY FILE 
   (NAME = Accounting,
    SIZE = 100MB)

EXEC sp_helpdb Accounting

EXEC sp_help Employees

ALTER TABLE Employees
   ADD 
      PreviousEmployer   varchar(30)   NULL

ALTER TABLE Employees
   ADD
      DateOfBirth     date       NULL,
      LastRaiseDate   date       NOT NULL
         DEFAULT '2008-01-01'

EXEC sp_help Employees

USE Accounting

DROP TABLE Customers, Employees

USE master

DROP DATABASE Accounting


