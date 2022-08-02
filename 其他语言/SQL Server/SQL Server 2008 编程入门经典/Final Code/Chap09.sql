CREATE TABLE MyTableKeyExample
(
   Column1   int IDENTITY
     PRIMARY KEY NONCLUSTERED,
   Column2   int
)

DECLARE @db_id SMALLINT;
DECLARE @object_id INT;
SET @db_id = DB_ID(N’AdventureWorks2008’);
SET @object_id = OBJECT_ID(N’AdventureWorks2008.Sales.SalesOrderDetail’);
SELECT database_id, object_id, index_id, index_depth, avg_fragmentation_in_percent,
page_count
FROM sys.dm_db_index_physical_stats(@db_id,@object_id,NULL,NULL,NULL);

ALTER INDEX PK_SalesOrderDetail_SalesOrderID_SalesOrderDetailID
  ON Sales.SalesOrderDetail
    REBUILD WITH (FILLFACTOR = 100)

