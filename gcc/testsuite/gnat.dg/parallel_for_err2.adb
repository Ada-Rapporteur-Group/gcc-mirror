-- { dg-do compile }
-- { dg-options "-gnat2022 -Werror" }

procedure parallel_for_err2 is
   subtype Chunk_Number is Natural range 2 .. 8;
begin
   parallel (Chunk_Index in Chunk_Number range 2 .. 10) -- { dg-error "warning: Suspicious chunk_index range: out of range of chunk_index subtype. \"Constraint_Error\" will be raised at run-time." }
      for I in 1..3 loop
         null;
      end loop;
end parallel_for_err2;
