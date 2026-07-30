-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with controlled_type_test_obj;

procedure parallel_return8 is

   package CI_Pac is new controlled_type_test_obj (Object_Limit => 10);
   use CI_Pac;

   type Ret_Type is (EXT_RET, FUNC);

   function Ret_Ctrl (R : Ret_Type; Val : Positive) return CI is
   begin
      parallel for I in 1 .. 100 loop
         case R is
            when EXT_RET =>
               return C : CI do
                  Set_Val (C, Val);
               end return;
            when FUNC =>
               return Ret_Ctrl (EXT_RET, Val);
         end case;
      end loop;

      return C : CI do
         null;
      end return;
   end Ret_Ctrl;

   A : constant CI := Ret_Ctrl (EXT_RET, 15);
   B : constant CI := Ret_Ctrl (FUNC, 20);

begin
   
   if Get_Val (A) /= 15 then
      raise Program_Error;
   end if;

   if Get_C_Id (A) /= 1 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if Get_Val (B) /= 20 then
      raise Program_Error;
   end if;

   if Get_C_Id (B) /= 2 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

end parallel_return8;
