use SemesterProject

SET IDENTITY_INSERT SemesterProject ON
Insert into SemesterProject(ID,sp_name)
Values (1,'name1'),
(2,'name2')
SET IDENTITY_INSERT SemesterProject OFF

SET IDENTITY_INSERT ProjectTeam ON
Insert into ProjectTeam(ID,pt_name,number,SPID)
Values (1,'name1',10,1),
(2,'name2',7,2)
SET IDENTITY_INSERT ProjectTeam OFF

SET IDENTITY_INSERT StudentMembers ON
INSERT INTO StudentMembers (ID, s_name, s_role, PTID)
VALUES (1, 'Ana', 'Developer', 1),
(2, 'Bob', 'Tester', 1),
(3, 'Charlie', 'Designer', 2),
(4, 'Diana', 'Leader', 2)
SET IDENTITY_INSERT StudentMembers OFF

SET IDENTITY_INSERT Task ON
INSERT INTO Task (ID, t_description, SMID)
VALUES (1, 'Task1', 1),
       (2, 'Coding', 1),
       (3, 'Testing', 2),
       (4, 'Documentation', 3),
       (5, 'Task2', 3),
       (6, 'Task3', 4);
SET IDENTITY_INSERT Task OFF

Select * from Task
Tasks