-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with controlled_type_test_obj;

procedure parallel_return11 is

   package CI_Pac is new controlled_type_test_obj (Object_Limit => 10);
   use CI_Pac;

   package class_pkg is
      type Base_Type is abstract tagged null record;
      function Test_Method (Self : Base_Type) return Integer is abstract;

      type Child_Norm is new Base_Type with record
         A : Integer;
      end record;
      overriding function Test_Method (Self : Child_Norm) return Integer;

      type Child_Ctrl is new Base_Type with record
         Val : CI;
      end record;
      overriding function Test_Method (Self : Child_Ctrl) return Integer;
   end class_pkg;

   package body class_pkg is
      overriding function Test_Method (Self : Child_Norm) return Integer is
      begin
         return Self.A;
      end Test_Method;

      overriding function Test_Method (Self : Child_Ctrl) return Integer is
      begin
         return Get_Val (Self.Val);
      end Test_Method;
   end class_pkg;

   use class_pkg;
   type Ret_Type is (OBJ, FUNC);

   function Gen_CI (Val : Integer) return CI;
   function Get_Item (B : Boolean; R : Ret_Type; Val : Integer)
     return Base_Type'Class;

   function Gen_CI (Val : Integer) return CI is
   begin
      return C : CI do
         Set_Val (C, Val);
      end return;
   end Gen_CI;

   function Get_Item (B : Boolean; R : Ret_Type; Val : Integer)
     return Base_Type'Class
   is
      C2 : Child_Norm := (A => Val);
   begin
      parallel for I in 1 .. 10 loop
         case R is
            when OBJ =>
               if B then
                  return Base_Type'Class (Child_Ctrl'(Val => Gen_CI (Val)));
               else
                  return C2;
               end if;
            when FUNC =>
               return Get_Item (B, OBJ, Val);
         end case;
      end loop;

      return C2;
   end Get_Item;

begin

   declare
      Obj_True  : Base_Type'Class := Get_Item (True, OBJ, 3);
      Obj_False : Base_Type'Class := Get_Item (False, OBJ, 5);
      Fn_True   : Base_Type'Class := Get_Item (True, FUNC, 7);
      Fn_False  : Base_Type'Class := Get_Item (False, FUNC, 11);
   begin
      if Test_Method (Obj_True) /= 3 then
         raise Program_Error;
      end if;

      if Test_Method (Fn_True) /= 7 then
         raise Program_Error;
      end if;

      if Obj_True not in Child_Ctrl'Class
        or else Get_C_Id (Child_Ctrl (Obj_True).Val) /= 1
      then
         raise Program_Error;
      end if;

      if Fn_True not in Child_Ctrl'Class
        or else Get_C_Id (Child_Ctrl (Fn_True).Val) /= 2
      then
         raise Program_Error;
      end if;

      if Test_Method (Obj_False) /= 5 then
         raise Program_Error;
      end if;

      if Test_Method (Fn_False) /= 11 then
         raise Program_Error;
      end if;
   end;

   for I in Par_Loop_Id range 1 .. 4 loop
      if Mock_Check_Loop (I) /= TERMINATED then
         raise Program_Error;
      end if;
   end loop;

   for I in Object_Index range 1 .. 2 loop
      if not Did_Finalize (I) then
         raise Program_Error;
      end if;
   end loop;

   for I in Object_Index range 3 .. 10 loop
      if Did_Finalize (I) then
         raise Program_Error;
      end if;
   end loop;

end parallel_return11;
