USE BRegExp;
CREATE TABLE People
 (ID INT PRIMARY KEY AUTO_INCREMENT,
  LastName VARCHAR(20),
  FirstName VARCHAR(20),
  DateOfBirth DATE);
INSERT INTO People
 (ID, LastName, FirstName, DateOfBirth)
  VALUES
   (NULL, 'Smith', 'George', '1959-11-11'), 
   (NULL, 'Armada', 'Francis', '1971-03-08'),
   (NULL, 'Schmidt', 'Georg', '1981-10-09'),
   (NULL, 'Clingon', 'David', '1944-11-01'),
   (NULL, 'Dalek', 'Eve', '1953-04-04'),
   (NULL, 'Bush', 'Harold', '1939-11-08'),
   (NULL, 'Burns', 'Geoffrey', '1960-08-02'),
   (NULL, 'Builth', 'Wellstone', '1947-10-05'),
   (NULL, 'Thomas', 'Dylan', '1984-07-07'),
   (NULL, 'LLareggub', 'Dai', '1950-11-02'),
   (NULL, 'Barns', 'Samuel', '1944-06-01'),
   (NULL, 'Claverhouse', 'Henry', '1931-08-12'),
   (NULL, 'Litmus', 'Susie', '1954-11-03');