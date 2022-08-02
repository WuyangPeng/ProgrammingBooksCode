CREATE TABLE MemberDetails
(
    MemberId integer,
    FirstName nvarchar(50),
    LastName nvarchar(50),
    DateOfBirth datetime,
    Street varchar(100),
    City varchar(75),
    State varchar(75),
    ZipCode varchar(12),
    Email varchar(200),
    DateOfJoining datetime

);

CREATE TABLE Attendance
(
    MeetingDate datetime,
    Location varchar(200),
    MemberAttended char(1),
    MemberId integer
);

CREATE TABLE Films
(
    FilmId integer,
    FilmName varchar(100),
    YearReleased integer,
    PlotSummary varchar(2000),
    AvailableOnDVD char(1),
    Rating integer,
    CategoryId integer 
);

CREATE TABLE Category
(
    CategoryId integer,
    Category varchar(100) 
);

CREATE TABLE FavCategory
(
    CategoryId integer,
    MemberId integer 
);


