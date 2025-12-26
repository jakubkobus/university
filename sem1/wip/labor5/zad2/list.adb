with Ada.Text_IO; use Ada.Text_IO;

package body List is
  function isEmpty(l : List_t) return Boolean is
  begin
    return l.first = null;
  end isEmpty;

  function Pop(l : in out List_t) return Integer is
    n : NodePtr := l.first;
    e : Integer := n.elem;
  begin
    l.first := n.next;
    if l.first = null then l.last := null; end if;
    l.length := l.length - 1;
    Free(n);
    return e;
  end Pop;

  procedure Push(l : in out List_t; e : Integer) is
    n : NodePtr := new Node;
  begin
    n.elem := e;
    n.next := l.first;
    l.first := n;
    if l.last = null then l.last := n; end if;
    l.length := l.length + 1;
  end Push;

  procedure Append(l : in out List_t; e : Integer) is
    n : NodePtr := new Node;
  begin
    n.elem := e;
    if l.first = null then l.first := n;
    else l.last.next := n; end if;
    l.last := n;
    l.length := l.length + 1;
  end Append;

  procedure Print(l : List_t) is
    n : NodePtr := l.first;
  begin
    while n /= null loop
      Put(n.elem'Image);
      n := n.next;
    end loop;
    Put_Line(" (" & l.length'Image & " )");
  end Print;

  function Length(l : List_t) return Integer is
    i : Integer := 0;
    n : NodePtr := l.first;
  begin
    while n /= null loop
      i := i + 1;
      n := n.next;
    end loop;

    return i;
  end Length;

  function Get(l : List_t; i : Integer ) return Integer is
    n : NodePtr := l.first;
  begin
    for j in 1 .. (i - 1) loop
      n := n.next;
    end loop;

    return n.elem;
  end Get;

  procedure Put(l : in out List_t; i : Integer; e : Integer) is
    n : NodePtr := l.first;
  begin
    for j in 1 .. (i - 1) loop
      n := n.next;
    end loop;

    n.elem := e;
  end Put;

  procedure Insert(l : in out List_t; i : Integer; e : Integer) is
   n    : NodePtr := New Node;
   prev : NodePtr := New Node;
  begin
    n.elem := e;

    if i = 1 then
      n.next := l.first;
      l.first := n;
      if l.length = 0 then l.last := n; end if;
    else
      prev := l.first;
      for j in 1 .. (i - 2) loop
        prev := prev.next;
      end loop;

      n.next := prev.next;
      prev.next := n;

      if n.next = null then l.last := n; end if;
    end if;

    l.length := l.length + 1;
  end Insert;

  procedure Delete(l : in out List_t; i : Integer) is
    n   : NodePtr := New Node;
    tmp : NodePtr := New Node;
    r   : Integer;
  begin
    if i = 1 then
      r := Pop(l);
      return;
    end if;

    n := l.first;
    for j in 1 .. (i - 2) loop
      n := n.next;
    end loop;

    tmp := n.next;
    n.next := tmp.next;

    if n.next = null then l.last := n; end if;

    Free(tmp);
    l.length := l.length - 1;
  end Delete;

  procedure Clean(l : in out List_t) is
  r : Integer;
  begin
    while not isEmpty(l) loop
      r := Pop(l);
    end loop;
  end Clean;
end List;