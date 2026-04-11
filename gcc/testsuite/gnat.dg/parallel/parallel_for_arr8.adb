-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with parallel_for_arr8_pkg;

procedure parallel_for_arr8 is
   Lo : constant Positive := 1;
   Hi : constant Positive := 4;

   type Rng is array (Positive range <>) of Natural;
   Visited : array (Lo .. Hi) of Boolean := (others => False);

   function Gen return Rng is
   begin
      return (1, 2, 3, 4);
   end Gen;
   
   procedure Element_Operation (E : Natural) is
   begin
      Visited (E) := True;
   end Element_Operation;

   package Inst is new parallel_for_arr8_pkg
     (Lo => Lo,
      Hi => Hi,
      Element_Type => Natural,
      Arr_Type => Rng,
      Element_Operation => Element_Operation,
      Gen_Val => Gen);

begin

   Inst.run_test;

   for V of Visited loop
      if not V then
         raise Program_Error;
      end if;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

end parallel_for_arr8;
