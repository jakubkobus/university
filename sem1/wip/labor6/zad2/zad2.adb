with Ada.Text_IO;      use Ada.Text_IO;
with Ada.Command_Line; use Ada.Command_Line;

procedure Zad2 is
  type PrmtArr_t is array(Natural range <>) of Natural;
  type PrmtArr_ptr is access PrmtArr_t;

  procedure printArray(arr : PrmtArr_ptr; n : Integer) is
  begin
    for i in 0 .. n - 1 loop
      Put(arr(i)'Img);
    end loop;
    New_Line;
  end printArray;

  function nextPermutation(arr : PrmtArr_ptr; n : Integer; min : Integer; max : Integer) return Boolean is
  begin
    for i in reverse 0 .. n - 1 loop
      if arr(i) < max then
        arr(i) := arr(i) + 1;
        for j in i + 1 .. n - 1 loop
          arr(j) := min;
        end loop;

        return True;
      end if;
    end loop;

    return False;
  end nextPermutation;

  function isValid(arr : PrmtArr_ptr; n : Integer) return Boolean is
      row   : array(0 .. N) of Natural := (others => 0);
      dgnl1 : array(-N .. N) of Natural := (others => 0);
      dgnl2 : array(0 .. 2 * N) of Natural := (others => 0);
   begin
      for i in 0 .. n - 1 loop
         row(arr(i)) := row(arr(i)) + 1;
         dgnl1(I - arr(i)) := dgnl1(I - arr(i)) + 1;
         dgnl2(I + arr(i)) := dgnl2(I + arr(i)) + 1;

         if row(arr(i)) > 1       or
            dgnl1(I - arr(i)) > 1 or
            dgnl2(I + arr(i)) > 1 then
            return False;
         end if;
      end loop;

      return True;
   end isValid;

  n : Natural;
  arr : PrmtArr_ptr;
  validSolutions : Natural := 0;
begin
  n := Integer'Value(Argument(1));
  
  arr := new PrmtArr_t(0 .. n - 1);
  arr.all := (others => 1);

  loop
    if isValid(arr, n) then
      printArray(arr, n);
      validSolutions := validSolutions + 1;
    end if;

    exit when not nextPermutation(arr, n, 1, n);
  end loop;

  Put_Line("Number of solutions:" & validSolutions'Image);
end Zad2;