-- { dg-options "-gnat2022" }

package body parallel_for_arr7_pkg is

   procedure run_test (A : Arr_Typ) is
   begin
      parallel for E of A loop
         Element_Operation (E);
      end loop;
   end run_test;

end parallel_for_arr7_pkg;
