-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_return is
   type Atomic_Int is new Integer with Atomic;

   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);

   function Compute_Something (C : Integer; S : Integer; F : Integer)
     return Integer
   is
      J : aliased Atomic_Int := 0;
   begin
      parallel for I in S .. F loop
         if I = C then
            return -14;
         else
            Int_Atomic.Atomic_Add (J, Atomic_Int (I));
         end if;
      end loop;
      return Integer (J);
   end Compute_Something;
begin
   if Compute_Something (10, 2, 5) /= 14 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   if Compute_Something (3, 2, 5) /= -14 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_return;
