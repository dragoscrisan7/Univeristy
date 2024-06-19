Use ExamExample
Go

Drop Table RoutesStations
Drop Table Stations
Drop Table Routes
Drop Table Trains
Drop Table TrainTypes
Go

Create Table TrainTypes
(
	TrainTypeID Int Primary Key,
	TTName Varchar(50),
	TTDescription Varchar(50)
)

Create Table Trains
(
	TrainID Int Primary Key,
	TName Varchar(50),
	TrainTypeID Int References TrainTypes(TrainTypeID)
)

Create Table Routes
(
	RouteID Int Primary Key,
	RName Varchar(50) Unique,
	TrainID Int References Trains(TrainID)
)


Create Table Stations
(
	StationID Int Primary Key,
	SName Varchar(50) Unique
)

Create Table RoutesStations
(
	RouteID Int References Routes(RouteID),
	StationID Int References Stations(StationID),
	Arrival Time,
	Departure Time,
	Primary Key(RouteID, StationID)
)
Go

Create or Alter Proc uspUpdateStationsOnRoute
(@RName Varchar(50), @SName Varchar(50), @Arrival Time, @Departure Time)
As 
	Declare @RouteID Int, @StationID Int

	If not exists (Select * From Routes Where RName = @RName)
	Begin
		Raiserror('Ivalide route name.',16,1)
	End

	If not exists (Select * From Stations Where SName = @SName)
	Begin 
		Raiserror('Invalid station name.',16,1)
	End

	Select @RouteID = (Select RouteID From Routes Where Rname = @RName), @StationID = 
	(Select StationID From Stations Where SName = @SName)

	If exists (Select * From RoutesStations Where RouteID = @RouteID And StationID = @StationID)
		Update RoutesStations
		Set Arrival = @Arrival, Departure = @Departure
		Where RouteID = @RouteID and StationID = @StationID
	Else
		Insert RoutesStations(RouteID, StationID, Arrival, Departure)
		Values(@RouteID, @StationID, @Arrival, @Departure)
Go
Insert TrainTypes Values(1, 'tt1', 'd1'), (2, 'tt2', 'd2')
Insert Trains Values(1, 't1', 1), (2, 't2', 1), (3, 't3', 1)
Insert Routes Values(1, 'r1', 1), (2, 'r2', 2), (3, 'r3', 3)
Insert Stations values(1, 's1'), (2, 's2'), (3, 's3')

Select * From TrainTypes
Select * From Trains
Select * From Routes
Select * From Stations
Select * From RoutesStations

Exec uspUpdateStationsOnRoute 'r1', 's1', '7:00 AM', '7:10 AM'
Exec uspUpdateStationsOnRoute 'r1', 's2', '7:00 AM', '7:10 AM'
Exec uspUpdateStationsOnRoute 'r1', 's3', '7:00 AM', '7:10 AM'

Exec uspUpdateStationsOnRoute 'r2', 's1', '7:00 AM', '7:10 AM'
Exec uspUpdateStationsOnRoute 'r2', 's2', '7:00 AM', '7:10 AM'
Exec uspUpdateStationsOnRoute 'r2', 's3', '7:00 AM', '7:10 AM'

Exec uspUpdateStationsOnRoute 'r3', 's1', '7:00 AM', '7:10 AM'
Exec uspUpdateStationsOnRoute 'r3', 's2', '7:00 AM', '7:10 AM'

Select StationID
From Stations
Except
Select StationID
From RoutesStations
Where RouteID = 3

Select R.RName
From Routes R
Where not exists
(
	Select StationID
	From Stations
	Except
	Select StationID
	From RoutesStations
	Where RouteID = R.RouteID
)
Go

--Select * From vRoutesWithAllStations

Create or Alter Function ufFilterStationsByNoRoutes(@R Int)
Returns Table
Return
Select SName 
From Stations
Where StationID in
(
Select StationID
From RoutesStations
Group By StationID
Having Count(*) > @R
)
Go

Select *
From ufFilterStationsByNoRoutes(2)

