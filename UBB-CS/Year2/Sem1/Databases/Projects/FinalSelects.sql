Use VaccinesSM

/*Inner join, multiple m to m joins*/
/*Display All pacients with their respective vaccine, vaccine type, city and quantity*/
Select Pacients.Last_Name, Pacients.First_name ,Pacients.Age as Age, Vaccine_Info.ID as Vaccine_ID, Vaccine_Info.Name as Vaccine_Name, Vaccine_Types.ID as VType_ID, Vaccine_Types.Name as VType_Name, Cities.Name AS City_Name, Taken_Vaccines.Quantity as Quantity
From Pacients
Inner join Taken_Vaccines on Taken_Vaccines.Pacient_ID = Pacients.ID
Inner join Vaccines on Vaccines.ID = Taken_Vaccines.Vaccines_ID
Inner join Vaccine_Producers on Vaccine_Producers.ID = Vaccines.Vaccine_Producers_ID
Inner join Vaccine_Info on Vaccine_Info.ID = Vaccine_Producers.Vaccine_Info_ID
Inner join Vaccine_Types on Vaccine_Types.ID = Vaccine_Info.Vaccine_Type_ID
Inner join Cabinets on Cabinets.ID = Vaccines.Cabinets_ID
Inner join Cities on Cities.ID = Cabinets.City_ID
Order by Pacients.Last_name, Pacients.First_Name

/*from with subquery, exists with subquery, in with subquery inside where, not in*/
/*some producers are not available in a country, find what vaccines would be available*/
Select Distinct V.Name, V.Vaccine_Type_ID
From (Select VT.ID from Vaccine_Types as VT Where VT.Name in ('viral vector','Extra')) as SingleUseTypes, Vaccine_Info as V
Left join Vaccine_Producers as VP on VP.Vaccine_Info_ID = V.ID
Where Exists(Select P.Name from Producers as P Where P.ID = VP.Producer_ID and P.Popularity > (Select avg(P.Popularity) from Producers as P)) and V.Vaccine_Type_ID not in (SingleUseTypes.ID)


/*intersect, from with subquery, group by*/
/*Show all the pacients younger than 30 years old that only took one Vaccine(the doses dont matter)*/
/*Select P.First_Name, P.Last_name
From (Select Pacients.First_Name, Pacients.Last_name from Pacients Where Pacients.Age < 30) as P
Intersect
Select Pacients.First_Name, Pacients.Last_name
From Pacients
Group by Pacients.First_Name, Pacients.Last_name
Having 1 = (Select count(Taken_Vaccines.ID) from Taken_Vaccines Where Taken_Vaccines.Pacient_ID = Pacients.ID)
*/

/*except, in with subquery in where, exists with subquery, group by*/
/*Show all cabinets that are from Romania that had at least one person vaccinated at their location, except the capital city*/
Select Distinct Cabinets.Name, Cities.Name
From Cabinets
Full join Cities on Cities.ID = Cabinets.City_ID
Where Cabinets.City_ID in (Select Cities.ID from Countries Where Cities.Country_ID = Countries.ID and Countries.Name = 'Romania') and 
exists (Select Vaccines.ID from Vaccines where Vaccines.Cabinets_ID = Cabinets.ID)
Group by Cabinets.Name, Cities.Name
Except 
Select Distinct Cabinets.Name, Cities.Name
From Cabinets
Full join Cities on Cities.Id = Cabinets.City_ID
Group by Cabinets.Name, Cities.Name, Cities.IsCapital
Having 1 = Cities.IsCapital
Order by Cities.Name

/*Union and or*/
/*Show the pacients that are older than the average whose cnp doesnt start with 2 or 3 if all pacients have unique mails and cnp's*/
Select Pacients.First_Name, Pacients.Last_name
From Pacients
Where Pacients.Mail = All
	(Select Pacients.Mail from Pacients as P where Pacients.First_Name = P.First_Name)
Union
Select Pacients.First_Name, Pacients.Last_name
From Pacients
Where Pacients.CNP = All
	(Select Pacients.CNP from Pacients as P where Pacients.First_Name = P.First_Name)
Except
Select Pacients.First_Name, Pacients.Last_name
From Pacients
Where Pacients.CNP = ANY
	(Select Pacients.CNP from Pacients
	Where Pacients.CNP like '2%' or Pacients.CNP like '3%') 
Except 
Select Pacients.First_Name, Pacients.Last_name
From Pacients
Where Pacients.Age > Any
	(Select Avg(Pacients.Age) from Pacients)

/*Show the youngest pacient that has taken more than 1 vaccine of any type*/
Select Top 1 Pacients.First_Name, Pacients.Last_name
From Pacients
Group by Pacients.First_Name, Pacients.Last_name, Pacients.ID, Pacients.Age
Having 1 < (Select SUM(Taken_Vaccines.Quantity) from Taken_Vaccines where Taken_Vaccines.Pacient_ID = Pacients.ID)
Order by Pacients.Age
/*Show the country with the most number of cabinets*/
Select Top 1 Countries.Name, Count(Cabinets.ID) as NR_OfCabinets
From Countries
Right join Cities on Cities.Country_ID = Countries.ID
Right join Cabinets on Cabinets.City_ID = Cities.ID
Group by Countries.Name
Order by NR_OfCabinets desc

/*Show the vacines that have sold more products than the average selling of vaccine products*/
Select *
From Vaccine_Info
Where Vaccine_Info.ID in
	(Select Vaccine_Producers.Vaccine_Info_ID
	From Vaccine_Producers
	Group by Vaccine_Producers.Vaccine_Info_ID, Vaccine_Producers.Sold
	Having Vaccine_Producers.Sold > (Select AVG(Vaccine_Producers.Sold) From Vaccine_Producers))
/*Same thing but with inner join and more information about vaccine producers beeing displayed*/
Select Vaccine_Producers.Vaccine_Info_ID, Vaccine_Producers.Sold, Vaccine_Info.Name
	From Vaccine_Producers
	Inner join Vaccine_Info on Vaccine_Info.ID = Vaccine_Producers.Vaccine_Info_ID
	Group by Vaccine_Producers.Vaccine_Info_ID, Vaccine_Producers.Sold, Vaccine_Info.Name
	Having Vaccine_Producers.Sold > (Select AVG(Vaccine_Producers.Sold) From Vaccine_Producers)


/*having */
/*Show pacients which have taken different vaccines at least once*/
Select *
From Pacients
Where Pacients.ID in 
	(Select Taken_Vaccines.Pacient_ID
	From Taken_Vaccines
	Group by Taken_Vaccines.Pacient_ID
	Having Count(*)>1)