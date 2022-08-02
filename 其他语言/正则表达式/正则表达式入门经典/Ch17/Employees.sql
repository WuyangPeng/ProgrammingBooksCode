USE BRegExp;
CREATE TABLE Employees
 (ID INT PRIMARY KEY AUTO_INCREMENT,
  LastName VARCHAR(20),
  FirstName VARCHAR(20),
  DateOfBirth DATE,
  SSN VARCHAR(11),
  Department VARCHAR(18),
  Skills VARCHAR(50),
  Comments VARCHAR(100));
INSERT INTO Employees
 (ID, LastName, FirstName, DateOfBirth, SSN, Department, Skills, Comments)
  VALUES
   (NULL, 'Smith', 'George', '1959-11-11', '123-45-6789', 'Data Management', 'Analysis Services, Business Intelligence, Data Transformation Services', 'Good skills in SQL Server 2000. Can be grumpy at times.'), 
   (NULL, 'Armada', 'Francis', '1971-03-08', '881-32-8913', 'Sales', NULL, 'Effective salesman. Particularly good at relating to the business needs of clients.'),
   (NULL, 'Schmidt', 'Georg', '1981-10-09', '456-12-1234', 'Admin', NULL, 'Effective head of Admin Department. Good communicator.'),
   (NULL, 'Clingon', 'David', '1944-11-01', '234-59-3489', 'Data Management', 'DBA, SQL DMO', 'Good database administrator. Lots of experience.'),
   (NULL, 'Dalek', 'Eve', '1953-04-04', '345-19-8822', 'Sales', NULL, 'Good sales record. Technically informed.'),
   (NULL, 'Bush', 'Harold', '1939-11-08', '378-12-0021', 'Public Relations', NULL, 'An old hand. Handled virus crisis excellently last year.'),
   (NULL, 'Burns', 'Geoffrey', '1960-08-02', '000-12-3872', 'Development', 'C#, .NET', 'Good .NET programmer. Can lack vision of bigger picture at times.'),
   (NULL, 'Builth', 'Wellstone', '1947-10-05', '009-348-234', 'Development', 'VB.NET, .NET, ADO.NET', 'Sound. Useful member of team.'),
   (NULL, 'Thomas', 'Dylan', '1984-07-07', '310-23-3891', 'Data Management', 'DTS', 'Great guy for those data transformation jobs.'),
   (NULL, 'LLareggub', 'Dai', '1950-11-02', '210-23-4578', 'Data Processing', 'Data Transformation Services, SQL DMO', 'Good guy. Could be more proactive.'),
   (NULL, 'Barns', 'Samuel', '1944-06-01', '238-12-9999', 'International Sales', 'Good French and German skills.', 'Good salesman.'),
   (NULL, 'Claverhouse', 'Henry', '1931-08-12', '723-123-234', 'International Sales', NULL, 'Semi-retired now. Still effective though.'),
   (NULL, 'Litmus', 'Susie', '1954-11-03', '123-34-4888', 'Admin', 'Good organizer.', 'Deputy to Georg Schmidt.');