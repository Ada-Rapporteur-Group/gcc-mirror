-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with System.Atomic_Operations.Integer_Arithmetic;

procedure parallel_for_arr1 is
   type Atomic_Int is new Integer with Atomic;
   package Int_Atomic is new
     System.Atomic_Operations.Integer_Arithmetic
       (Atomic_Type => Atomic_Int);

   Ran_A : aliased Atomic_Int := 0;
   Ran_B : aliased Atomic_Int := 0;
   Ran_C : aliased Atomic_Int := 0;

   type Color is (Red, Green, Blue,
     Orange, Purple, Yellow);
   type Byte is new Integer range 0 .. 255;

   type Arr_3D_Type is array
     (1 .. 3, Color, Byte range 3 .. 7)
      of Integer;
   Total_Items : constant Integer :=
     Arr_3D_Type'Length (1) * Arr_3D_Type'Length (2) *
       Arr_3D_Type'Length (3);

   function Gen_Arr return Arr_3D_Type;
   function Gen_Hi (I : Integer) return Integer;
   function Gen_Lo (I : Integer) return Integer;

   function Gen_Arr return Arr_3D_Type is
      Counter : Integer := 1;
      Arr_3D  : Arr_3D_Type;
   begin
      for Val of Arr_3D loop
         Val := Counter;
         Counter := Counter + 1;
      end loop;

      Int_Atomic.Atomic_Add (Ran_A, 1);
      return Arr_3D;
   end Gen_Arr;

   function Gen_Lo (I : Integer) return Integer is
   begin
      Int_Atomic.Atomic_Add (Ran_B, 1);
      return I + 1;
   end Gen_Lo;

   function Gen_Hi (I : Integer) return Integer is
   begin
      Int_Atomic.Atomic_Add (Ran_C, 1);
      return I + 3;
   end Gen_Hi;

   Visited : array (1 .. Total_Items) of Boolean :=
     (others => False);
   Chunks  : array (3 .. 6) of Boolean;

begin
   parallel (Chunk_Ind in Gen_Lo (2) .. Gen_Hi (3))
      for Val of Gen_Arr loop
         Visited (Val) := True;
         Chunks (Chunk_Ind) := True;
      end loop;

   for Ind in Visited'Range loop
      if not Visited (Ind) Then
         raise Program_Error;
      end if;
   end loop;

   for Ind in Chunks'Range loop
      if not Chunks (Ind) Then
         raise Program_Error;
      end if;
   end loop;

   if Ran_A /= 1 then
      raise Program_Error;
   end if;

   if Ran_B /= 1 then
      raise Program_Error;
   end if;

   if Ran_C /= 1 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr1;
