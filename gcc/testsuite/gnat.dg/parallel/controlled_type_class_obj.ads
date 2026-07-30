with Ada.Finalization; use Ada.Finalization;

--  Package for testing generic object instantiation/finalization
--  with polymorphism

generic
   Object_Limit : Positive;

package controlled_type_class_obj is

   type Object_Index is new Positive range 1 .. Object_Limit;
   --  Controlled object ID type

   type CI is new Controlled with record
      Index : Object_Index;
      Value : Integer := 0;
   end record;
   --  Controlled object Instance

   function Get_C_Id (E : CI) return Object_Index is (E.Index);
   function Munge_Val (E : CI) return Integer is (E.Value);

   overriding procedure Initialize (E : in out CI);
   overriding procedure Finalize (E : in out CI);

   type Child_One_CI is new CI with null record;
   overriding function Munge_Val (E : Child_One_CI) return Integer
     is (E.Value * 2);

   type Child_Two_CI is new CI with null record;
   overriding function Munge_Val (E : Child_Two_CI) return Integer
     is (E.Value * 3);

   function Did_Finalize (I : Object_Index) return Boolean;
   --  Check if Finalize was calls for controlled object with index I 

end controlled_type_class_obj;
