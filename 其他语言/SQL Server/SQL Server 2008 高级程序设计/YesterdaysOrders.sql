USE AdventureWorks

SELECT   sc.AccountNumber,
         soh.SalesOrderID,
         soh.OrderDate,
         sod.ProductID,
         pp.Name,
         sod.OrderQty,
         sod.UnitPrice,
         sod.UnitPriceDiscount * sod.UnitPrice * sod.OrderQty AS TotalDiscount,
         sod.LineTotal
FROM     Sales.Customer AS sc
INNER JOIN   Sales.SalesOrderHeader AS soh
      ON sc.CustomerID = soh.CustomerID
INNER JOIN   Sales.SalesOrderDetail AS sod
      ON soh.SalesOrderID = sod.SalesOrderID
INNER JOIN Production.Product AS pp
      ON sod.ProductID = pp.ProductID
WHERE CAST(soh.OrderDate AS Date) = 
      CAST(DATEADD(day,-1,GETDATE()) AS Date)
