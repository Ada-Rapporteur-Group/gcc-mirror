with controlled_id_bank;
with Ada.Finalization; use Ada.Finalization;

package body controlled_type_test_obj is

   package Bank is new controlled_id_bank
     (Object_Index => Object_Index);

   function Did_Finalize (I : Object_Index) return Boolean is
   begin
      return Bank.Did_Finalize (I);
   end Did_Finalize;

   function Get_C_Id (E : CI) return Object_Index is
   begin
      return E.Index;
   end Get_C_Id;

   function Get_C_Id (E : CLI) return Object_Index is
   begin
      return E.Index;
   end Get_C_Id;

   function Get_Val (E : CI) return Integer is
   begin
      return E.Value;
   end Get_Val;

   procedure Set_Val (E : in out CI; Val : Integer) is
   begin
      E.Value := Val;
   end Set_Val;

   function Get_Val (E : CLI) return Integer is
   begin
      return E.Value;
   end Get_Val;

   procedure Set_Val (E : in out CLI; Val : Integer) is
   begin
      E.Value := Val;
   end Set_Val;

   procedure Initialize (E : in out CI) is
   begin
      E.Index := Bank.Next_Index;
   end Initialize;

   procedure Finalize (E : in out CI) is
   begin
      Bank.Finalize (E.Index);
   end Finalize;

   overriding procedure Initialize (E : in out CLI) is
   begin
      E.Index := Bank.Next_Index;
   end Initialize;

   overriding procedure Finalize (E : in out CLI) is
   begin
      Bank.Finalize (E.Index);
   end Finalize;

end controlled_type_test_obj;
