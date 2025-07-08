-- { dg-do compile }
-- { dg-options "-gnat2022 -Werror" }

procedure parallel_do_err6 is
begin
   parallel (0) do -- { dg-error "warning: maximum number of chunks must be greater than zero" }
      null;
   and
      null;
   end do;
end parallel_do_err6;
