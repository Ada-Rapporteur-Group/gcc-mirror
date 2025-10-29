-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with Ada.Text_IO;     use Ada.Text_IO;

procedure parallel_nested2 is
begin
   for I in 1 .. 10 loop
      parallel do
         if I mod 2 = 0 then
            exit;
         end if;
      and
         Put_Line ("Test " & Integer'Image (I));
      end do;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

   parallel for I in 1 .. 10 loop
      parallel do
         exit when I mod 2 = 0;
      and
         Put_Line ("Test " & Integer'Image (I));
      end do;
   end loop;

   if Mock_Check_Loop (3) /= TERMINATED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (4) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (5) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_nested2;
