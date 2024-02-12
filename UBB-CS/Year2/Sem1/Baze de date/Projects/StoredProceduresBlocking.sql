use VaccinesSM 

go
/*Select * 
from LogTable
Select * 
from Producers

Select * 
from Vaccine_Info
full join Vaccine_Producers on Vaccine_Info.ID = Vaccine_Producers.Vaccine_Info_ID
full join Producers on Vaccine_Producers.ID = Producers.ID
Go
*/
Create or alter Procedure AddVaccine_Info @vname varchar(50), @admN int, @VTI int, @yearsR int, 
@pname varchar(50), @popularity int, @yearsF int, @sold int as
Begin

Begin try
Begin tran
If(dbo.f_ValidateVaccine(@admN) <> 1)
Begin
	Raiserror('Administrations Necesary must be at least 2',14,1)
End
Insert into Vaccine_Info (Name, AdministrationsNecesary, Vaccine_Type_ID, YearsSinceRelease) 
Values (@vname, @admN, @VTI, @yearsR)
declare @VID int
Set @VID = (Select SCOPE_IDENTITY())

If(dbo.f_ValidateProducer(@popularity, @yearsF) <> 1)
Begin
	Raiserror('Popularity must be higher than 0 and years since founding must be higher than 1',14,1)
End
Insert into Producers (Name, Popularity, YearsSinceFounding) 
Values (@pname, @popularity, @yearsF)
declare @PID int
Set @PID = (Select SCOPE_IDENTITY())

If(dbo.f_ValidateMtoM(@VID, @PID, @sold) <> 1)
Begin
	Raiserror('vaccine and producer must exist and sold must be positive nr',14,1)
End

Insert into Vaccine_Producers(Vaccine_Info_ID, Producer_ID, Sold) 
Values (@VID, @PID, @sold)
Commit tran
Select 'transaction completed'
End try

Begin catch
Rollback tran
Select 'Transaction rollbacked'
End catch
End
Go

Select * 
from Vaccine_Info
Exec AddVandP 'vaccin-test',3,1,2,'producator',5,4,2
Select *
from Vaccine_Info

Delete Vaccine_Info
Where name='vaccin-test'


Select * 
from Vaccine_Info
Exec AddVandP 'vaccin-test',3,1,2,'producator',5,4,-10
Select *
from Vaccine_Info
Go
/*-----------------------------------------------------------------------------------*/

Create or alter Procedure AddVandP @vname varchar(50), @admN int, @VTI int, @yearsR int, 
@pname varchar(50), @popularity int, @yearsF int, @sold int as
Begin

Begin try
Begin tran
If(dbo.f_ValidateVaccine(@admN) <> 1)
Begin
	Raiserror('Administrations Necesary must be at least 2',14,1)
End
Insert into Vaccine_Info (Name, AdministrationsNecesary, Vaccine_Type_ID, YearsSinceRelease) 
Values (@vname, @admN, @VTI, @yearsR)
declare @VID int
Set @VID = (Select SCOPE_IDENTITY())
Commit tran
Select 'transaction completed'
End try

Begin catch
Rollback tran
Select 'Transaction rollbacked'
End catch
/*---*/
Begin try
Begin tran
If(dbo.f_ValidateProducer(@popularity, @yearsF) <> 1)
Begin
	Raiserror('Popularity must be higher than 0 and years since founding must be higher than 1',14,1)
End
Insert into Producers (Name, Popularity, YearsSinceFounding) 
Values (@pname, @popularity, @yearsF)
declare @PID int
Set @PID = (Select SCOPE_IDENTITY())
Commit tran
Select 'transaction completed'
End try

Begin catch
Rollback tran
Select 'Transaction rollbacked'
End catch
/*---*/
Begin try
Begin tran
If(dbo.f_ValidateMtoM(@VID, @PID, @sold) <> 1)
Begin
	Raiserror('vaccine and producer must exist and sold must be positive nr',14,1)
End

Insert into Vaccine_Producers(Vaccine_Info_ID, Producer_ID, Sold) 
Values (@VID, @PID, @sold)
Commit tran
Select 'transaction completed'
End try

Begin catch
Rollback tran
Select 'Transaction rollbacked'
End catch
/*---*/
End
Go


Select * 
From Vaccine_Info
Select * 
From Producers
Select * 
From Vaccine_Info
Exec AddVandP 'vaccin-test',3,1,2,'producator',5,4,2
Select * 
From Vaccine_Info
Select * 
From Producers
Select * 
From Vaccine_Producers

Delete Vaccine_Producers
Where Vaccine_Producers.ID = (Select Max(ID) from Vaccine_Producers)
Delete Vaccine_Info
Where Vaccine_Info.Name = 'vaccin-test'
Delete Producers
Where Producers.Name = 'producator'


Select * 
From Vaccine_Info
Select * 
From Producers
Select * 
From Vaccine_Info
Exec AddVandP 'vaccin-test',3,1,2,'producator',5,4,-10
Select * 
From Vaccine_Info
Select * 
From Producers
Select * 
From Vaccine_Producers

Delete Vaccine_Info
Where Vaccine_Info.Name = 'vaccin-test'
Delete Producers
Where Producers.Name = 'producator'
/*-----------------------------------------------------------------------------------*/

