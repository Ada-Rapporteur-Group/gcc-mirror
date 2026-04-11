-- { dg-options "-gnat2022" }

package body parallel_for_arr8_pkg is

   procedure run_test is
   begin
      parallel for E of Gen_Val loop
         Element_Operation (E);
      end loop;
   end run_test;

end parallel_for_arr8_pkg;
