CREATE TRIGGER Sales.SalesOrderDetailNotDiscontinued
   ON Sales.SalesOrderDetail
   FOR INSERT, UPDATE
AS
   IF EXISTS 
      (
       SELECT 'True' 
       FROM Inserted i
       JOIN Production.Product p
          ON i.ProductID = p.ProductID
       WHERE p.DiscontinuedDate IS NOT NULL
      )
   BEGIN
      RAISERROR('Order Item is discontinued. Transaction Failed.',16,1)
      ROLLBACK TRAN
   END


UPDATE Production.Product
SET DiscontinuedDate = '01-01-2008'
WHERE ProductID = 680


INSERT INTO Sales.SalesOrderDetail
VALUES 
(43659, '4911-403C-98', 1, 680, 1, 1431.50,0.00, NEWID(), GETDATE())


CREATE TRIGGER Production.ProductIsRationed
   ON Production.ProductInventory
   FOR UPDATE
AS
   IF EXISTS 
      (
       SELECT 'True' 
       FROM Inserted i
       JOIN Deleted d
          ON i.ProductID = d.ProductID
         AND i.LocationID = d.LocationID
       WHERE (d.Quantity - i.Quantity) > d.Quantity / 2
          AND d.Quantity – i.Quantity > 0
      )
   BEGIN
      RAISERROR('Cannot reduce stock by more than 50%% at once.',16,1)
      ROLLBACK TRAN
   END


UPDATE Production.ProductInventory
SET Quantity = 1  -- Was 408 if you want to set it back
WHERE ProductID = 1
  AND LocationID = 1


ALTER TRIGGER Production.ProductIsRationed
   ON Production.ProductInventory
   FOR UPDATE
AS
   IF UPDATE(Quantity)
   BEGIN
     IF EXISTS 
      (
       SELECT 'True' 
       FROM Inserted i
       JOIN Deleted d
        ON i.ProductID = d.ProductID
       AND i.LocationID = d.LocationID
       WHERE (d.Quantity - i.Quantity) > d.Quantity / 2
        AND d.Quantity > 0
      )
     BEGIN
      RAISERROR('Cannot reduce stock by more than 50%% at once.',16,1)
      ROLLBACK TRAN
     END
  END



BEGIN TRAN
  -- This one should work
  UPDATE Production.ProductInventory
  SET Quantity = 400  -- Was 408 if you want to set it back
  WHERE ProductID = 1
    AND LocationID = 1
  
  -- This one shouldn't
  UPDATE Production.ProductInventory
  SET Quantity = 1  -- Was 408 if you want to set it back
  WHERE ProductID = 1
    AND LocationID = 1
IF @@TRANCOUNT > 0
  ROLLBACK TRAN

