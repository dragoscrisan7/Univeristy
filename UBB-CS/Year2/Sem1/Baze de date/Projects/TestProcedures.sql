use VaccinesSM

GO
create or alter procedure populatePacients @rows int
as
begin
	declare @text varchar(5) = 'test'
	declare @email_ending varchar(10) = '@test.com'
	declare @email varchar(215)
	declare @age int = 18
	declare @cnp int = 10000000
	while @rows > 0
	begin
		set @email = @text + CONVERT(varchar(200), (@rows)) + @email_ending
		set @cnp = @cnp + @rows
		insert into Pacients (Age, First_Name, Last_Name, Mail, CNP) values (@age, @text, @text, @email, @cnp)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateCabinets @rows int
as
begin
	declare @name varchar(5) = 'test'
	declare @city_id int = 0
	while @rows > 0
	begin
		select top 1 @city_id = Cities.ID from Cities order by NEWID()
		insert into Cabinets(name, City_ID) values(@name, @city_id)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateVaccine_Info @rows int
as
begin
	declare @an int = 3
	declare @ysr int = 2
	declare @name varchar(5) = 'test'
	while @rows > 0
	begin
		insert into Vaccine_Info(Name, AdministrationsNecesary, YearsSinceRelease) values(@name, @an, @ysr)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateVaccine_Producers
	@rows int
as 
begin
	declare @sold int = 5
	declare @v_i_id int

	while @rows > 0
	begin
		select top 1 @v_i_id = Vaccine_Info.ID from Vaccine_Info order by NEWID()
		insert into Vaccine_Producers(Vaccine_Info_ID, Sold) values (@v_i_id, @sold)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateCities @rows int
as
begin
	declare @text varchar(5) = 'city'
	declare @name varchar(205)
	declare @country_id int
	while @rows > 0
	begin
		set @name = @text + CONVERT(varchar(200), (@rows))
		select top 1 @country_id = Countries.id from Countries order by NEWID()
		insert into Cities(name, country_id) values(@name, @country_id)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateCountries @rows int
as
begin
	declare @text varchar(8) = 'country'
	declare @name varchar(208)
	while @rows > 0
	begin
		set @name = @text + CONVERT(varchar(200), (@rows))
		insert into Countries(name) values(@name)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateVaccines @rows int
as
begin
	declare @v_p_id int
	while @rows > 0
	begin
		select top 1 @v_p_id = Vaccine_Producers.ID from Vaccine_Producers order by NEWID()
		insert into Vaccines(Vaccine_Producers_ID) values(@v_p_id)
		set @rows = @rows - 1
	end
end

go
create or alter procedure populateTaken_Vaccines @rows int
as
begin
	declare @quantity int = 5
	declare @p_id int
	declare @v_id int
	while @rows > 0
	begin
		select top 1 @p_id = Pacients.ID from Pacients order by NEWID()
		select top 1 @v_id = Vaccines.ID from Vaccines order by NEWID()
		insert into Taken_Vaccines(Quantity, Pacient_ID, Vaccines_ID) values(@quantity, @p_id, @v_id)
		set @rows = @rows - 1
	end
end

go
create or alter procedure deleteTableRows @table_name varchar(200)
as
begin
	IF not EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = @table_name)
	BEGIN
		PRINT 'Table not found'
		RAISERROR (15600, -1, -1, 'deleteTableRows')
	END
	else
	BEGIN
		declare @sql varchar(max)
		set @sql = 'delete from ' + @table_name
		exec(@sql)
	END
end
go