-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_return3 is

   function Ret_Val (N : Positive) return Positive is
   begin
      parallel for I in 1 .. N loop
         if I mod 2 = 0 then
            return Val : Positive := N do
               if Mock_Check_Loop (1) /= TERMINATED then
                  raise Program_Error;
               end if;
            end return;
         end if;
      end loop;
      return 1;
   end Ret_Val;

   Val : Positive := Ret_Val (3);

begin
   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_return3;
