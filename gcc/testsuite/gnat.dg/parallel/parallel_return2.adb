-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

--  Test return values on the secondary stack

procedure parallel_return2 is
   type Var_Arr is array (Positive range <>) of Integer;

   function Par_Return_Obj (Sz : Positive; V : Positive) return Var_Arr is
      Ret_Arr : Var_Arr (1 .. Sz);
   begin
      for I in 1 .. Sz loop
         Ret_Arr (I) := V;
      end loop;
      return Ret_Arr;
   end Par_Return_Obj;

   function Par_Return
     (A : Positive; B : Positive;
      C : Positive; D : Positive;
      E : Positive)
      return Var_Arr
   is
      Arr1 : Var_Arr (1 .. A) := (others => 1);
      Arr2 : Var_Arr (1 .. B) := (others => 2);
   begin
      parallel (CI in 5 .. 7) for Par_Loop_Param in 1 .. D loop
         if Par_Loop_Param = E then
            if Par_Loop_Param mod 2 = 1 then
               return Arr1;
            else
               return Par_Return_Obj (C, CI);
            end if;
         end if;
      end loop;

      return Arr2;
   end Par_Return;

   A : constant Positive := 1;
   B : constant Positive := 2;
   C : constant Positive := 3;

   Result_A : constant Var_Arr := Par_Return (A, B, C, 10, 5);
   Result_B : constant Var_Arr := Par_Return (A, B, C, 10, 20);
   Result_C : constant Var_Arr := Par_Return (A, B, C, 10, 6);

begin
   if Result_A'Length /= A then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if Result_B'Length /= B then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= ENDED then
      raise Program_Error;
   end if;

   if Result_C'Length /= C then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (3) /= TERMINATED then
      raise Program_Error;
   end if;

   for I of Result_C loop
      if I < 5 then
         raise Program_Error;
      end if;
   end loop;
end parallel_return2;
