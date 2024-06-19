use VaccinesSM
Select Producers.Name as Producer, VC.Name as Location, Count(Distinct P.ID) as NoUniquePacients, Sum(Taken_Vaccines.Quantity) as TotalVaccinesUsed
From Producers
Left Join
(
    Select * From Vaccine_Producers
    Where Vaccine_Producers.Vaccine_Info_ID in(
        Select Vaccine_Info.Id
        From Vaccine_Info
        Inner Join
        (
            Select *
            From Vaccine_Types
            Except
            Select *
            From Vaccine_Types
            Where Vaccine_Types.Name not in 
                (
                    Select Name
                    From Vaccine_Types
                    Where Name like '%viral%' or Name like '%mRNA%'
                )
        ) as Types
        On Vaccine_Info.Vaccine_Type_ID = Types.ID
        )
) as VP
On VP.Producer_ID = Producers.ID
Left Join
(
    Select Top 2 Vaccines.ID, Countries.Name, Vaccines.Vaccine_Producers_ID, 0 as Priority
    From Vaccines
    Inner Join Cabinets on Vaccines.Cabinets_ID = Cabinets.ID
    Right Join Cities on Cities.ID = Cabinets.City_ID
    Right Join Countries on Countries.ID = Cities.Country_ID
    Order BY Countries.Incidence

    Union

    Select Vaccines.ID, Cities.Name, Vaccines.Vaccine_Producers_ID, 1 As Priority
    From Vaccines
    Inner Join Cabinets on Vaccines.Cabinets_ID = Cabinets.ID
    Right Join Cities on Cities.ID = Cabinets.City_ID
)as VC
on VC.Vaccine_Producers_ID = VP.ID
Left Join Taken_Vaccines on Taken_Vaccines.Vaccines_ID = VC.ID
Inner Join
(
    Select *
    From Pacients as T
    Where EXISTS(Select ID From Pacients Where Pacients.Age < 25 and ID = T.ID)
)as P
on P.ID = Taken_Vaccines.Pacient_ID
Group by Producers.Name, VC.Name, VC.Priority
Having Sum(Taken_Vaccines.Quantity) > 0
Order By Sum(Taken_Vaccines.Quantity)/Count(Taken_Vaccines.Quantity) desc, Producers.Name, VC.Priority, VC.Name, Sum(Taken_Vaccines.Quantity) desc
