Create or alter function f_ValidateProducer(@pop int, @years int) returns int as
Begin
Declare @return int
Set @return = 0
If(@pop > 0 and @years > 1)
Set @return = 1
Return @return
End
Go