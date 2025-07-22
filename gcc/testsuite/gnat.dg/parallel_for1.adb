-- { dg-options "-gnat2022" }

procedure parallel_for1 is
   subtype Chunk_Number is Natural range 1 .. 8;

   Ran_A : Boolean := False;
   Ran_B : Boolean := False;
   Chunk_Lower : Integer;

   function Test_A (A : Integer) return Integer is
   begin
      Ran_A := True;
      return A * 2;
   end Test_A;

   function Test_B (B : Integer) return Integer is
   begin
      Ran_B := True;
      return B * 3;
   end Test_B;
begin
   parallel (Chunk_Index in Test_A (1) .. Test_B (2))
      for I in Chunk_Number range 2..6 loop
         Chunk_Lower := Chunk_Index;
      end loop;
   
   if not (Ran_A and then Ran_B and then Chunk_Lower = 2) then
      raise Program_Error;
   end if;
end parallel_for1;
