generic
   Rng : Positive;
   type Ret_Type is private;

package parallel_do2_pkg is

   function run_test
     (A : Ret_Type; B : Ret_Type;
      C : Ret_Type; Ind : Positive)
      return Ret_Type;

end parallel_do2_pkg;
