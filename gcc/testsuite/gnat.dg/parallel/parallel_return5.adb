-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_return5 is
   type Limited_Val is limited record
      Value : Integer;
   end record;

   function Ret_Limited (A : Natural; B : Natural) return Limited_Val is
   begin
      parallel for J in 1 .. 100 loop
         if J = A then
            return Z : Limited_Val do
               Z.Value := 42;
            end return;
         elsif J = B then
            return (Value => 99);
         end if;
      end loop;

      return L : Limited_Val do
         L.Value := 3;
      end return;
   end Ret_Limited;

   L1 : Limited_Val := Ret_Limited (20, 30);
   L2 : Limited_Val := Ret_Limited (98, 30);
   L3 : Limited_Val := Ret_Limited (200, 300);
begin
   if L1.Value /= 42 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (1) /= TERMINATED then
      raise Program_Error;
   end if;

   if L2.Value /= 99 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (2) /= TERMINATED then
      raise Program_Error;
   end if;

   if L3.Value /= 3 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (3) /= ENDED then
      raise Program_Error;
   end if;
end parallel_return5;
