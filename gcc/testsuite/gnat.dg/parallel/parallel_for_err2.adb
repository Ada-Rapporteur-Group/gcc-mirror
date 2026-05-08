-- { dg-do compile }
-- { dg-options "-gnat2022" }

procedure parallel_for_err2 is
   subtype A is Integer range 1 .. 10;
   subtype Null_Subtype is Integer range 1 .. 0;  -- { dg-error "warning: null range" }
begin
   parallel for I in 3 .. 2 loop -- { dg-error "warning: loop range is null, loop will not execute" }
      raise Program_Error;
   end loop;

   parallel for I in Null_Subtype loop -- { dg-error "warning: loop range is null, loop will not execute" }
      raise Program_Error;
   end loop;

   begin
      parallel (Ch in A range 5 .. 15)
         for I in 1 .. 100 loop
            raise Program_Error;
         end loop;
   exception
      when Constraint_Error =>
         null;
      when others =>
         raise Program_Error;
   end;
end parallel_for_err2;

-- { dg-error "warning: static value out of range of type \"A\" defined at line 5" "" { target *-*-* } 17 }
-- { dg-error "warning: Constraint_Error will be raised at run time" "" { target *-*-* } 17 }
-- { dg-error "warning: Suspicious chunk_index range: out of range of chunk_index subtype. \"Constraint_Error\" will be raised at run-time." "" { target *-*-* } 17 }
