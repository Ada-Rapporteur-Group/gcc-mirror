-- { dg-do compile }
-- { dg-options "-gnat2022 -Werror" }

procedure parallel_for_err1 is
begin
   parallel (Chunk_Index in 10 .. 9) -- { dg-error "warning: chunk specification range is null, Program_Error will be raised at runtime" }
      for I in 1..3 loop
         null;
      end loop;
end parallel_for_err1;

-- { dg-error "\"lwt\" library not found. Parallel loop will execute sequentially" "" { target *-*-* } 7 }
