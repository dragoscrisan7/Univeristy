use SemesterProject

BEGIN TRAN T1;

WAITFOR DELAY '00:00:05';

UPDATE StudentMembers SET s_name = 'Updated1' WHERE ID = 1;

WAITFOR DELAY '00:00:03';

COMMIT TRAN T1;
