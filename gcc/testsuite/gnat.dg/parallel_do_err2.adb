-- { dg-do compile }
-- { dg-options "-gnat2022" }

with Ada.Text_IO;

procedure parallel_do_err2 is
begin
   parallel do
      null;
   and
      null;
   and
      null;
end parallel_do_err2; -- { dg-error "error: \"end do;\" expected for \"do\" at line 8" }
