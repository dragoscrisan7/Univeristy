DROP TABLE Tc
DROP TABLE Tb
DROP TABLE Ta


Create Table Ta(
	aid int Primary Key,
	a2 int Unique,
	a3 int
)
DELETE FROM Ta

Create Table Tb(
	bid int Primary Key,
	b2 int
)

Create Table Tc(
	cid int Primary Key,
	aid int Foreign Key References Ta(aid),
	bid int Foreign Key References Tb(bid)
)

GO
CREATE OR ALTER PROCEDURE insertIntoTa(@rows INT) AS
BEGIN
	DECLARE @max INT
	SET @max = @rows*2 + 100
	WHILE @rows > 0
	BEGIN
		INSERT INTO Ta VALUES (@rows, @max, @max%210)
		SET @rows = @rows - 1
		SET @max = @max - 2
	END
END

-- Procedure to generate and insert random data into Tb
GO
CREATE OR ALTER PROCEDURE insertIntoTb(@rows INT) AS
BEGIN
	WHILE @rows > 0 
	BEGIN
		INSERT INTO Tb VALUES(@rows, @rows%542)
		SET @rows = @rows - 1
	END
END

-- Procedure to generate and insert random data into Tc
GO
CREATE OR ALTER PROCEDURE insertIntoTc(@rows INT) AS
BEGIN
	DECLARE @aid INT
	DECLARE @bid INT
	WHILE @rows > 0
	BEGIN
		SET @aid = (SELECT TOP 1 aid FROM Ta ORDER BY NEWID())
		SET @bid = (SELECT TOP 1 bid FROM Tb ORDER BY NEWID())
		INSERT INTO Tc VALUES(@rows, @aid, @bid)
		SET @rows = @rows - 1
	END
END

-- Inserting data
EXEC insertIntoTa 100
EXEC insertIntoTb 150
EXEC insertIntoTc 100

SELECT *
FROM Ta

SELECT *
FROM Tb

SELECT *
FROM Tc

-- a) Write queries on Ta such that their execution plans contain the following operators:
SELECT *
FROM Ta

-- clustered index seek - return a specific subset of rows from a clustered index
SELECT *
FROM Ta
WHERE aid < 70

-- nonclustered index scan - scan the entire nonclustered index
SELECT a2
FROM Ta
ORDER BY a2

-- nonclustered index seek - return a specific subset of rows from a nonclustered index
SELECT a2
FROM Ta
WHERE a2 BETWEEN 70 AND 90

-- key lookup - nonclustered index seek + key lookup - the data is found in a nonclustered index, but additional data is needed
SELECT a3, a2
FROM Ta
WHERE a2 = 178

-- b) Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. Create a nonclustered index that can speed up the query. Examine the execution plan again.
SELECT *
FROM Tb
WHERE b2 = 78

DROP INDEX Tb_b2_index ON Tb
CREATE NONCLUSTERED INDEX Tb_b2_index ON Tb(b2)

-- c) Create a view that joins at least 2 tables. Check whether existing indexes are helpful; if not, reassess existing indexes / examine the cardinality of the tables.

GO
CREATE OR ALTER VIEW View1 AS
	SELECT A.aid, B.bid, C.cid
	FROM Tc C
	INNER JOIN Ta A ON A.aid = C.aid
	INNER JOIN Tb B ON B.bid = C.bid
	WHERE B.b2 > 50 AND A.a3 < 150

GO
SELECT *
FROM View1

DROP INDEX Ta_a3_index ON Ta
CREATE NONCLUSTERED INDEX Ta_a3_index ON Ta(a3)

DROP INDEX Tc_index ON Tc
CREATE NONCLUSTERED INDEX Tc_index ON Tc(aid, bid)
