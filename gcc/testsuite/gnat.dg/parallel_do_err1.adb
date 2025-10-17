-- { dg-do compile }
-- { dg-options "-gnat2022" }

with Ada.Text_IO;

procedure parallel_do_err1 is
begin
   parallel
      Ada.Text_IO.Put_Line ("Branch 1"); -- { dg-error "error: Invalid token following parallel. Expected \"do\" or \"for\"" }
   and -- { dg-error "error: \"and\" not allowed here" }
      Ada.Text_IO.Put_Line ("Branch 2");
   and -- { dg-error "error: \"and\" not allowed here" }
      Ada.Text_IO.Put_Line ("Branch 3");
   end do; -- { dg-error "error: no \"do\" for this \"end do\"" }
end parallel_do_err1;
