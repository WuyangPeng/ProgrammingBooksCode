
USE master

IF EXISTS 
	(SELECT 1 
		FROM sys.databases
		WHERE name = 'Chapter4DB')
	DROP DATABASE Chapter4DB
GO

CREATE DATABASE Chapter4DB
GO

USE Chapter4DB

CREATE TABLE [dbo].[Address] (
	[AddressID] [tinyint] NULL ,
	[Address] [char] (15) NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[VendorAddress] (
	[VendorID] [tinyint] NULL ,
	[AddressID] [tinyint] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[Vendors] (
	[VendorName] [char] (30) NULL ,
	[VendorID] [tinyint] NULL 
) ON [PRIMARY]
GO

INSERT INTO Vendors
(VendorName, VendorID)
VALUES
('Don''s Database Design Shop', 1)

INSERT INTO Vendors
(VendorName, VendorID)
VALUES
('Dave''s Data', 2)

INSERT INTO Vendors
(VendorName, VendorID)
VALUES
('The SQL Sequel', 3)

INSERT INTO VendorAddress
(VendorID, AddressID)
VALUES
(1, 1)

INSERT INTO VendorAddress
(VendorID, AddressID)
VALUES
(2, 3)

INSERT INTO Address
(Address, AddressID)
VALUES
('1234 Anywhere', 1)

INSERT INTO Address
(Address, AddressID)
VALUES
('567 Main St.', 3)

INSERT INTO Address
(Address)
VALUES
('999 1st St.')

INSERT INTO Address
(Address)
VALUES
('1212 Smith Ave')

INSERT INTO Address
(Address)
VALUES
('364 Westin')