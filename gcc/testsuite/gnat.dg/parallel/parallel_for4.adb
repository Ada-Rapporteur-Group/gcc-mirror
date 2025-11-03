-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_for4 is
   subtype Iter_Range is Natural range 1 .. 25;
   type Atomic_Int is new Integer with Atomic;

   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);
   Sum : aliased Atomic_Int := 0;

   type Items is (Item_A, Item_B, Item_C, Item_D);
   
   type Items_Set_Arr is array (Items) of Boolean
     with Default_Component_Value => False;

   Items_Set : Items_Set_Arr;
begin
   parallel (Chunk_Index in Items)
      for I in Iter_Range'Range loop
         Items_Set (Chunk_Index) := True;
         Int_Atomic.Atomic_Add (Sum, Atomic_Int (I));
      end loop;

   for I in Items loop
      if not Items_Set (I) then
         raise Program_Error;
      end if;
   end loop;

   if Sum /= 325 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for4;
