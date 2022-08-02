USE BRegExp;
CREATE TABLE Parts
 (ID INT PRIMARY KEY AUTO_INCREMENT,
  PartNum VARCHAR(12),
  Description VARCHAR(50));
INSERT INTO Parts
 (ID, PartNum, Description)
  VALUES
   (NULL, 'ABC123', 'A basic widget.'),
   (NULL, 'AAC123', 'A special widget.'),
   (NULL, 'ABBC1234', 'A green widget.'),
   (NULL, 'AAAAAAC2345', 'A purple thing.'),
   (NULL, 'AAAAADD8899', 'A tartan widget'),
   (NULL, 'BC123', 'A thin widget'),
   (NULL, 'ART987', 'An artistic widget'),
   (NULL, 'XYZ345', 'A recent widget'),
   (NULL, 'AB123', 'A super widget'),
   (NULL, 'AC123', 'An exercise widget'),
   (NULL, 'ABCD234567', 'A long widget'),
   (NULL, 'STUV234', 'A late widget'),
   (NULL, 'VWX7656', 'An automatic widget'),
   (NULL, 'NOP278', 'An opinionated widget'),
   (NULL, 'A2345', 'An numeric widget');