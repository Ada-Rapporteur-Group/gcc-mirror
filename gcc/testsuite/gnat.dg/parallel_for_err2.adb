-- { dg-do compile }
-- { dg-options "-gnat2022 -Werror" }

procedure parallel_for_err2 is
   subtype Chunk_Number is Natural range 2 .. 8;
begin
   parallel (Chunk_Index in Chunk_Number range 2 .. 10) -- { dg-error "warning: suspicious subrange bound out of range of chunk index subtype" }
      for I in 1..3 loop
         null;
      end loop;
end parallel_for_err2;
