-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with Ada.Text_IO; use Ada.Text_IO;

procedure parallel_for_arr5 is
   type Array_2D is array
     (Positive range <>, Positive range <>)
      of Integer;

   A : constant Integer := 6;
   B : constant Integer := 7;
   C : constant Integer := A * B;
   Visited : array (1 .. C) of Boolean := (others => False);

   procedure Run_Test (Arr : in out Array_2D);

   procedure Process_Arr
     (A : Positive; B : Positive);

   procedure Run_Test (Arr : in out Array_2D) is
   begin
      parallel for Val of Arr loop
         Visited (Val) := True;
         Val := 0;
      end loop;
   end Run_Test;

   procedure Process_Arr
     (A : Positive; B : Positive)
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

      Run_Test (Arr);

      for I in Visited'Range loop
         if not Visited (I) then
            raise Program_Error;
         end if;
      end loop;

      for I of Arr loop
         if I /= 0 then
            raise Program_Error;
         end if;
      end loop;
   end Process_Arr;
begin
   Process_Arr (A, B);

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr5;
