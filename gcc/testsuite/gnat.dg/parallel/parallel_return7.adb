-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_return7 is

   package class_pkg is
      type Base_Type is abstract tagged null record;
      function Test_Method (Self : Base_Type) return Integer is abstract;

      type Child_One is new Base_Type with record
         A : Integer;
      end record;
      overriding function Test_Method (Self : Child_One) return Integer;

      type Child_Two is new Base_Type with record
         B : Integer;
      end record;
      overriding function Test_Method (Self : Child_Two) return Integer;
   end class_pkg;

   package body class_pkg is
      overriding function Test_Method (Self : Child_One) return Integer is
      begin
         return Self.A;
      end Test_Method;

      overriding function Test_Method (Self : Child_Two) return Integer is
      begin
         return Self.B * 2;
      end Test_Method;
   end class_pkg;

   use class_pkg;

   function Get_Item (B : Boolean) return Base_Type'Class;

   function Get_Item (B : Boolean) return Base_Type'Class is
      C1 : Child_One := (A => 1);
      C2 : Child_Two := (B => 2);
   begin
      parallel for I in 1 .. 10 loop
         if B then
            return C1;
         else
            return C2;
         end if;
      end loop;
      return C1;
   end Get_Item;

   Item_True  : Base_Type'Class := Get_Item (True);
   Item_False : Base_Type'Class := Get_Item (False);

begin

   if Test_Method (Item_True) /= 1 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if Test_Method (Item_False) /= 4 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

end parallel_return7;
