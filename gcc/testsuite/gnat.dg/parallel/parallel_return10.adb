-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with controlled_type_class_obj;

procedure parallel_return10 is

   package CI_Pac is new controlled_type_class_obj (Object_Limit => 10);
   use CI_Pac;

   type Ret_Type is (EXT_RET, FUNC);

   function Ret_Ctrl (R : Ret_Type; B : Boolean; Val : Positive)
     return CI'Class
   is
   begin
      parallel for I in 1 .. 100 loop
         case R is
            when EXT_RET =>
               if B then
                  declare
                     C : Child_One_CI;
                  begin
                     C.Value := Val;
                     return CI'Class (C);
                  end;
               else
                  declare
                     C : Child_Two_CI;
                  begin
                     C.Value := Val;
                     return CI'Class (C);
                  end;
               end if;
            when FUNC =>
               return Ret_Ctrl (EXT_RET, B, Val);
         end case;
      end loop;

      return C : CI do
         null;
      end return;
   end Ret_Ctrl;

   A : constant CI'Class := Ret_Ctrl (EXT_RET, True, 15);
   B : constant CI'Class := Ret_Ctrl (FUNC, False, 20);

begin
   
   if Munge_Val (A) /= 30 then
      raise Program_Error;
   end if;

   if Get_C_Id (A) /= 1 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if Munge_Val (B) /= 60 then
      raise Program_Error;
   end if;

   if Get_C_Id (B) /= 2 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

   if not Did_Finalize (1) then
      raise Program_Error;
   end if;

   if not Did_Finalize (2) then
      raise Program_Error;
   end if;
   
   for I in Object_Index range 3 .. 10 loop
      if Did_Finalize (I) then
         raise Program_Error;
      end if;
   end loop;

end parallel_return10;
