use VaccinesSM

SET IDENTITY_INSERT Pacients ON
Insert into Pacients(ID,Age,First_Name,Last_Name,CNP,Mail)
Values (1, 20, 'Dragos', 'Crisan', 8324923812076,'dragos@gmail,com'), (2, 27, 'Denis', 'Moldovan', 7095104612056,'denis@gmail,com'), 
(3, 24, 'Tabita', 'Lucaciu', 2347091256742,'tabita@gmail,com'),(4, 25, 'Bianca', 'Mereu', 2149096472341 ,'bianca@gmail,com'), 
(5, 93, 'Adi', 'Schiop', 1209378412304,'adi@gmail,com'), (6, 36, 'Ionut', 'Sancraianu', 3284710574124,'ionut@gmail,com'), 
(7, 16,'Dan', 'Angheluta', 9465738926438,'dan@gmail,com'), (8, 102, 'Ben', 'Ben', 3289489327621,'ben@gmail,com')
SET IDENTITY_INSERT Pacients OFF

SET IDENTITY_INSERT Countries ON
Insert into Countries(ID,Name,Incidence)
Values (1,'Romania',4),(2,'Tasmania',1),(3,'Tannu Tuva',3)
SET IDENTITY_INSERT Countries OFF

SET IDENTITY_INSERT Cities ON
Insert into Cities(ID, Name, Country_ID, IsCapital)
Values (1,'Cluj-Napoca',1, 0),(2,'Bucuresti',1, 1),(3,'Galati',1, 0),(4,'Hobart',2, 0),(5,'Launcheston',2, 1),
(6,'Kyzyl',3, 1),(7,'Kak',3,0)
SET IDENTITY_INSERT Cities OFF

SET IDENTITY_INSERT Cabinets ON
Insert into Cabinets(ID, Name, City_ID)
Values (1, 'Regina Maria', 2), (2, 'Med', 3), (3, 'Bioline', 1), 
(4, 'Endomed', 7), (5, 'Medstar', 4), (6, 'Life', 3), (7,'InoMed',5),(8,'Farma',6)
SET IDENTITY_INSERT Cabinets OFF

SET IDENTITY_INSERT Producers ON
Insert into Producers(ID, Name, Popularity, YearsSinceFounding)
Values (1, 'Abott', 2, 4), (2, 'Moderna', 9, 3), (3, 'GSK', 10, 5), (4, 'IDT', 1, 6), (5, 'Urevak', 4, 2)
SET IDENTITY_INSERT Producers OFF

SET IDENTITY_INSERT Vaccine_Types ON
Insert into Vaccine_Types(ID, Name)
Values (1, 'viral vector'), (2, 'protein subunit'), (3, 'mRNA'), (4, 'Extra')
SET IDENTITY_INSERT Vaccine_Types OFF

SET IDENTITY_INSERT Vaccine_Info ON
Insert into Vaccine_Info(ID, Name, AdministrationsNecesary, Vaccine_Type_ID, YearsSinceRelease)
Values (1, 'Pfizer-BioNTech', null, 3, 4), (2, 'Moderna', null, 3, 3),
(3, 'Novavax', null, 2, 2), (4, 'Johnson & Johnson’s Janssen', null, 1, 2),
(5, 'Sputnik', null, 1, 1)
SET IDENTITY_INSERT Vaccine_Info OFF

SET IDENTITY_INSERT Vaccine_Producers ON
Insert into Vaccine_Producers(ID, Vaccine_Info_ID, Producer_ID, Sold)
Values (1, 1, 4, 7), (2, 1, 5, 5), (3, 2, 2, 3), (4, 2, 4, 4), (5, 3, 1, 10), (6, 3, 2, 6), (7, 4, 3, 8), (8, 5, 1, 9)
SET IDENTITY_INSERT Vaccine_Producers OFF

SET IDENTITY_INSERT Vaccines ON
Insert into Vaccines(ID, Cabinets_ID, Vaccine_Producers_ID)
Values (1, 5, 1), (2, 4, 2), (3, 2, 3), (4, 1, 4), (5, 3, 5), (6, 8, 6), (7, 7, 7), (8, 6, 8), 
(9, 2, 4), (10, 3, 1), (11, 7, 5)
SET IDENTITY_INSERT Vaccines OFF


SET IDENTITY_INSERT Taken_Vaccines ON
Insert into Taken_Vaccines(ID, Quantity, Pacient_ID, Vaccines_ID)
Values (1, 3, 1, 2),  (2, 1, 1, 4), (3, 1, 2, 6), (4, 1, 3, 7), (5, 2, 4, 11), (6, 1, 7, 2), (7, 1, 5, 3)
SET IDENTITY_INSERT Taken_Vaccines OFF

Update Vaccine_Info
Set Vaccine_Info.AdministrationsNecesary = 1
Where Vaccine_Info.Vaccine_Type_ID = 1

Update Vaccine_Info
Set Vaccine_Info.AdministrationsNecesary = 3
Where Vaccine_Info.Vaccine_Type_ID Between 2 and 3 and Vaccine_Info.AdministrationsNecesary is null

Update Taken_Vaccines
Set Taken_Vaccines.Quantity = 1
Where Taken_Vaccines.Vaccines_ID In(4,5)

Delete Pacients
Where Pacients.Age >= 100

Delete Vaccine_Types
Where Vaccine_Types.ID = 4


Select * from Cities
