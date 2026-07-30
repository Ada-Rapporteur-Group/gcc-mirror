--  Helper package for generating unique indices to associate with
--  controlled object instances.

generic
   type Object_Index is (<>);

package controlled_id_bank is

   function Did_Finalize (I : Object_Index) return Boolean;
   --  Check if Finalize was calls for controlled object with index I 

   procedure Finalize (I : Object_Index);
   --  Marks index I as having been finalized

   function Next_Index return Object_Index;
   --  Creates a new object index. Panics if no IDs are left

private

   type Finalization_Arr is array (Object_Index) of Boolean;

   --  Controlled object that manages the creation of new IDs

   protected Id_Store is
      procedure New_Index (Id : out Object_Index);
      procedure Finalize (I : Object_Index);
      function Finalized (I : Object_Index) return Boolean;
   private
      Index     : Object_Index     := Object_Index'First;
      Empty     : Boolean          := False;
      Final_Ids : Finalization_Arr := (others => False);
   end Id_Store;
end controlled_id_bank;
