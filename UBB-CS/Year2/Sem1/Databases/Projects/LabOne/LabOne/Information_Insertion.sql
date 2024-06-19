use Vaccines

SET IDENTITY_INSERT VaccinesInfo ON
Insert into VaccinesInfo(VaccineID, VaccineName, VaccineType)
Values (1, 'Pfizer-BioNTech', 'mRNA vaccine'), (2, 'Moderna', 'mRNA vaccine'),
(3, 'Novavax', 'protein subunit vaccine'), (4, 'Johnson & Johnson’s Janssen', 'viral vector vaccine'),
(5, 'Sputnik', 'viral vector vaccine')
SET IDENTITY_INSERT VaccinesInfo OFF

SET IDENTITY_INSERT Producers ON
Insert into Producers(ProducerID, ProducerName)
Values (1, 'Pfizer'), (2, 'Moderna'), (3, 'AstraZeneca'), (4, 'Johnson & Johnson/Janssen')
SET IDENTITY_INSERT Producers OFF

SET IDENTITY_INSERT Cabinets ON
Insert into Cabinets(CabinetID, CabinetsName, ProducerID, VaccineID)
Values (1, 'Regina Maria', 2, 2), (2, 'Med', 3, 5), (3, 'Bioline', 1, 4), 
(4, 'Endomed', 4, 4), (5, 'Medstar', 3, 3), (6, 'Life', 3, 5)
SET IDENTITY_INSERT Cabinets OFF

SET IDENTITY_INSERT Pacients ON
Insert into Pacients(PacientID, CabinetID, PacientName, Age, NumberOfVaccinesTaken)
Values (1, 2, 'Crisan Dragos', 20, 1), (2, 2, 'Moldovan Denis', 7, null), (3, 1, 'Tabita Lucaciu', 34, null),
(4, 5, 'Bianca Mereu', 42, 1), (5, 4, 'Adi Schiop', 93, 1), (6, 3, 'Ionut Sancraianu', 36, 1), 
(7, 6,'Dan Angheluta', 92, 2) 
SET IDENTITY_INSERT Pacients OFF

SET IDENTITY_INSERT Suppliers ON
Insert into Suppliers(SupplierID, SupplierName)
Values(1, 'European Pharma Partner')
SET IDENTITY_INSERT Suppliers OFF

SET IDENTITY_INSERT Country ON
Insert into Country(CountryID,CountryName,Incidence)
Values (1,'Romania',4),(2,'Tazmania',1),(3,'Tannu Tuva',3)
SET IDENTITY_INSERT Country OFF

Insert into VaccinesInfo_Country(CountryID, VaccineID)
Values(1,1),(1,3),(2,5),(3,1),(3,4),(2,2)

---The cabinets Med and Life have decided to join and make one cabinet Medlife---
---For this, everyone will be transfered to Medlife---
Update Pacients
Set CabinetID = 2
Where CabinetID = 6

Delete Cabinets
Where CabinetsName = 'Life'

Update Cabinets
Set CabinetsName = 'Medlife'
Where CabinetsName = 'Med'

Delete Pacients
Where CabinetID In (6) and NumberOfVaccinesTaken = 0

---All pacients without any vaccine have been obligated to be vaccinated---
Update Pacients
Set NumberOFVaccinesTaken = 1
Where NumberOFVaccinesTaken is null

Delete Pacients
Where Age BETWEEN 70 AND 100 AND CabinetID IN(3,4)

Update VaccinesInfo
Set AdministrationsNecesary = 1
Where VaccineType Like 'viral%'




