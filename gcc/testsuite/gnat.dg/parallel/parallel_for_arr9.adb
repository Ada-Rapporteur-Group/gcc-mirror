-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

--  NOTE: This test relies on the Mock LWT being sequential.
--  This test will fail for parallel implementations of LWT.

procedure parallel_for_arr9 is
   X_Max : constant Natural := 2;
   Y_Max : constant Natural := 3;
   Total_Len : constant Natural := X_Max * Y_Max;

   type X is new Natural range 1 .. X_Max;
   type Y is new Natural range 1 .. Y_Max;

   type Arr_2D_Row is array (X, Y) of Natural;
   type Arr_2D_Col is array (X, Y) of Natural;
   pragma Convention(Fortran, Arr_2D_Col);
   type Arr_1D is array (1 .. Total_Len) of Natural;

   Row_Arr : Arr_2D_Row := ((1, 2, 3), (4, 5, 6));
   Col_Arr : Arr_2D_Col := ((1, 2, 3), (4, 5, 6));

   Row_Ord : aliased constant Arr_1D := (1, 2, 3, 4, 5, 6);
   Col_Ord : aliased constant Arr_1D := (1, 4, 2, 5, 3, 6);

   Row_Ind : Integer := 1;
   Col_Ind : Integer := 1;
begin
   parallel
   for Row_Val of Row_Arr loop
      if Row_Val /= Row_Ord (Row_Ind) then
         raise Program_Error;
      end if;
      Row_Ind := Row_Ind + 1;
   end loop;

   parallel
   for Col_Val of Col_Arr loop
      if Col_Val /= Col_Ord (Col_Ind) then
         raise Program_Error;
      end if;
      Col_Ind := Col_Ind + 1;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr9;
