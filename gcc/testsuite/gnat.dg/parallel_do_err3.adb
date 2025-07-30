-- { dg-do compile }
-- { dg-options "-gnat2022" }

procedure parallel_do_err3 is
begin
   parallel (Chunk in 1..3) do -- { dg-error "error: Range chunk specification not permitted in parallel block statements" }
      null;
   and
      null;
   and
      null;
   end do;
end parallel_do_err3;
