with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Command_Line;    use Ada.Command_Line;
with Ada.Strings.Fixed;   use Ada.Strings.Fixed;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad2 is
  type intArr is array(Natural range <>) of Integer;
  type intArr_ptr is access intArr;

  function image(number : in Natural) return String is
  begin
    return Trim(number'Image, Ada.Strings.Left);
  end image;

  function getCoins(filename : String; amount : out Integer) return intArr_ptr is
    file  : File_Type;
    coins : intArr_ptr;
  begin
    begin
      Open(file, In_File, filename);
    exception
      when NAME_ERROR =>
        Put_Line("File '" & filename & "' does not exist");
        return null;
    end;

    Get(file, amount);
    coins := new intArr(1 .. amount);

    for i in 1 .. amount loop
      Get(file, coins(i));
    end loop;

    Close(file);
    return coins;
  end getCoins;

  procedure solveChangeProblem(coins : intArr; n, r : Integer) is
    C : intArr(0 .. r) := (others => Integer'Last);
    D : intArr(0 .. r) := (others => -1);
    result : intArr_ptr;
    left : Integer := R;
    TAB : constant Character := Character'Val(9);
  begin
    C(0) := 0;

    for i in 1 .. r loop
      for j in 1 .. n loop
        if coins(j) <= i and then
           c(i - coins(j)) /= Integer'Last and then
           C(i) > C(i - coins(j)) + 1 then

            C(i) := C(i - coins(j)) + 1;
            D(i) := coins(j);
        end if;
      end loop;
    end loop;

    if C(r) = Integer'Last then
      Put_Line(image(r) & " ==> No solution!");
    else
      Put_Line(image(r) & " ==> " & image(C(r)));
      result := new intArr(1 .. n);
      for i in 1 .. n loop
        result(i) := 0;
      end loop;

      while left > 0 loop
        for i in 1 .. n loop
          if coins(i) = D(left) then
            result(i) := result(i) + 1;
            exit;
          end if;
        end loop;

      left := left - D(left);
      end loop;

      for i in 1 .. n loop
        if result(i) > 0 then
          Put_Line(TAB & image(result(i)) & " x " & image(coins(i)));
        end if;
      end loop;

      result := null;
    end if;
  end solveChangeProblem;


  amount : Integer;
  coins : intArr_ptr;
  value : Integer;
begin
  if Argument_Count < 2 then
    Put_Line("Unknown usage: <filename:str> <amount:int> ... <amount:int>");
    return;
  end if;

  coins := getCoins(Argument(1), amount);

  if coins = null then return; end if;

  for i in 2 .. Argument_Count loop
    begin
      value := Integer'Value(Argument(i));
      solveChangeProblem(coins.all, amount, value);
    exception
      when CONSTRAINT_ERROR =>
        Put_Line("'" & Argument(i) & "' is not an integer");
    end;
  end loop;

  coins := null;
end Zad2;
