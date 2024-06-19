use SemesterProject

DROP TABLE Licence;
DROP TABLE Task;
DROP TABLE StudentMembers;
DROP TABLE SoftwareTool;
DROP TABLE ProjectTeam;
DROP TABLE SemesterProject;


Create Table SemesterProject(
	ID int Identity Primary Key,
	sp_name varchar(50)
)

Create Table ProjectTeam(
	ID int Identity Primary Key,
	pt_name varchar(50),
	number int,
	SPID int Foreign Key References SemesterProject(ID)
)

Create Table StudentMembers(
	ID int Identity Primary Key,
	s_name varchar(50),
	s_role varchar(50),
	PTID int Foreign Key References ProjectTeam(ID)
)

Create Table Task(
	ID int Identity Primary Key,
	t_description varchar(50),
	SMID int Foreign Key References StudentMembers(ID)
)

Create Table SoftwareTool(
	ID int Identity Primary Key,
	st_name varchar(50),
	st_description varchar(50),
)

CREATE TABLE Licence (
    PTID INT,
    STID INT,
    availability_in_days INT,
    FOREIGN KEY (PTID) REFERENCES ProjectTeam(ID),
    FOREIGN KEY (STID) REFERENCES SoftwareTool(ID)
)