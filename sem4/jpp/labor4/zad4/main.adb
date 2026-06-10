with Ada.Numerics.Discrete_Random;
with Ada.Text_IO; use Ada.Text_IO;

procedure Main is
   USER_COUNT    : constant Integer := 20;
   MESSAGE_COUNT : constant Integer := 50;

   protected Logger is
      procedure Log (Msg : String);
   end Logger;

   protected body Logger is
      procedure Log (Msg : String) is
      begin
         Put_Line (Msg);
      end Log;
   end Logger;

   task Server is
      entry Send (Target : Integer; Sender : Integer);
      entry WaitDone;
   end Server;

   task type UserTask (Id : Integer) is
      entry Start;
      entry Deliver (Sender : Integer);
      entry GetStats (Received : out Integer);
   end UserTask;

   type UserAccess is access UserTask;
   Users : array (1 .. USER_COUNT) of UserAccess;

   task body Server is
      T, S : Integer;
   begin
      for I in 1 .. USER_COUNT * MESSAGE_COUNT loop
         accept Send (Target : Integer; Sender : Integer) do
            T := Target;
            S := Sender;
         end Send;
         
         Users(T).Deliver(S);
      end loop;
      
      accept WaitDone;
   end Server;

   task body UserTask is
      subtype TargetRange is Integer range 1 .. USER_COUNT;
      package RandomTarget is new Ada.Numerics.Discrete_Random (TargetRange);
      use RandomTarget;

      Gen : Generator;
      Sent, ReceivedCount, Target : Integer := 0;
   begin
      accept Start;
      Reset(Gen, Id * 99); 

      loop
         select
            accept Deliver (Sender : Integer) do
               ReceivedCount := ReceivedCount + 1;
               Logger.Log("[<-] User" & Integer'Image(Id) & " received from" & Integer'Image(Sender));
            end Deliver;
         else
            if Sent < MESSAGE_COUNT then
               Target := Random(Gen);
               
               select
                  Server.Send(Target, Id);
                  Sent := Sent + 1;
                  Logger.Log("[->] User" & Integer'Image(Id) & " sent to" & Integer'Image(Target));
               else
                  delay 0.05;
               end select;
               
            else
               select
                  accept Deliver (Sender : Integer) do
                     ReceivedCount := ReceivedCount + 1;
                     Logger.Log("[<-] User" & Integer'Image(Id) & " received from" & Integer'Image(Sender));
                  end Deliver;
               or
                  accept GetStats (Received : out Integer) do
                     Received := ReceivedCount;
                  end GetStats;
                  exit;
               end select;
            end if;
            
         end select;
      end loop;
   end UserTask;

   TotalReceived : Integer;

begin
   Logger.Log("SERVER READY");

   for I in 1 .. USER_COUNT loop
      Users(I) := new UserTask(I);
   end loop;

   for I in 1 .. USER_COUNT loop
      Users(I).Start;
   end loop;

   Server.WaitDone;

   Logger.Log("");
   Logger.Log("SUMMARY");
   for I in 1 .. USER_COUNT loop
      Users(I).GetStats(TotalReceived);
      Logger.Log("User" & Integer'Image(I) & " received" & Integer'Image(TotalReceived) & " messages");
   end loop;
end Main;
