Create or alter function f_ValidateVaccine(@administrationsN int) returns int as
Begin
Declare @return int
Set @return = 0
If(@administrationsN > 0)
Set @return = 1
Return @return
End
Go