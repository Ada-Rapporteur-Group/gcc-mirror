-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_return is
   function Compute_Something (C : Integer; S : Integer; F : Integer) return Integer is
      J : Integer := 0 with Atomic;
   begin
      parallel for I in S .. F loop
         if I = C then
            return -14;
         else
            J := J + I;
         end if;
      end loop;
      return J;
   end Compute_Something;
begin
   if Compute_Something (10, 2, 5) /= 14 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   if Compute_Something (3, 2, 5) /= -14 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_return;
