-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for_arr6 is
   A : constant Integer := 42;
   B : constant Integer := 15;

   Chunks : array (1 .. 2) of Boolean := (others => False);
   Arr : array (1 .. 20) of Integer := (others => A);

   procedure Run_Test (Low : Integer; Hi : Integer) is
   begin
      parallel (Chunk_Id in Chunks'Range)
         for I of Arr (Low .. Hi) loop
            Chunks (Chunk_Id) := True;
            I := B;
         end loop;
   end Run_Test;
begin
   Run_Test (5, 10);

   for I in 5 .. 10 loop
      if Arr (I) /= B then
         raise Program_Error;
      end if;
   end loop;

   for I in 1 .. 4 loop
      if Arr (I) /= A then
         raise Program_Error;
      end if;
   end loop;

   for I in 11 .. 20 loop
      if Arr (I) /= A then
         raise Program_Error;
      end if;
   end loop;

   for Visited of Chunks loop
      if not Visited then
         raise Program_Error;
      end if;
   end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;
end parallel_for_arr6;
