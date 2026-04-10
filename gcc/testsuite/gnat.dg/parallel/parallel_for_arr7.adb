-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;
with parallel_for_arr7_pkg;

procedure parallel_for_arr7 is

   Lo : constant Natural := 1;
   Hi : constant Natural := 3;

   Visited : array (Lo .. Hi) of Boolean := (others => False);

   procedure Visit (I : Integer) is
   begin
      Visited (I) := True;
   end Visit;

   package Inst is new parallel_for_arr7_pkg
     (Element_Type => Integer,
      Element_Operation => Visit);
   
   Arr : Inst.Arr_Typ (1 .. 3) := (1, 2, 3);
begin

   Inst.run_test (Arr);

   for V of Visited loop
      if not V then
         raise Program_Error;
      end if;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

end parallel_for_arr7;
