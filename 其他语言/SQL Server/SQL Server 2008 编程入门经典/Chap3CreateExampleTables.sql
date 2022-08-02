/* This script creates a couple of tables for use with
** several examples in Chapter 3 of Beginning SQL Server
** 2008 Programming
*/

CREATE TABLE Stores
(
  StoreCode    char(4)      NOT NULL PRIMARY KEY,
  Name         varchar(40)  NOT NULL,
  Address      varchar(40)  NULL,
  City         varchar(20)  NOT NULL,
  State        char(2)      NOT NULL,
  Zip          char(5)      NOT NULL
)

CREATE TABLE Sales
(
  OrderNumber  varchar(20)  NOT NULL PRIMARY KEY,
  StoreCode    char(4)      NOT NULL 
    FOREIGN KEY REFERENCES Stores(StoreCode),
  OrderDate    date         NOT NULL,
  Quantity     int          NOT NULL,
  Terms        varchar(12)  NOT NULL,
  TitleID      int          NOT NULL
)