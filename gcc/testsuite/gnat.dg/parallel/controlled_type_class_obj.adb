with controlled_id_bank;

package body controlled_type_class_obj is

   package Bank is new controlled_id_bank (Object_Index => Object_Index);

   function Did_Finalize (I : Object_Index) return Boolean is
   begin
      return Bank.Did_Finalize (I);
   end Did_Finalize;

   procedure Initialize (E : in out CI) is
   begin
      E.Index := Bank.Next_Index;
   end Initialize;

   procedure Finalize (E : in out CI) is
   begin
      Bank.Finalize (E.Index);
   end Finalize;

end controlled_type_class_obj;
