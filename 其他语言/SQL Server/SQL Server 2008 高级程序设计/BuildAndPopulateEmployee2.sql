USE AdventureWorks2008
GO

CREATE TABLE HumanResources.Employee2
(
  EmployeeID int NOT NULL,
  ManagerID int NULL REFERENCES HumanResources.Employee2(EmployeeID),
  JobTitle nvarchar(50) NOT NULL,
  LastName nvarchar(50) NOT NULL,
  FirstName nvarchar(50) NOT NULL,
    CONSTRAINT PK_Employee2_EmployeeID PRIMARY KEY CLUSTERED (EmployeeID ASC)
);

INSERT INTO HumanResources.Employee2(EmployeeID,ManagerID,JobTitle,LastName,FirstName)
VALUES
  (1, NULL, 'CEO','Smith', 'Hunter'),
  (2, 1, 'CFO', 'Jones', 'Drew'),
  (3, 1, 'COO','Lenzy','Sheila'),
  (4, 1, 'CTO', 'Huntington', 'Karla'),
  (5, 4, 'VP of Engineering', 'Gutierrez', 'Ron'),
  (8, 5, 'VP of Engineering', 'Gutierrez', 'Ron'),
  (9, 5, 'Software Engineer', 'Bray', 'Marky'),
  (10 ,5, 'Data Architect', 'Cheechov', 'Robert'),
  (11 ,5, 'Software Engineer', 'Gale', 'Sue'),
  (6, 4, 'VP of Professional Services', 'Cross', 'Gary'),
  (7, 4, 'VP of Security','Lebowski','Jeff');

