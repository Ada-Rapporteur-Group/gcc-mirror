generic
   type Element_Type is private;
   with procedure Element_Operation (E : Element_Type);
package parallel_for_arr7_pkg is
   type Arr_Typ is array (Positive range <>) of Element_Type;
   procedure run_test (A : Arr_Typ);
end parallel_for_arr7_pkg;
