-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for1 is
   subtype Chunk_Number is Natural range 1 .. 8;

   Ran_A : Boolean := False;
   Ran_B : Boolean := False;
   Ran_C : Boolean := False;
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
         Ran_C := True;
      end loop;

   if not (Ran_A and then Ran_B and then Ran_C) then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for1;
