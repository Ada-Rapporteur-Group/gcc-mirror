-- { dg-do compile }
-- { dg-options "-gnat2022" }

procedure parallel_do_err5 is
begin
   parallel ('A') do -- { dg-error "error: expected an integer type" }
   -- { dg-error "error: found a character type" "" { target *-*-* } 6 }
      null;
   and
      null;
   end do;
end parallel_do_err5;
