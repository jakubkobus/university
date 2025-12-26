with Ada.Unchecked_Deallocation;

package List is
  type List_t is private;

  function  isEmpty(l : List_t) return Boolean;

  function  Pop(l : in out List_t) return Integer;
  procedure Push(l : in out List_t; e : Integer);
  procedure Append(l : in out List_t; e : Integer);

  function  Get(l : List_t; i : Integer ) return Integer;
  procedure Put(l : in out List_t; i : Integer; e : Integer);
  procedure Insert(l : in out List_t; i : Integer; e : Integer);
  procedure Delete(l : in out List_t; i : Integer);

  procedure Print(l : List_t);
  procedure Clean(l : in out List_t);
  function  Length(l : List_t) return Integer;

private
  type Node;
  type NodePtr is access Node;

  type Node is record
    elem : Integer := 0;
    next : NodePtr := null;
  end record;

  type List_t is record
    first  : NodePtr := null;
    last   : NodePtr := null;
    length : Integer := 0;
  end record;

  procedure Free is
    new Standard.Ada.Unchecked_Deallocation(Node, NodePtr);
end List;