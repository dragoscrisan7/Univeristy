Create or alter function f_ValidateMtoM(@VID int, @PID int, @sold int) returns int as
Begin
Declare @return int
Set @return = 0
If(exists 
(Select * from Vaccine_Info where Vaccine_Info.ID = @VID) and exists 
(Select * from Producers where Producers.ID = @PID) and @sold > -1)
Set @return = 1
Return @return
End
Go