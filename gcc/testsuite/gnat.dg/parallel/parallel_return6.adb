-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with Ada.Text_IO;     use Ada.Text_IO;

with controlled_type_test_obj;

--  Test returning dynamically sized arrays of controlled objects 

procedure parallel_return6 is

   package CI_Pac is new controlled_type_test_obj (Object_Limit => 100);
   use CI_Pac;

   type CI_Arr is array (Positive range <>) of CI;

   function Ret_Sec_Stack (N : Positive; R : Positive; Id : Positive)
     return CI_Arr
   is
   begin
      parallel for I in 1 .. R loop
         if I = Id then
            if N <= 10 then
               return Arr : CI_Arr (1 .. N) do
                  for I in 1 .. N loop
                     Set_Val (Arr (I), I);
                  end loop;
               end return;
            else
               return Ret_Sec_Stack (N - 1, R, Id);
            end if;
         end if;
      end loop;

      return Arr : CI_Arr (1 .. 1) do
         null;
      end return;
   end Ret_Sec_Stack;

begin
   Put_Line ("Start of program");

   declare
      Items : CI_Arr := Ret_Sec_Stack (13, 20, 15);
   begin
      for I in 1 .. 10 loop
         if Get_Val (Items (I)) /= I then
            raise Program_Error;
         end if;
      end loop;

      Put_Line ("End of block");
   end;

   Put_Line ("End of program");

   for I in 1 .. 10 loop
      if not CI_Pac.Did_Finalize (Object_Index (I)) then
         raise Program_Error;
      end if;
   end loop;

   for I in 11 .. 100 loop
      if CI_Pac.Did_Finalize (Object_Index (I)) then
         raise Program_Error;
      end if;
   end loop;

   for I in 1 .. 4 loop
      if Mock_Check_Loop (Par_Loop_Id (I)) /= TERMINATED then
         raise Program_Error;
      end if;
   end loop;

end parallel_return6;
