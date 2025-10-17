-- { dg-do run }
-- { dg-options "-gnat2022" }

procedure parallel_do1_sequential is
   Ran_Chunk_Gen : Boolean := False;
   Ran_Branch_1  : Boolean := False;
   Ran_Branch_2  : Boolean := False;
   Ran_Branch_3  : Boolean := False;

   function Gen_Chunk (N : Integer) return Integer is
   begin
      Ran_Chunk_Gen := True;
      return 3 * N;
   end Gen_Chunk;

begin
   parallel (Gen_Chunk (3)) do
      Ran_Branch_1 := True;
   and
      Ran_Branch_2 := True;
   and
      Ran_Branch_3 := True;
   end do;

   if not (Ran_Chunk_Gen and then Ran_Branch_1
     and then Ran_Branch_2 and then Ran_Branch_3)
   then
      raise Program_Error;
   end if;
end parallel_do1_sequential;

-- { dg-warning "\"lwt\" library not found. Parallel block will execute sequentially" "" { target *-*-* } 17 }
