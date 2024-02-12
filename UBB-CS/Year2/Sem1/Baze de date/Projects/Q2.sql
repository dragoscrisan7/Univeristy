Use VaccinesSM
go
Set transaction isolation level snapshot
Begin tran 
Select * from Producers where ID=6
Waitfor delay '00:00:03'
Select * from Producers where ID=3
Update Producers set Name='after_snpsht' where ID=6
Commit tran
Alter database VaccinesSM set allow_snapshot_isolation off