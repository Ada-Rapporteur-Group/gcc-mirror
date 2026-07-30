-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with controlled_type_test_obj;

procedure parallel_return9 is

   package CI_Pac is new controlled_type_test_obj (Object_Limit => 100);
   use CI_Pac;

   type CLI_Arr is array (Positive range <>) of CLI;
   type Ret_Type is (Ext_Ret, Func);

   function Ret_Sec_Stack (R : Ret_Type; N : Positive) return CLI_Arr is
   begin
      parallel for I in 1 .. 100 loop
         case R is
            when Ext_Ret =>
               return Arr : CLI_Arr (1 .. N) do
                  for I in 1 .. N loop
                     Set_Val (Arr (I), I);
                  end loop;
               end return;
            when Func =>
               return Ret_Sec_Stack (Ext_Ret, N);
         end case;
      end loop;

      return Arr : CLI_Arr (1 .. 1) do
         null;
      end return;
   end Ret_Sec_Stack;

begin
   declare
      Items : CLI_Arr := Ret_Sec_Stack (Func, 10);
   begin
      for I in Items'Range loop
         if Get_Val (Items (I)) /= I then
            raise Program_Error;
         end if;
      end loop;
   end;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

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

end parallel_return9;
