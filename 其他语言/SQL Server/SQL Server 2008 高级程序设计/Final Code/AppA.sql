SELECT @@TRANCOUNT As TransactionNestLevel      --This will be zero 
                                                --at this point

BEGIN TRAN
SELECT @@TRANCOUNT As TransactionNestLevel      --This will be one
                                                --at this point

  BEGIN TRAN
    SELECT @@TRANCOUNT As TransactionNestLevel  --This will be two
                                                --at this point
  COMMIT TRAN
SELECT @@TRANCOUNT As TransactionNestLevel      --This will be back to one 
                                                --at this point
ROLLBACK TRAN
SELECT @@TRANCOUNT As TransactionNestLevel      --This will be back to zero
                                                --at this point


SELECT @@VERSION


CREATE TABLE dbo.test 
   (
   ColDatetimeoffset datetimeoffset
   );
GO
INSERT INTO dbo.test 
VALUES ('1998-09-20 7:45:50.71345 -5:00');
GO
SELECT SWITCHOFFSET (ColDatetimeoffset, '-08:00') 
FROM dbo.test;
GO
--Returns: 1998-09-20 04:45:50.7134500 -08:00
SELECT ColDatetimeoffset
FROM dbo.test;
--Returns: 1998-09-20 07:45:50.7134500 -05:00



DECLARE @OurDateTimeTest datetime;
SELECT @OurDateTimeTest = '2008-01-01 12:54';
SELECT TODATETIMEOFFSET(@OurDateTimeTest, '-07:00');


