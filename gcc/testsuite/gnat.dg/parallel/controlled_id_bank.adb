package body controlled_id_bank is

   protected body Id_Store is
      procedure New_Index (Id : out Object_Index) is
         Ind : Object_Index := Index;
      begin
         if Empty then
            raise Program_Error;
         elsif Ind = Object_Index'Last then
            Empty := True;
         else
            Index := Object_Index'Succ (Index);
         end if;
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

   function Did_Finalize (I : Object_Index) return Boolean
     is (Id_Store.Finalized (I));

   procedure Finalize (I : Object_Index) is
   begin
      Id_Store.Finalize (I);
   end Finalize;

   function Next_Index return Object_Index is
      NI : Object_Index;
   begin
      Id_Store.New_Index (NI);
      return NI;
   end Next_Index;

end controlled_id_bank;
