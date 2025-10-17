with LWT;
with LWT.Aspects;
with System;
with Ada.Containers; use Ada.Containers;
with Ada.Containers.Hashed_Maps;

package LWT.Parallelism is
   type Longest_Integer is range System.Min_Int .. System.Max_Int;
   type Par_Loop_Id is new Integer;

   procedure Par_Range_Loop_With_Early_Exit
     (Low, High : Longest_Integer;
      Num_Chunks : Natural := 0;
      Aspects : access LWT.Aspects.Root_Aspect'Class := null;
      Loop_Body : access procedure
        (Low, High : Longest_Integer; Chunk_Index : Positive;
         PID : Par_Loop_Id));

   function Early_Exit (PID : Par_Loop_Id) return Boolean;

   type Mock_Loop_Status is (ACTIVE, TERMINATED, ENDED);
   function Mock_Check_Loop (PID : Par_Loop_Id) return Mock_Loop_Status;
private
   function Hash_Identity (PID : Par_Loop_Id)
      return Hash_Type is (Hash_Type (PID));

   package Loop_Status_Map is new
      Ada.Containers.Hashed_Maps
        (Key_Type => Par_Loop_Id,
         Element_Type => Mock_Loop_Status,
         Hash => Hash_Identity,
         Equivalent_Keys => "=");

   Next_PID      : Par_Loop_Id := 0;
   Loop_Statuses : Loop_Status_Map.Map;

   function New_PID return Par_Loop_Id with Global => Next_PID;
end LWT.Parallelism;
