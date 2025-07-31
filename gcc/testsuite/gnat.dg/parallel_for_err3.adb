-- { dg-do compile }
-- { dg-options "-gnat2022" }

procedure parallel_for_err3 is
begin
   parallel for I in reverse 1..5 loop -- { dg-error "error: Parallel loops cannot use reverse in their loop parameter specification" }
      null;
   end loop;
end parallel_for_err3;
