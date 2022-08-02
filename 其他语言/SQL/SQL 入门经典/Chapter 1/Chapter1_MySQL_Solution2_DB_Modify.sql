ALTER TABLE Attendance
  DROP COLUMN Location;

ALTER TABLE Attendance
  ADD LocationId integer;

CREATE TABLE Location
(
    LocationId integer,
    Street varchar(100),
    City varchar(75),
    State varchar(75)
);

