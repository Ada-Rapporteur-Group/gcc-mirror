-- { dg-do run }
-- { dg-options "-gnat2022" }

with LWT.Parallelism; use LWT.Parallelism;

procedure parallel_return5 is
   type Limited_Val is limited record
      Value : Integer;
   end record;

   type Ret_Type is (EXT_RET, AGGR, FUNC);

   function Ret_Limited (R : Ret_Type; Val : Natural) return Limited_Val is
   begin
      parallel for J in 1 .. 100 loop
         case R is
            when EXT_RET =>
               return Z : Limited_Val do
                  Z.Value := Val;
               end return;
            when AGGR =>
               return (Value => Val);
            when FUNC =>
               return Ret_Limited (EXT_RET, Val);
         end case;
      end loop;

      return L : Limited_Val do
         L.Value := 3;
      end return;
   end Ret_Limited;

   L1 : Limited_Val := Ret_Limited (EXT_RET, 42);
   L2 : Limited_Val := Ret_Limited (AGGR, 99);
   L3 : Limited_Val := Ret_Limited (FUNC, 12);

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

   if L3.Value /= 12 then
      raise Program_Error;
   end if;

   if Mock_Check_Loop (3) /= TERMINATED then
      raise Program_Error;
   end if;
end parallel_return5;
