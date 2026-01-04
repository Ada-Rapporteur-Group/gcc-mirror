-- { dg-do compile }
-- { dg-options "-gnat2022 -Werror" }

with Ada.Text_IO; use Ada.Text_IO;

procedure parallel_for8 is
   subtype A is Integer range 1 .. 10;
begin
   parallel for I in 3 .. 2 loop -- { dg-error "warning: loop range is null, loop will not execute" }
      Put_Line ("Unreachable");
   end loop;

   parallel (Ch in A range 5 .. 15)
      for I in 1 .. 100 loop
         Put_Line ("Unreachable");
      end loop;
end parallel_for8;

-- { dg-error "warning: static value out of range of type \"A\" defined at line 7" "" { target *-*-* } 13 }
-- { dg-error "warning: Constraint_Error will be raised at run time" "" { target *-*-* } 13 }
-- { dg-error "warning: Suspicious chunk_index range: out of range of chunk_index subtype. \"Constraint_Error\" will be raised at run-time." "" { target *-*-* } 13 }
