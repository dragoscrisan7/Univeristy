Use VaccinesSM
Go

--Version 1
--a)Modify the type of a Column
If(not EXISTS (Select ID From Versions Where ID = 1))
Begin
	Insert into Versions Values (1, 'Changed Pacients.Mail TYPE from VARCHAR(50) to NVARCHAR(50)')
End
Go

Create or Alter Procedure APPLY_VERSION_1 AS
	Alter Table Pacients
	Alter Column Mail nvarchar(50)
Go

Create or Alter Procedure REVERT_VERSION_1 AS
	Alter Table Pacients
	Alter Column Mail varchar(50)
Go

--Version 2
--b)add / remove a column
If(not EXISTS (Select ID From Versions Where ID = 2))
Begin
	Insert into Versions Values (2, 'Added Pacients.Gender of type varchar(16)')
End
Go

Create or Alter Procedure APPLY_VERSION_2 AS	
	Alter Table Pacients
	Add Gender varchar(16)
Go

Create or Alter Procedure REVERT_VERSION_2 AS
	Alter Table Pacients
	Drop Column Gender
Go

--Version 3
--c)add / remove a DEFAULT constraint
If(not EXISTS (Select ID From Versions Where ID = 3))
Begin
	Insert into Versions Values (3, 'Added DEFAULT VALUE 1 for Taken_Vaccines.Quantity')
End
Go

Create or Alter Procedure APPLY_VERSION_3 AS
	Alter Table Taken_Vaccines
	Add Constraint default_taken_vaccines_quantity
	Default 1 For Quantity
Go

Create or Alter Procedure REVERT_VERSION_3 AS
	Alter Table Taken_Vaccines
	Drop Constraint default_taken_vaccines_quantity
Go

--Version 4
--g)create / drop a table
If(not EXISTS (Select ID From Versions Where ID = 4))
Begin
	Insert into Versions Values (4, 'Created new Gender Table')
End
Go

Create or Alter Procedure APPLY_VERSION_4 AS
	Create Table Genders(
		Name varchar(50),
		Constraint pk_genders Primary Key(Name)
	)
Go

Create or Alter Procedure REVERT_VERSION_4 AS
	Drop Table Genders
Go

--Version 5
--d)add / remove a primary key
If(not EXISTS (Select ID From Versions Where ID = 5))
Begin
	Insert into Versions Values (5, 'Changed the Primary Key in Genders')
End
Go

Create or Alter Procedure APPLY_VERSION_5 AS
	Alter Table Genders
	Drop Constraint pk_genders
	Alter Table Genders
	Add ID int not null Identity
	Alter Table Genders
	Add Constraint pk_genders 
	Primary Key(ID)
Go

Create or Alter Procedure REVERT_VERSION_5 AS
	Alter Table Genders
	Drop Constraint pk_genders
	Alter Table Genders
	Drop Column ID
	Alter Table Genders
	Add Constraint pk_genders 
	Primary Key(Name)
Go

--Version 6
--f)add / remove a foreign key
If(not EXISTS (Select ID From Versions Where ID = 6))
Begin
	Insert into Versions Values (6, 'Added a foregin key in Pacients for Genders')
End
Go

Create or Alter Procedure APPLY_VERSION_6 AS
	Alter Table Pacients
	Drop Column Gender
	Alter Table Pacients
	Add GID int
	Alter Table Pacients
	Add Constraint fk_pacients_gender
	Foreign Key(GID) References Genders(ID)
Go

Create or Alter Procedure REVERT_VERSION_6 AS
	Alter Table Pacients
	Drop Constraint fk_pacients_gender
	Alter Table Pacients
	Drop Column GID
	Alter Table Pacients
	Add Gender varchar(16)
Go

--Version 7
--e)add / remove a candidate key
If(not EXISTS (Select ID From Versions Where ID = 7))
Begin
	Insert into Versions Values (7, 'Create Candidate Key in Pacients')
End
Go

Create or Alter Procedure APPLY_VERSION_7 AS
	Alter Table Pacients
	Add Constraint ck_pacients_cnp
	Unique(CNP)
Go

Create or Alter Procedure REVERT_VERSION_7 AS
	Alter Table Pacients
	Drop Constraint ck_pacients_cnp
Go

Create or Alter Procedure CHANGE_VERSION @Version int as
	If(not EXISTS (Select ID From Versions Where ID = @Version))
	Begin
		RAISERROR (15600, -1, -1, 'CHANGE_VERSION')
	End
	Else
	Begin
		Declare @Current_version int
		Set @Current_version = (Select Top 1 ID From Current_Version)
		
		If(@Current_version != @Version)
		Begin
			Declare @Start nvarchar(100)
			Declare @Command nvarchar(200)

			Set @Start = 'APPLY_VERSION_'
			While(@Current_version < @Version)
			Begin
				Set @Current_version = @Current_version + 1
				Set @Command = @Start + CAST(@Current_version AS VARCHAR(100))
				Exec @Command
			End

			Set @Start = 'REVERT_VERSION_'
			While(@Current_version > @Version)
			Begin
				Set @Command = @Start + CAST(@Current_version AS VARCHAR(100))
				Exec @Command
				Set @Current_version = @Current_version - 1
			End

			Update Current_Version
				Set ID = @Version
			Print('Version successfully changed to ' + CAST(@Version AS VARCHAR(100)))
		End
		Else
		Begin
			Print('Version is already ' + CAST(@Version AS VARCHAR(100)))
		End
	End
	Go
Go
Use master