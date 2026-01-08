-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for_arr2 is
   Arr : array (1 .. 6) of Integer := (0, 1, 0, 1, 0, 1);
begin
   parallel for Val of Arr when Val = 0 loop
      Val := 2;
   end loop;

   for Ind in Arr'Range loop
      if Arr (Ind) /= Ind mod 2 + 1 then
         raise Program_Error;
      end if;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr2;
