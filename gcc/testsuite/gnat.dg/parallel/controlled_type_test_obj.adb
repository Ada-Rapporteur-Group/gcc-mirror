with Ada.Finalization; use Ada.Finalization;
with Ada.Text_IO;      use Ada.Text_IO;

package body controlled_type_test_obj is

   protected body Id_Store is
      procedure New_Index (Id : out Object_Index) is
         Ind : Object_Index := Index;
      begin
         Index := Index + 1;
         Id := Ind;
      end New_Index;

      function Finalized (I : Object_Index) return Boolean is
      begin
         return Final_Ids (I);
      end Finalized;

      procedure Finalize (I : Object_Index) is
      begin
         Final_Ids (I) := True;
      end Finalize;
   end Id_Store;

   function Did_Finalize (I : Object_Index) return Boolean is
   begin
      return Id_Store.Finalized (I);
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
      Id_Store.New_Index (E.Index);
      Put_Line ("Initializing " & E.Index'Image);
   end Initialize;

   procedure Finalize (E : in out CI) is
   begin
      Id_Store.Finalize (E.Index);
      Put_Line ("Finalizing " & E.Index'Image);
   end Finalize;

   overriding procedure Initialize (E : in out CLI) is
   begin
      Id_Store.New_Index (E.Index);
      Put_Line ("Initialize " & E.Index'Image);
   end Initialize;

   overriding procedure Finalize (E : in out CLI) is
   begin
      Id_Store.Finalize (E.Index);
      Put_Line ("Finalize " & E.Index'Image);
   end Finalize;

end controlled_type_test_obj;
