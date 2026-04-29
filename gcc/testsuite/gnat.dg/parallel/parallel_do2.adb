-- { dg-do run }
-- { dg-options "-gnat2022" }

with parallel_do2_pkg;
with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_do2 is

   package Inst is new parallel_do2_pkg
     (Rng => 10, Ret_Type => Integer);

begin

   if Inst.run_test(1, 2, 3, 5) /= 1 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if Inst.run_test(1, 2, 3, 15) /= 2 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

   if Inst.run_test(1, 2, 3, 25) /= 3 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (3) /= ENDED then
      raise Program_Error;
   end if;

end parallel_do2;
