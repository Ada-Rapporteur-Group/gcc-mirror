-- { dg-options "-gnat2022" }

package body parallel_do2_pkg is

   function run_test
     (A : Ret_Type; B : Ret_Type;
      C : Ret_Type; Ind : Positive)
      return Ret_Type
   is
   begin
      parallel do
         for J in 1 .. Rng loop
            if Ind = J then
               return A;
            end if;
         end loop;
      and
         for J in Rng + 1 .. Rng * 2 loop
            if Ind = J then
               return B;
            end if;
         end loop;
      end do;

      return C;
   end run_test;

end parallel_do2_pkg;
