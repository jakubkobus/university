with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Ada.Text_IO;               use Ada.Text_IO;

procedure Main is
   PHILOSOPHER_COUNT : constant Integer := 5;
   MEAL_COUNT        : constant Integer := 3;

   protected Logger is
      procedure Log (Msg : String);
   end Logger;

   protected body Logger is
      procedure Log (Msg : String) is
      begin
         Put_Line (Msg);
      end Log;
   end Logger;

   protected type Fork is
      procedure TryGrab (Success : out Boolean);
      procedure Drop;
   private
      IsFree : Boolean := True;
   end Fork;

   protected body Fork is
      procedure TryGrab (Success : out Boolean) is
      begin
         if IsFree then
            IsFree := False;
            Success := True;
         else
            Success := False;
         end if;
      end TryGrab;

      procedure Drop is
      begin
         IsFree := True;
      end Drop;
   end Fork;

   Forks : array (1 .. PHILOSOPHER_COUNT) of Fork;

   task type Philosopher (Id : Integer);
   
   task body Philosopher is
      MealsEaten, Fails : Integer := 0;
      LeftFork  : Integer := Id;
      RightFork : Integer := (Id mod PHILOSOPHER_COUNT) + 1;
      GotLeft, GotRight : Boolean;
      
      Gen : Generator;
      
      procedure RandomWait is
         Time : Float;
      begin
         Time := Random(Gen) * 0.5; 
         delay Duration(Time);
      end RandomWait;

   begin
      Reset(Gen);

      while MealsEaten < MEAL_COUNT loop
         Logger.Log("Philosopher" & Integer'Image(Id) & " thinks...");
         RandomWait;
         
         Forks(LeftFork).TryGrab(GotLeft);
         
         if GotLeft then
            Forks(RightFork).TryGrab(GotRight);
            
            if GotRight then
               MealsEaten := MealsEaten + 1;
               Logger.Log("--- Philosopher" & Integer'Image(Id) & " eats (meal" & Integer'Image(MealsEaten) & ")");
               RandomWait;
               
               Forks(RightFork).Drop;
               Forks(LeftFork).Drop;
               Logger.Log("Philosopher" & Integer'Image(Id) & " dropped both forks");
            else
               Forks(LeftFork).Drop;
               Fails := Fails + 1;
               Logger.Log("[!] Philosopher" & Integer'Image(Id) & " couldn't get right fork, drops left one");
               RandomWait;
            end if;
         else
            Fails := Fails + 1;
            Logger.Log("[!] Philosopher" & Integer'Image(Id) & " couldn't get left fork");
            RandomWait;
         end if;
      end loop;

      Logger.Log("");
      Logger.Log("[SUCCESS] Philosopher" & Integer'Image(Id) & " finished eating, failures:" & Integer'Image(Fails));
      Logger.Log("");
   end Philosopher;

   type PhilosopherAccess is access Philosopher;
   type PhilosopherArray is array (1 .. PHILOSOPHER_COUNT) of PhilosopherAccess;
   Philosophers : PhilosopherArray;

begin
   for I in 1 .. PHILOSOPHER_COUNT loop
      Philosophers(I) := new Philosopher(I);
   end loop;
end Main;
