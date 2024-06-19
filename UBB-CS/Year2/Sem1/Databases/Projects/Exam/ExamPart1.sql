Drop table R
Drop table DeleteLog

Create Table R
(
	RID int Primary Key, 
	C1 int,
	C2 int,
	C3 int, C4 int, 
	C5 int, C6 int
)

Create Table DeleteLog(
	C3Value int,
	N int,
	DateTimeOp DATETIME
)

Insert into R(RID, C1, C2, C3, C4, C5, C6)
Values(1,20,30,2,0,50,5),(2,20,20,2,2,50,5),
(3,30,30,3,5,60,5),(8,40,40,4,4,50,7),
(9,50,50,5,7,50,7),(10,60,60,6,4,20,7),
(11,70,70,7,4,100,9),(12,80,80,8,4,30,9),
(13,90,90,9,3,90,9),(14,90,100,10,3,40,9),
(17,100,10,1,98,5,9)


Select *
From R

Select r1.C6, Count(r2.C6) NoC6, Sum(r1.C4) SumC4
From R r1 LEFT Join R r2 On r1.RID = r2.RID
Right Join R r3 On r2.RID = r3.RID
Group by r1.C6
Having Count(*) < 4

Select r1.C5, MAX(r1.C3) MaxC3
From R r1
Group by r1.C5
Union
Select Distinct r2.C4, MIN(r2.C3) MinC3
From R r2
Group by r2.C4

CREATE OR ALTER FUNCTION ufF1(@C3 int)
Returns int
Begin
Return 
	(Select Count(*)
	From R
	Where C3>@C3)
End

Delete
From R
Where RID < 12

Create or alter Trigger TRONDELETE
On R
For Delete
AS
Insert DeleteLog(C3Value,N,DateTimeOP)
Select d.C3, dbo.ufF1(d.C3)*100,GETDATE()
From deleted d

Select *
From DeleteLog