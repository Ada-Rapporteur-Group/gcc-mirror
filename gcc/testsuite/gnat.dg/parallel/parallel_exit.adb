-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_exit is
begin
   --  Exit from parallel loop
   parallel for I in 1..3 loop
      exit when I mod 2 = 0;
   end loop;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   --  Exit enclosing loop
   Outer: for I in 1..3 loop
      parallel for J in 1..3 loop
         exit Outer when J = 1;
      end loop;
   end loop Outer;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

   --  Exit nested loop
   parallel for J in 1..3 loop
      for I in 1..15 loop
         exit when I mod 2 = 0;
      end loop;
   end loop;

   if Mock_Check_Loop (3) /= ENDED then
      raise Program_Error;
   end if;

   --  Exit from parallel loop inside enclosed loop
   Par: parallel for J in 1..3 loop
      for I in 1..15 loop
         if I mod 2 = 0 then
            exit Par;
         end if;
      end loop;
   end loop Par;

   if Mock_Check_Loop (4) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_exit;
