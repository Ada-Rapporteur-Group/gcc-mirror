-- { dg-do run }
-- { dg-options "-gnat2022" }

with Ada.Text_IO; use Ada.Text_IO;

procedure parallel_for_err1 is
   procedure Test (Val : Integer) is
      type T is new Integer range Val .. Val + 20;
   begin
      parallel for I in T range 1 .. 20 loop
         Put_Line (I'Image);
      end loop;
   end Test;

   Raised_Err : Boolean := False;
begin
   begin
      Test (3);
   exception
      when Constraint_Error =>
         Raised_Err := True;
   end;

   if not Raised_Err then
      raise Program_Error;
   end if;
end parallel_for_err1;
