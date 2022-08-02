/* Note that this was mostly automatically scripted from SQL Server, so don't
** take this as an example for how you should format things when you write your
** own scripts.
*/
USE master
CREATE DATABASE Accounting
GO

USE Accounting
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Employees](
	[EmployeeID] [int] IDENTITY(1,1) NOT NULL,
	[FirstName] [varchar](25) NOT NULL,
	[MiddleInitial] [char](1) NULL,
	[LastName] [varchar](25) NOT NULL,
	[Title] [varchar](25) NOT NULL,
	[SSN] [varchar](11) NOT NULL,
	[Salary] [money] NOT NULL,
	[PriorSalary] [money] NOT NULL,
	[LastRaise]  AS ([Salary]-[PriorSalary]),
	[HireDate] [date] NOT NULL,
	[TerminationDate] [date] NULL,
	[ManagerEmpID] [int] NOT NULL,
	[Department] [varchar](25) NOT NULL,
 CONSTRAINT [PK_EmployeeID] PRIMARY KEY CLUSTERED 
(
	[EmployeeID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY],
 CONSTRAINT [AK_EmployeeSSN] UNIQUE NONCLUSTERED 
(
	[SSN] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Customers](
	[CustomerNo] [int] IDENTITY(1,1) NOT NULL,
	[CustomerName] [varchar](30) NOT NULL,
	[Address1] [varchar](30) NOT NULL CONSTRAINT [CN_CustomerAddress]  DEFAULT ('UNKNOWN'),
	[Address2] [varchar](30) NOT NULL,
	[City] [varchar](20) NOT NULL,
	[State] [char](2) NOT NULL,
	[Zip] [varchar](10) NOT NULL,
	[Contact] [varchar](25) NOT NULL,
	[Phone] [char](15) NOT NULL,
	[FedIDNo] [varchar](9) NOT NULL,
	[DateInSystem] [datetime] NOT NULL CONSTRAINT [CN_CustomerDefaultDateInSystem]  DEFAULT (getdate()),
PRIMARY KEY CLUSTERED 
(
	[CustomerNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF

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
   )

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
    GETDATE ())

GO
/****** Object:  Table [dbo].[Shippers]    Script Date: 10/06/2007 07:12:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Shippers](
	[ShipperID] [int] IDENTITY(1,1) NOT NULL,
	[ShipperName] [varchar](30) NOT NULL,
	[DateInSystem] [datetime] NOT NULL DEFAULT (getdate()),
PRIMARY KEY CLUSTERED 
(
	[ShipperID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Orders](
	[OrderID] [int] IDENTITY(1,1) NOT NULL,
	[CustomerNo] [int] NOT NULL,
	[OrderDate] [date] NOT NULL,
	[EmployeeID] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[OrderID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[OrderDetails](
	[OrderID] [int] NOT NULL,
	[PartNo] [varchar](10) NOT NULL,
	[Description] [varchar](25) NOT NULL,
	[UnitPrice] [money] NOT NULL,
	[Qty] [int] NOT NULL,
 CONSTRAINT [PKOrderDetails] PRIMARY KEY CLUSTERED 
(
	[OrderID] ASC,
	[PartNo] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[Customers]  WITH NOCHECK ADD  CONSTRAINT [CN_CustomerDateInSystem] CHECK  (([DateInSystem]<=getdate()))
GO
ALTER TABLE [dbo].[Customers] CHECK CONSTRAINT [CN_CustomerDateInSystem]
GO

ALTER TABLE [dbo].[Customers]  WITH NOCHECK ADD  CONSTRAINT [CN_CustomerPhoneNo] CHECK  (([Phone] like '([0-9][0-9][0-9]) [0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]'))
GO
ALTER TABLE [dbo].[Customers] CHECK CONSTRAINT [CN_CustomerPhoneNo]
GO

ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_EmployeeHasManager] FOREIGN KEY([ManagerEmpID])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_EmployeeHasManager]
GO

ALTER TABLE [dbo].[OrderDetails]  WITH CHECK ADD  CONSTRAINT [FKOrderContainsDetails] FOREIGN KEY([OrderID])
REFERENCES [dbo].[Orders] ([OrderID])
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[OrderDetails] CHECK CONSTRAINT [FKOrderContainsDetails]
GO

ALTER TABLE [dbo].[Orders]  WITH CHECK ADD FOREIGN KEY([CustomerNo])
REFERENCES [dbo].[Customers] ([CustomerNo])
GO

ALTER TABLE [dbo].[Orders]  WITH CHECK ADD  CONSTRAINT [FK_EmployeeCreatesOrder] FOREIGN KEY([EmployeeID])
REFERENCES [dbo].[Employees] ([EmployeeID])
GO
ALTER TABLE [dbo].[Orders] CHECK CONSTRAINT [FK_EmployeeCreatesOrder]
GO

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
   )


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
   )


INSERT INTO Shippers
   (ShipperName)
VALUES
   ('United Parcel Service')
