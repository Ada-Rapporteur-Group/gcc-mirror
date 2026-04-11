generic
   Lo, Hi : Positive;

   type Element_Type is private;
   with procedure Element_Operation (E : Element_Type);

   type Arr_Type is array (Positive range <>) of Element_Type;
   with function Gen_Val return Arr_Type;

package parallel_for_arr8_pkg is

   procedure run_test;

end parallel_for_arr8_pkg;
