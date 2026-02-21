with Ada.Finalization; use Ada.Finalization;

--  Package for testing generic object instantiation/finalization.
--  Each controlled object is initialized with a unique, auto-incrementing
--  ID. We can use this ID to query a controlled object's state. Each
--  controlled object can also store a non-ID integer value.

generic
   Object_Limit : Positive;
   --  The maximum number of controlled objects that can be created
   --  for this package.

package controlled_type_test_obj is
   type Object_Index is new Positive range 1 .. Object_Limit;
   --  Controlled object ID type

   type CI is tagged private;
   --  Controlled object Instance

   type CLI is tagged limited private;
   --  Controlled Limited object Instance

   function Did_Finalize (I : Object_Index) return Boolean;
   --  Check if Finalize was calls for controlled object with index I 

   --  Getters and setters

   function Get_C_Id (E : CI) return Object_Index;
   function Get_C_Id (E : CLI) return Object_Index;

   function Get_Val (E : CI) return Integer;
   procedure Set_Val (E : in out CI; Val : Integer);

   function Get_Val (E : CLI) return Integer;
   procedure Set_Val (E : in out CLI; Val : Integer);

private

   type Finalization_Arr is array (Object_Index) of Boolean;

   --  Controlled object that manages the creation of new IDs

   protected Id_Store is
      procedure New_Index (Id : out Object_Index);
      procedure Finalize (I : Object_Index);
      function Finalized (I : Object_Index) return Boolean;
   private
      Index     : Object_Index := Object_Index'First;
      Final_Ids : Finalization_Arr := (others => False);
   end Id_Store;

   type CI is new Controlled with record
      Index : Object_Index;
      Value : Integer := 0;
   end record;

   overriding procedure Initialize (E : in out CI);
   overriding procedure Finalize (E : in out CI);

   type CLI is new Limited_Controlled with record
      Index : Object_Index;
      Value : Integer := 0;
   end record;

   overriding procedure Initialize (E : in out CLI);
   overriding procedure Finalize (E : in out CLI);

end controlled_type_test_obj;
