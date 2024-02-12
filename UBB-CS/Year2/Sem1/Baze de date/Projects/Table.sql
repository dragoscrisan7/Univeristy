use VaccinesSM

DROP TABLE Taken_Vaccines
DROP TABLE Vaccines
DROP TABLE Vaccine_Producers
DROP TABLE Producers
DROP TABLE Vaccine_Info
DROP TABLE Vaccine_Types

DROP TABLE Cabinets
DROP TABLE Cities
DROP TABLE Countries

DROP TABLE Pacients
DROP TABLE Current_Version
DROP TABLE Versions

DROP TABLE LogTable

CREATE TABLE Pacients (
	ID int IDENTITY Primary Key,
	Age int,
	First_Name varchar(50),
	Last_name varchar(50),
	Mail varchar(50),
	CNP varchar(13)
)

CREATE TABLE Countries (
	ID int Identity Primary key,
	Name varchar(50) NOT NULL,
	Incidence int
)

CREATE TABLE Cities (
	ID int Identity Primary key,
	Name varchar(50) NOT NULL,
	Country_ID int,
	IsCapital bit,
	Foreign key (Country_id) References Countries(ID)
)

CREATE TABLE Cabinets (
	ID int IDENTITY Primary Key,
	Name varchar(50) NOT NULL,
	City_ID int NOT NULL,
	Foreign key (City_ID) References Cities(ID)
)

CREATE TABLE Producers (
	ID int IDENTITY Primary Key,
	Name varchar(50) NOT NULL,
	Popularity int,
	YearsSinceFounding int
)

CREATE TABLE Vaccine_Types (
	ID int IDENTITY Primary Key,
	Name varchar(50) NOT NULL
)

CREATE TABLE Vaccine_Info
(
	ID int Identity Primary Key,
	Name varchar(50),
	AdministrationsNecesary int,
	Vaccine_Type_ID int Foreign Key References Vaccine_Types(ID),
	YearsSinceRelease int
)

CREATE TABLE Vaccine_Producers(
	ID int Identity Primary Key,
	Vaccine_Info_ID int Foreign Key References Vaccine_Info(ID),
	Producer_ID int Foreign Key References Producers(ID),
	Sold int
	--got unique out for running tests
	--Unique (Vaccine_Info_ID, Producer_ID)
)

CREATE TABLE Vaccines(
	ID int Identity Primary key,
	Cabinets_ID int Foreign Key References Cabinets(ID),
	Vaccine_Producers_ID int  Foreign Key References Vaccine_Producers(ID),
	--remove unique for tests
	--Unique (Cabinets_ID, Vaccine_Producers_ID)
)

CREATE TABLE Taken_Vaccines(
	ID int Identity Primary Key,
	Quantity int, 
	Pacient_ID int Foreign Key References Pacients(ID),
	Vaccines_ID int Foreign Key References Vaccines(ID),
	Check(Quantity>0)
	--removed unique for tests
	--Unique(Pacient_ID, Vaccines_ID),
)


Create Table Versions(
	ID int Primary Key,
	Description varchar(500)
)
Create Table Current_Version(
	ID int Primary Key Foreign Key References Versions(ID)
)

Insert into Versions Values(0,'base version')
Insert into Current_Version Values(0)

Create Table LogTable(
	LID int Primary Key,
	TypeOperation varchar(50),
	TableOperation varchar(50),
	ExecutionDate DateTime,
)