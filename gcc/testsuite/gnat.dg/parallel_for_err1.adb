-- { dg-do compile }
-- { dg-options "-gnat2022 -Werror" }

procedure parallel_for_err1 is
begin
   parallel (Chunk_Index in 10 .. 9) -- { dg-error "warning: chunk specifier range is null, maximum number of chunks is zero" }
      for I in 1..3 loop
         null;
      end loop;
end parallel_for_err1;
