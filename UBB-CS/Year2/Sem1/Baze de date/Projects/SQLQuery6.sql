use SemesterProject

BEGIN TRAN T2;

WAITFOR DELAY '00:00:02';

UPDATE StudentMembers SET s_name = 'Updated2' WHERE ID = 1;

WAITFOR DELAY '00:00:03';

COMMIT TRAN T2;
