use Vaccines

Drop Table Suppliers_Producers
Drop Table Pacients
Drop Table Cabinets
Drop Table VaccinesInfo_Country
Drop Table VaccinesInfo_DeniedCountry


Drop Table Denied_Country
Drop Table Suppliers
Drop table Producers
DROP Table VaccinesInfo
Drop Table Country

CREATE TABLE Producers (
  ProducerID int IDENTITY,
  ProducerName varchar(50) NOT NULL,
  PRIMARY KEY  (ProducerID)
)

Create table Suppliers
(
SupplierID int Identity,
SupplierName varchar(50),
Primary Key (SupplierID)
)

CREATE TABLE VaccinesInfo
(
VaccineID int Identity,
VaccineName varchar(50),
VaccineType varchar(50),
AdministrationsNecesary int,
Primary Key (VaccineID)
)

Create Table Suppliers_Producers
(
SupplierID int,
ProducerID int,
Primary Key (SupplierID, ProducerID),
Foreign Key (SupplierID) References Suppliers(SupplierID),
Foreign Key (ProducerID) References Producers(ProducerID)
)

CREATE TABLE Cabinets (
  CabinetID int IDENTITY,
  CabinetsName varchar(50) NOT NULL,
  ProducerID int NOT NULL,
  VaccineID int NOT NULL,
  PRIMARY KEY (CabinetID),
  FOREIGN KEY (ProducerID) REFERENCES Producers (ProducerID),
  FOREIGN KEY (VaccineID) References VaccinesInfo (VaccineID)
)

CREATE TABLE Pacients (
CabinetID int NOT NULL,
PacientID int IDENTITY,
Age int,
NumberOfVaccinesTaken int,
PRIMARY KEY (PacientID),
PacientName varchar(50),
FOREIGN KEY (CabinetID) References Cabinets (CabinetID)
)

CREATE TABLE Country (
CountryID int Identity,
CountryName varchar(50) NOT NULL,
Incidence int,
PRIMARY KEY (CountryID)
)

CREATE TABLE VaccinesInfo_Country (
CountryID int,
VaccineID int,
PRIMARY KEY (CountryID, VaccineID),
Foreign Key (CountryID) References Country(CountryID),
Foreign Key (VaccineID) References VaccinesInfo(VaccineID)
)

CREATE TABLE Denied_Country (
DeniedCountryID int Identity,
CountryName varchar(50) NOT NULL,
Incidence int,
PRIMARY KEY (DeniedCountryID)
)

CREATE TABLE VaccinesInfo_DeniedCountry (
DeniedCountryID int,
VaccineID int,
PRIMARY KEY (DeniedCountryID, VaccineID),
Foreign Key (DeniedCountryID) References Denied_Country(DeniedCountryID),
Foreign Key (VaccineID) References VaccinesInfo(VaccineID)
)
