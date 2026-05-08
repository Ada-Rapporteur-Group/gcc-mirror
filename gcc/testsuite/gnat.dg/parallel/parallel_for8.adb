-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for8 is
   type Base_Type is (A, B, C, D, E);
   subtype Pred_Type is Base_Type
      with Static_Predicate => Pred_Type in A | C | E;

   type Tens is (One, Two, Three);
   for Tens use (One => 10, Two => 20, Three => 30);

   subtype Odd_Tens is Tens
      with Static_Predicate => Odd_Tens in One | Three;

   subtype Int_Sub is Integer range 1 .. 50
     with Static_Predicate => Int_Sub in 1 | 5 .. 25 | 47;

   Visited_Enum : array (Base_Type) of Boolean := (others => False);
   Visited_Ints : array (1 .. 50) of Boolean := (others => False);
   Visited_Tens : array (Tens) of Boolean := (others => False);
   Visited_Odds : array (Tens) of Boolean := (others => False);

begin
   parallel for I in Pred_Type loop
      Visited_Enum (I) := True;
   end loop;

   parallel for I in Int_Sub loop
      Visited_Ints (I) := True;
   end loop;

   parallel for I in Tens loop
      Visited_Tens (I) := True;
   end loop;

   parallel for I in Odd_Tens loop
      Visited_Odds (I) := True;
   end loop;

   for I in Pred_Type loop
      if not Visited_Enum (I) then
         raise Program_Error;
      end if;
   end loop;

   if Visited_Enum (B) or else Visited_Enum (D) then
      raise Program_Error;
   end if;

   for I in Visited_Ints'Range loop
      if I in 1 | 5 .. 25 | 47 xor Visited_Ints (I) then
         raise Program_Error;
      end if;
   end loop;

   for I in Tens loop
      if not Visited_Tens (I) then
         raise Program_Error;
      end if;
   end loop;

   for I in Odd_Tens loop
      if not Visited_Odds (I) then
         raise Program_Error;
      end if;
   end loop;

   if Visited_Odds (Two) then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (3) /= ENDED then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (4) /= ENDED then
      raise Program_Error;
   end if;

end parallel_for8;
