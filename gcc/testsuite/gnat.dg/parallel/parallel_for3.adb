-- { dg-do run }
-- { dg-options "-gnat2022" }

with Ada.Text_IO;     use Ada.Text_IO;
with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_for3 is
   type Atomic_Int is new Integer with Atomic;

   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);

   Ret_Arr_Called : aliased Atomic_Int := 0;

   type Group_Set is array (1 .. 5) of Boolean
     with Default_Component_Value => False;
   Groups : Group_Set;

   procedure Test (I : Integer) is
      type My_Array is array (1 .. I) of Integer;

      function Ret_Arr (J : Integer) return My_Array is
         Arr : My_Array;
      begin
         Int_Atomic.Atomic_Add (Ret_Arr_Called, 1);
         for K in My_Array'Range loop
            Arr (K) := J;
         end loop;
         return Arr;
      end Ret_Arr;
   begin
      parallel (Ch in Ret_Arr (3)'Range)
         for J in 1 .. 10 loop
            Groups (Ch) := True;
            Put_Line (Integer'Image (J));
         end loop;
   end Test;
begin
   Test (Group_Set'Last);

   for I in Group_Set'Range loop
      if not Groups (I) then
         raise Program_Error;
      end if;
   end loop;

   if Ret_Arr_Called /= 1 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for3;
