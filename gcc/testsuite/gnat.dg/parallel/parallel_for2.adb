-- { dg-do run }
-- { dg-options "-gnat2022" }

with Ada.Text_IO;     use Ada.Text_IO;
with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_for2 is
   type Alphabet is new Character range 'A' .. 'Z';
   subtype Sub_Alpha is Alphabet range 'C' .. 'Z';

   type Alphabet_Set is array (Alphabet) of Boolean
     with Default_Component_Value => False;
   Group_Hits : Alphabet_Set;
begin
   parallel (Ch in Sub_Alpha'Range)
      for I in 25 .. 125 loop
         Group_Hits (Ch) := True;
         Put_Line ("Chunk: " & Sub_Alpha'Image (Ch) &
                   " | I: " & Integer'Image (I));
      end loop;

   if Mock_Check_Loop (1) /= ENDED then
      raise Program_Error;
   end if;

   for I in Alphabet range
     Alphabet'First .. Alphabet'Pred (Sub_Alpha'First)
   loop
      if Group_Hits(I) then
         raise Program_Error;
      end if;
   end loop;

   for I in Sub_Alpha'Range loop
      if not Group_Hits(I) then
         raise Program_Error;
      end if;
   end loop;
end parallel_for2;
