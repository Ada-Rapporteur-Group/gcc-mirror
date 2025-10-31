-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for1 is
   subtype Chunk_Number is Natural range 1 .. 8;

   Ran_A : Integer := 0 with Atomic;
   Ran_B : Integer := 0 with Atomic;
   Ran_C : Integer := 0 with Atomic;
   Ran_D : Integer := 0 with Atomic;

   function Test_A (A : Integer) return Integer is
   begin
      Ran_A := Ran_A + 1;
      return A * 2;
   end Test_A;

   function Test_B (B : Integer) return Integer is
   begin
      Ran_B := Ran_B + 1;
      return B * 3;
   end Test_B;

   function Test_C (C : Integer) return Integer is
   begin
      Ran_C := Ran_C + 1;
      return C * 3 - 1;
   end Test_C;
begin
   parallel (Chunk_Index in Test_A (1) .. Test_B (2))
      for I in Chunk_Number range Test_C (1) .. 6 loop
         Ran_D := Ran_D + 1;
      end loop;

   if Ran_A /= 1 then
      raise Program_Error;
   end if;

   if Ran_B /= 1 then
      raise Program_Error;
   end if;

   if Ran_C /= 1 then
      raise Program_Error;
   end if;

   if Ran_D /= 5 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for1;
