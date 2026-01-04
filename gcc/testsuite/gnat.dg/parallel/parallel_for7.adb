-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_for7 is
   type Int_Arr is array (2 .. 10) of Integer;
   function Gen_Arr return Int_Arr;

   type Atomic_Int is new Integer with Atomic;
   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);

   Ran_Gen_Arr : aliased Atomic_Int := 0;
   Ran_Loop_1  : aliased Atomic_Int := 0;
   Ran_Loop_2  : aliased Atomic_Int := 0;
   Ran_Loop_3  : aliased Atomic_Int := 0;

   Arr : Int_Arr := (1, 2, 3,
                     4, 5, 6,
                     7, 8, 9);

   function Gen_Arr return Int_Arr is
   begin
      Ran_Gen_Arr := Ran_Gen_Arr + 1;
      return Arr;
   end Gen_Arr;
begin
   parallel for I in Gen_Arr'Range loop
      Ran_Loop_1 := Ran_Loop_1 + 1;
   end loop;

   parallel for I in Arr'Range loop
      Ran_Loop_2 := Ran_Loop_2 + 1;
   end loop;

   parallel (CI in Gen_Arr'Range)
      for I in 1 .. 100 loop
         Ran_Loop_3 := Ran_Loop_3 + 1;
      end loop;

   if Ran_Gen_Arr /= 2 then
      raise Program_Error;
   end if;

   if Ran_Loop_1 /= 9 then
      raise Program_Error;
   end if;

   if Ran_Loop_2 /= 9 then
      raise Program_Error;
   end if;

   if Ran_Loop_3 /= 100 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (3) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for7;
