-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_nested is
   Ran_Internal : Boolean := False;
   Ran_External : Boolean := False;
begin
   parallel for I in 1..100 loop
      parallel do
         if I mod 2 = 0 then
            goto Internal;
         end if;
      and
         if I mod 13 = 0 then
            goto External;
         end if;
      end do;

      goto Loop_End_Area;

      <<Internal>>
         Ran_Internal := True;

      <<Loop_End_Area>>
         null;
   end loop;

   goto End_Area;

   <<External>>
      Ran_External := True;

   <<End_Area>>
      if not (Ran_Internal and then Ran_External) then
         raise Program_Error;
      end if;

      if Mock_Check_Loop (1) /= TERMINATED then
         raise Program_Error;
      end if;
end parallel_nested;
