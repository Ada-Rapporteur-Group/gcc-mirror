-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_for6 is
   subtype Chunk_Number is Natural range 1 .. 8;

   type Atomic_Int is new Integer with Atomic;

   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);

   Ran_A : aliased Atomic_Int := 0;
   Ran_B : aliased Atomic_Int := 0;
   Ran_C : aliased Atomic_Int := 0;
   Ran_D : aliased Atomic_Int := 0;

   function Test_A (A : Integer) return Integer is
   begin
      Int_Atomic.Atomic_Add (Ran_A, 1);
      return A * 2;
   end Test_A;

   function Test_B (B : Integer) return Integer is
   begin
      Int_Atomic.Atomic_Add (Ran_B, 1);
      return B * 3;
   end Test_B;

   function Test_C (C : Integer) return Integer is
   begin
      Int_Atomic.Atomic_Add (Ran_C, 1);
      return C * 3 - 1;
   end Test_C;
begin
   parallel (Chunk_Index in Chunk_Number range Test_A (1) .. Test_B (2))
      for I in Test_C (1) .. 6 loop
         Int_Atomic.Atomic_Add (Ran_D, 1);
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
end parallel_for6;
