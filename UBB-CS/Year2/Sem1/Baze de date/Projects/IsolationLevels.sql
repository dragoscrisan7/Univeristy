use VaccinesSM

/*Dirty reads*/
Insert into Producers (Name, Popularity, YearsSinceFounding) 
Values('producator', 1, 1)

Begin Transaction
Update Producers Set Name='nume_nou'
Where Producers.Name='producator'
Waitfor delay '00:00:10'
Rollback Transaction

Set transaction isolation level read uncommitted
Begin tran
Select * from Producers
Waitfor delay '00:00:15'
Select * from Producers
Commit tran
--change uncommitted to comitted
/*-----------------------------------------------------------------------------------*/
Insert into Producers (Name, Popularity, YearsSinceFounding)Values('P',7,7)
Begin tran
Waitfor Delay '00:00:05'
Update Producers Set Popularity=10 Where Name='P'
Commit tran
--change from committed to repeatable read
/*-----------------------------------------------------------------------------------*/
Delete Producers where Name='P'
Begin tran
Waitfor delay '00:00:04'
Insert into Producers (Name, Popularity, YearsSinceFounding) Values('P',7,7)
Commit tran
--change from repeated read to serializable
/*-----------------------------------------------------------------------------------*/
Select * 
from Vaccine_Info
Select *
from Producers
-------
SET IDENTITY_INSERT Vaccine_Info ON
Insert into Vaccine_Info(Name, AdministrationsNecesary, Vaccine_Type_ID, YearsSinceRelease)
Values ('pipi', null, 3, 4)

Begin tran
Update Vaccine_Info set Name='nu_pipi1' where ID=9
Waitfor delay '00:00:05'
Update Producers set Name='deadlock1' where ID=9
Commit tran

--we add Set DEADLOCK_PRIORITY HIGH before tran

--Set DEADLOCK_PRIORITY HIGH
Begin tran
Update Producers set Name='deadlock2' where ID=9
Waitfor delay '00:00:05'
Update Vaccine_Info set Name='nu_pipi2' where ID=9
Commit tran
/*---------------------------------------------------------------------------------------*/
Alter database VaccinesSM set allow_snapshot_isolation on
Use VaccinesSM
go
Waitfor delay '00:00:10'
Begin tran
Update Producers set Name='snapshot' where ID=6
Waitfor delay '00:00:10'
Commit tran
------
Use VaccinesSM
go
Set transaction isolation level snapshot
Begin tran 
Select * from Producers where ID=6
Waitfor delay '00:00:10'
Select * from Producers where ID=3
Update Producers set Name='after_snpsht' where ID=6
Commit tran
Alter database VaccinesSM set allow_snapshot_isolation off