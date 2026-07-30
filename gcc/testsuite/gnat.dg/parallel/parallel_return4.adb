-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism;   use LWT.Parallelism;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;

--  Secondary stack return value (string)

procedure parallel_return4 is

   function Get_A_Big_String (M : Natural) return String;
   function Get_A_Big_String (M : Natural) return String is
      String_Size : constant Natural := Natural'Last;
   begin
      parallel for I in 1 .. 100000 loop
         if I mod M = 0 then
            return I * 'a';
         end if;
      end loop;
      return "";
   end Get_A_Big_String;

begin
   declare
      R : String := Get_A_Big_String (30000);
   begin
      if R'Length /= 30000 then
         raise Program_Error;
      end if;
   end;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_return4;
