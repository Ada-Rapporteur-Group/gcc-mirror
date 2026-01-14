-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with Ada.Text_IO; use Ada.Text_IO;

procedure parallel_for_arr3 is
   type Array_2D is array
     (Positive range <>, Positive range <>)
      of Integer;

   procedure Process_Arr
     (A : Positive; B : Positive);

   procedure Process_Arr
     (A : Positive; B : Positive)
   is
      C : constant Positive := A * B;
      Arr : Array_2D (1 .. A, 1 .. B);
      Counter : Integer := 1;
      Visited : array (1 .. C) of Boolean := (others => False);
   begin
      for I in Arr'Range (1) loop
         for J in Arr'Range (2) loop
            Arr (I, J) := Counter;
            Counter := Counter + 1;
         end loop;
      end loop;

      parallel for Val of Arr loop
         Visited (Val) := True;
      end loop;

      for I in Visited'Range loop
         if not Visited (I) then
            raise Program_Error;
         end if;
      end loop;
   end Process_Arr;
begin
   Process_Arr (3, 4);

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr3;
