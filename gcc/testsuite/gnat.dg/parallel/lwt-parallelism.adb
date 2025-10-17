package body LWT.Parallelism is
   procedure Par_Range_Loop_With_Early_Exit
      (Low, High : Longest_Integer;
      Num_Chunks : Natural := 0;
      Aspects : access LWT.Aspects.Root_Aspect'Class := null;
      Loop_Body : access procedure
         (Low, High : Longest_Integer; Chunk_Index : Positive;
         PID : Par_Loop_Id))
   is
      PID : Par_Loop_Id := New_PID;
   begin
      Loop_Body (Low, High, 1, PID);
      if Mock_Check_Loop (PID) = ACTIVE then
         Loop_Statuses.Replace (PID, ENDED);
      end if;
   end Par_Range_Loop_With_Early_Exit;

   function Early_Exit (PID : Par_Loop_Id) return Boolean is
      pragma Assert (Loop_Statuses.Contains (PID));
   begin
      Loop_Statuses.Replace (PID, TERMINATED);
      return True;
   end Early_Exit;

   function New_PID return Par_Loop_Id is
   begin
      Next_PID := Next_PID + 1;
      Loop_Statuses.Insert (Next_PID, ACTIVE);
      return Next_PID;
   end New_PID;

   function Mock_Check_Loop (PID : Par_Loop_Id) return Mock_Loop_Status is
      pragma Assert (Loop_Statuses.Contains (PID));
   begin
      return Loop_Statuses.Element (PID);
   end Mock_Check_Loop;
end LWT.Parallelism;
