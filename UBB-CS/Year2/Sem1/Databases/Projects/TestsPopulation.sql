use VaccinesSM

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO
 
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO

CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Tests] (
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [Tables] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 
	(
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRuns] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Tests] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 
	(
		[TestID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Views] WITH NOCHECK ADD 
	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 
	(
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] ADD 
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestRunViews] ADD 
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestTables] ADD 
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestViews] ADD 
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	)
GO

/*
create table TestViewDTO
(
view_id int primary key not null,
StartAt datetime not null,
EndAt datetime not null
)

create table TestTableDTO
(
table_id int primary key not null,
StartAt datetime not null,
EndAt datetime not null
)*/

INSERT INTO Views(Name) VALUES('ViewCabinets'), ('ViewPacients'), ('ViewTaken_Vaccines_Paccients');

INSERT INTO Tables(Name) VALUES('Cities'),('Countries'),('Cabinets'),('Pacients'),('Taken_Vaccines'),('Vaccines'),('Vaccine_Producers'),('Vaccine_Info');

insert into Tests(Name) values ('TestViewTaken_Vaccines_Paccients'), ('TestCabinets'), ('TestPacients')

insert into TestViews(TestID, ViewID) values (1,1),(2,2),(3,3)

insert into TestTables(TestID, TableID, NoOfRows, Position) values
(3, 5, 10, 4),
(3, 6, 10, 2),
(3, 7, 10, 5),
(3, 8, 10, 3),
(3, 4, 10, 1),
(1, 3, 10, 3),
(1, 1, 10, 2),
(1, 2, 10, 1),
(2, 4, 10, 1)


go
create or alter procedure SingleTest @test_id int
as
BEGIN
	declare @table_id int
	declare @no_rows int
	declare @name varchar(max)

	Insert Into TestRuns(Description, StartAt) Values((Select Tests.Name from Tests Where Tests.TestID = @test_id),GETDATE())

	declare @test_runs_id int = SCOPE_IDENTITY()
	declare @start_time datetime
	declare @procedure varchar(410)
	
	
	declare insert_cursor cursor
	for
	select TableID, NoOfRows from TestTables where TestID = @test_id order by Position

	open insert_cursor
	fetch next from insert_cursor into @table_id, @no_rows

	while @@FETCH_STATUS = 0
	begin
		set @start_time = GETDATE()
		set @procedure = 'populate' + (Select Tables.Name From Tables Where Tables.TableID = @table_id)+' '+ CONVERT(varchar(200), (@no_rows))
		exec(@procedure)

		Insert Into TestRunTables(TestRunID, TableID, StartAt, EndAt) Values (@test_runs_id, @table_id, @start_time, GETDATE())
		fetch next from insert_cursor into @table_id, @no_rows
	end

	declare @view_id int

	declare select_cursor cursor
	for
	select ViewID from TestViews where TestID = @test_id

	open select_cursor
	fetch next from select_cursor into @view_id

	while @@FETCH_STATUS = 0
	begin
		set @start_time = GETDATE()
		set @procedure = 'Select * From '+ (Select Views.Name From Views Where Views.ViewID = @view_id)
		exec(@procedure)

		Insert Into TestRunViews(TestRunID, ViewID, StartAt, EndAt) Values (@test_runs_id, @view_id, @start_time, GETDATE())
		fetch next from select_cursor into @view_id
	end

	declare delete_cursor cursor
	for
	select TableID from TestTables where TestID = @test_id order by Position desc

	open delete_cursor
	fetch next from delete_cursor into @table_id

	while @@FETCH_STATUS = 0
	BEGIN
		set @name = (Select Tables.Name From Tables Where Tables.TableID = @table_id)
		exec deleteTableRows @name
		fetch next from delete_cursor into @table_id
	END
	
	Update TestRuns
	Set TestRuns.EndAt = GETDATE()
	Where TestRuns.TestRunID = @test_runs_id

	CLOSE insert_cursor
	DEALLOCATE insert_cursor

	CLOSE delete_cursor
	DEALLOCATE delete_cursor

	CLOSE select_cursor
	DEALLOCATE select_cursor
END

go
create or alter procedure TestAll
as
Begin
	declare @test_id int
	declare test_cursor cursor
	for
	select Tests.TestID from Tests

	open test_cursor
	fetch next from test_cursor into @test_id

	while @@FETCH_STATUS = 0
	begin
		exec SingleTest @test_id
		fetch next from test_cursor into @test_id
	end
	CLOSE test_cursor
	DEALLOCATE test_cursor
End
go

Exec TestAll
/*
Select * from Tests
Select * from TestTables
Select * from Tables
Select * from TestViews
Select * from Views
*/
Select * from TestRunTables
Select * from TestRunViews
Select * from TestRuns

Select * from Pacients
Select * from Taken_Vaccines