-- { dg-do compile }
-- { dg-options "-gnat2022" }

procedure parallel_do_err4 is
begin
   parallel do
      <<TEST>>
         null;
         goto TEST2; -- { dg-error "error: target of goto statement is not reachable" }
   and
      null;
   and
      <<TEST2>>
         null;
   end do;
end parallel_do_err4;
