Use VaccinesSM
go
Waitfor delay '00:00:03'
Begin tran
Update Producers set Name='snapshot' where ID=6
Waitfor delay '00:00:03'
Commit tran