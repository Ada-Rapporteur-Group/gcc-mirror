-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with Ada.Text_IO; use Ada.Text_IO;

procedure parallel_for_arr4 is
   type Array_2D is array
     (Positive range <>, Positive range <>)
      of Integer;

   function Gen_Arr
     (A : Positive; B : Positive)
      return Array_2D;

   function Gen_Arr
     (A : Positive; B : Positive)
      return Array_2D
   is
      Arr : Array_2D (1 .. A, 1 .. B);
      Counter : Integer := 1;
   begin
      for I in Arr'Range (1) loop
         for J in Arr'Range (2) loop
            Arr (I, J) := Counter;
            Counter := Counter + 1;
         end loop;
      end loop;

      return Arr;
   end Gen_Arr;

   A : constant Positive := 3;
   B : constant Positive := 4;
   C : constant Positive := A * B;

   Visited : array (1 .. C) of Boolean := (others => False);
begin

   parallel for Val of Gen_Arr (A, B) loop
      Visited (Val) := True;
   end loop;

   for I in Visited'Range loop
      if not Visited (I) then
         raise Program_Error;
      end if;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr4;
