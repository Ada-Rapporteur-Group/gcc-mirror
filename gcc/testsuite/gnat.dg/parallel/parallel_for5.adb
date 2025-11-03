-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_for5 is

   package Sample_Package is
      subtype Iter_Range is Natural range 1 .. 30;
   end Sample_Package;
   
   type Atomic_Int is new Integer with Atomic;

   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);
   Count : aliased Atomic_Int := 0;
begin
   parallel for I in Sample_Package.Iter_Range'Range loop
      Int_Atomic.Atomic_Add (Count, 1);
   end loop;

   if Count /= 30 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for5;
