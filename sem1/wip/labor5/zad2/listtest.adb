with Ada.Text_IO;                   use Ada.Text_IO;
with Ada.Integer_Text_IO;           use Ada.Integer_Text_IO;
with Ada.Strings.Unbounded;         use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;

with List; use List;

procedure listTest is
  l : List_t;
  v, i : Integer;
  command : Unbounded_String;
  continue : Boolean := True;
begin
  while continue loop
    Put("Command: ");
    Get_Line(command);

    if command = "Pop" then
      if not isEmpty(l) then
        v := Pop(l);
        Put_Line("Result: " & v'Image);
      else
        Put_Line("[Error] stack is empty");
      end if;
    elsif command = "Push" then
      Put("Value: ");
      Get(v);
      Skip_Line;
      Push(l, v);
      Put_Line("Result: OK");
    elsif command = "Append" then
      Put("Value: ");
      Get(v);
      Skip_Line;
      Append(l, v);
      Put_Line("Result: OK");
    elsif command = "Print" then
      Put("Result:");
      Print(l);
    elsif command = "Length" then
      v := Length(l);
      Put_Line("Result: " & v'Image );
    elsif command = "Get" then
      Put("Index: ");
      Get(i);
      Skip_Line;
      if i >= 1 and i <= Length(l) then
        v := Get(l, i);
        Put_Line("Result:" & v'Image);
      else
        Put_Line("[Error] index out of bounds!");
      end if;
    elsif command = "Put" then
      Put("Index: ");
      Get(i);
      Skip_Line;
      Put("Value: ");
      Get(v);
      Skip_Line;
      if i >= 1 and i <= Length(l) then
        Put(l, i, v);
        Put_Line("Result: OK");
      else
        Put_Line("[Error] index out of bounds!");
      end if;
    elsif command = "Insert" then
      Put("Index: ");
      Get(i);
      Skip_Line;
      Put("Value: ");
      Get(v);
      Skip_Line;
      if i >= 1 and i <= (Length(l) + 1) then
        Insert(l, i, v);
        Put_Line("Result: OK");
      else
        Put_Line("[Error] index out of bounds!");
      end if;
    elsif command = "Delete" then
      Put("Index: ");
      Get(i);
      Skip_Line;
      if i >= 1 and i <= Length(l) then
        Delete(l, i);
        Put_Line("Result: OK");
      else
        Put_Line("[Error] index out of bounds!");
      end if;
    elsif command = "Clean" then
      Clean(l);
      Put_Line("Result: OK");
    elsif command = "Exit" then
      continue := False;
    else
      Put_Line("Unknown command!");
    end if;
  end loop ;

  Clean(l);
end listTest;
