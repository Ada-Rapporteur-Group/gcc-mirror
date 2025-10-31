-- { dg-do run }
-- { dg-options "-gnat2022" }

with Ada.Text_IO;     use Ada.Text_IO;
with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for3 is
   Ret_Arr_Called : Integer := 0 with Atomic;

   type Group_Set is array (1 .. 5) of Boolean
     with Default_Component_Value => False;
   Groups : Group_Set;

   procedure Test (I : Integer) is
      type My_Array is array (1 .. I) of Integer;

      function Ret_Arr (J : Integer) return My_Array is
         Arr : My_Array;
      begin
         Ret_Arr_Called := Ret_Arr_Called + 1;
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
